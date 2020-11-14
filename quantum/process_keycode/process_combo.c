/* Copyright 2016 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "print.h"
#include "process_combo.h"
#include "action_tapping.h"


extern combo_t  key_combos[];
extern uint16_t COMBO_LEN;

__attribute__((weak)) void process_combo_event(uint16_t combo_index, bool pressed) {}

#ifdef COMBO_MUST_HOLD_PER_COMBO
__attribute__((weak)) bool get_combo_must_hold(uint16_t index, combo_t *combo) { return false; }
#endif

#ifdef COMBO_TERM_PER_COMBO
__attribute__((weak)) uint16_t get_combo_term(uint16_t index, combo_t *combo) { return COMBO_TERM; }
#endif

static uint16_t timer                 = 0;
static bool     b_combo_enable        = true;  // defaults to enabled
static uint16_t longest_term          = 0;

typedef struct {
    keyrecord_t record;
    uint16_t combo_index;
    uint16_t keycode;
} queued_record_t;
static uint8_t key_buffer_write = 0;
static uint8_t key_buffer_read = 0;
static queued_record_t key_buffer[MAX_COMBO_LENGTH];

typedef struct {
    uint16_t combo_index;
} queued_combo_t;
static uint8_t combo_buffer_write= 0;
static uint8_t combo_buffer_read = 0;
static queued_combo_t combo_buffer[MAX_COMBO_LENGTH];

#define INCREMENT_MOD(i) i = (i + 1) % MAX_COMBO_LENGTH

#define COMBO_KEY_POS ((keypos_t){.col=254, .row=254})

static inline void release_combo(uint16_t combo_index, combo_t *combo) {
    if (combo->keycode) {
        keyrecord_t record = {
            .event = {
                .key = COMBO_KEY_POS,
                .time = timer_read()|1,
                .pressed = false,
            },
            .keycode = combo->keycode,
        };
#ifndef NO_ACTION_TAPPING
        action_tapping_process(record);
#else
        process_record(record);
#endif
    } else {
        process_combo_event(combo_index, false);
    }
    combo->active = false;
}

static inline bool _get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
#if defined(COMBO_MUST_HOLD_PER_COMBO)
        return get_combo_must_hold(combo_index, combo);
#elif defined(COMBO_MUST_HOLD_MODS)
        return KEYCODE_IS_MOD(combo->keycode);
#endif
}

static inline uint16_t _get_combo_term(uint16_t combo_index, combo_t *combo) {

#if defined(COMBO_TERM_PER_COMBO)
        return get_combo_term(combo_index, combo);
#else
        if (_get_combo_must_hold(combo_index, combo)) {
            return COMBO_MOD_TERM
        }
#endif

    return COMBO_TERM;
}

void clear_combos(void) {
    uint16_t index = 0;
    longest_term = 0;
    for (index = 0; index < COMBO_LEN; ++index) {
        combo_t *combo = &key_combos[index];
        if (!combo->active) {
            combo->disabled = false;
            combo->state = 0;
        }
    }
}

static inline void dump_key_buffer(void) {
    if (key_buffer_read == key_buffer_write) {
        return;
    }

    for (uint8_t key_buffer_i = key_buffer_read;
            key_buffer_i != key_buffer_write;
            INCREMENT_MOD(key_buffer_i)
        ) {

        queued_record_t *qrecord = &key_buffer[key_buffer_i];
        keyrecord_t *record = &qrecord->record;

        if (IS_NOEVENT(record->event)) {
            continue;
        }

        if (!record->keycode && qrecord->combo_index != (uint16_t)-1) {
            process_combo_event(qrecord->combo_index, true);
        } else {
#ifndef NO_ACTION_TAPPING
        action_tapping_process(*record);
#else
        process_record(record);
#endif
        }
        record->event.time = 0;
    }

    key_buffer_read = key_buffer_write;
}

#define NO_COMBO_KEYS_ARE_DOWN (0 == combo->state)
#define ALL_COMBO_KEYS_ARE_DOWN(state, key_count) (((1 << key_count) - 1) == state)
#define ONLY_ONE_KEY_IS_DOWN(state) !(state & (state - 1))
#define KEY_NOT_YET_RELEASED(state, key_index) ((1 << key_index) & state)
#define KEY_STATE_DOWN(state, key_index) \
    do {                                 \
        state |= (1 << key_index);       \
    } while (0)
#define KEY_STATE_UP(state, key_index) \
    do {                               \
        state &= ~(1 << key_index);    \
    } while (0)

static inline void _find_key_index_and_count(const uint16_t *keys, uint16_t keycode, uint16_t *key_index, uint8_t *key_count) {
    while (true) {
        uint16_t key = pgm_read_word(&keys[*key_count]);
        if (keycode == key) *key_index = *key_count;
        if (COMBO_END == key) break;
        (*key_count)++;
    }
}

void drop_combo_from_buffer(uint16_t combo_index) {
    /* Mark a combo as processed from the buffer. I the buffer is in the
     * beginning of the buffer, drop it.  */
    uint8_t i = combo_buffer_read;
    while (i != combo_buffer_write) {
        queued_combo_t *qcombo = &combo_buffer[i];

        if (qcombo->combo_index == combo_index) {
            combo_t *combo = &key_combos[combo_index];
            combo->disabled = true;

            if (i == combo_buffer_read) {
                INCREMENT_MOD(combo_buffer_read);
            }
            break;
        }
        INCREMENT_MOD(i);
    }
}

void apply_combo(uint16_t combo_index, combo_t *combo) {
    /* Apply combo's result keycode to the last chord key of the combo and
     * disable the other keys. */

    // state to check against so we find the last key of the combo from the buffer
#if defined(EXTRA_EXTRA_LONG_COMBOS)
    uint32_t state = 0;
#elif defined(EXTRA_LONG_COMBOS)
    uint16_t state = 0;
#else
    uint8_t state = 0;
#endif

    for (uint8_t key_buffer_i = key_buffer_read;
            key_buffer_i != key_buffer_write;
            INCREMENT_MOD(key_buffer_i)
        ) {

        queued_record_t *qrecord = &key_buffer[key_buffer_i];
        keyrecord_t *record = &qrecord->record;
        uint16_t keycode = qrecord->keycode;

        combo_t *combo = &key_combos[combo_index];
        if (combo->disabled) {
            continue;
        }

        uint8_t key_count = 0;
        uint16_t key_index = -1;
        _find_key_index_and_count(combo->keys, keycode, &key_index, &key_count);

        if (-1 == (int16_t)key_index) {
            // key not part of this combo
            continue;
        }

        KEY_STATE_DOWN(state, key_index);
        if (ALL_COMBO_KEYS_ARE_DOWN(state, key_count)) {
            // this in the end executes the combo when the key_buffer is dumped.
            record->keycode = combo->keycode;
            record->event.key = COMBO_KEY_POS;

            qrecord->combo_index = combo_index;
            combo->active = true;

            break;
        } else {
            // key was part of the combo but not the last one, "disable" it
            // by making it a TICK event.
            record->event.time = 0;
        }

    }
    drop_combo_from_buffer(combo_index);
}

void apply_combos(void) {
    for (uint8_t i = combo_buffer_read;
            i != combo_buffer_write;
            INCREMENT_MOD(i)) {

        queued_combo_t *buffered_combo = &combo_buffer[i];
        combo_t *combo = &key_combos[buffered_combo->combo_index];

        apply_combo(buffered_combo->combo_index, combo);
    }
    dump_key_buffer();
    clear_combos();
}

combo_t* overlaps(combo_t *combo1, combo_t *combo2) {
    /* Checks if the combos overlap and returns the combo that should be
     * dropped from the combo buffer.
     * The combo that has less keys will be dropped. If they have the same
     * amount of keys, drop combo1. */

    uint8_t idx1 = 0, idx2 = 0;
    uint16_t key1, key2;
    bool overlaps = false;

    while ((key1 = pgm_read_word(&combo1->keys[idx1])) != COMBO_END) {
        idx2 = 0;
        while ((key2 = pgm_read_word(&combo2->keys[idx2])) != COMBO_END) {
            if (key1 == key2) overlaps = true;
            idx2 += 1;
        }
        idx1 += 1;
    }

    if (!overlaps) return NULL;
    if (idx2 < idx1) return combo2;
    return combo1;
}

static bool process_single_combo(combo_t *combo, uint16_t keycode, keyrecord_t *record, uint16_t combo_index) {
    uint8_t key_count = 0;
    uint16_t key_index = -1;
    _find_key_index_and_count(combo->keys, keycode, &key_index, &key_count);

    /* Continue processing if key isn't part of current combo. */
    if (-1 == (int16_t)key_index) {
        return false;
    }

    bool key_is_part_of_combo = !combo->disabled;

    if (record->event.pressed && !combo->disabled) {
        uint16_t time = _get_combo_term(combo_index, combo);
        if (!combo->active) {
            KEY_STATE_DOWN(combo->state, key_index);
            if (longest_term < time) {
                longest_term = time;
            }
        }
        if (ALL_COMBO_KEYS_ARE_DOWN(combo->state, key_count)) {
            /* Combo was fully pressed */
            /* Buffer the combo so we can fire it after COMBO_TERM */

            /* Don't buffer this combo if its combo term has passed. */
            if (timer && timer_elapsed(timer) > time) {
                combo->disabled = true;
            } else {

                // disable readied combos that overlap with this combo
                combo_t *drop = NULL;
                for (uint8_t combo_buffer_i = combo_buffer_read;
                        combo_buffer_i != combo_buffer_write;
                        INCREMENT_MOD(combo_buffer_i)) {

                    queued_combo_t *qcombo = &combo_buffer[combo_buffer_i];
                    combo_t *buffered_combo = &key_combos[qcombo->combo_index];

                    if ((drop = overlaps(buffered_combo, combo))) {
                        drop->disabled = true;
                        if (drop == combo) {
                            // stop checking for overlaps if dropped combo was current combo.
                            break;
                        } else if (combo_buffer_i == combo_buffer_read && drop == buffered_combo) {
                            /* Drop the disabled buffered combo from the buffer if
                             * it is in the beginning of the buffer. */
                            INCREMENT_MOD(combo_buffer_read);
                        }
                    }

                }

                if (drop != combo) {
                    // save this combo to buffer
                    combo_buffer[combo_buffer_write] = (queued_combo_t){
                        .combo_index=combo_index,
                    };
                    INCREMENT_MOD(combo_buffer_write);
                }
            } // if timer elapsed end

        }
    } else {
        // chord releases
        if (!combo->active && ALL_COMBO_KEYS_ARE_DOWN(combo->state, key_count)) {
            /* First key quickly released */
            if (combo->disabled || _get_combo_must_hold(combo_index, combo)) {
                // combo wasn't tappable, disable it and drop it from buffer.
                drop_combo_from_buffer(combo_index);
                key_is_part_of_combo = false;
            }
        } else if (combo->active
                && ONLY_ONE_KEY_IS_DOWN(combo->state)
                && KEY_NOT_YET_RELEASED(combo->state, key_index)
                ) {
            /* last key released */
            release_combo(combo_index, combo);
            key_is_part_of_combo = true;

        } else if (combo->active
                && KEY_NOT_YET_RELEASED(combo->state, key_index)
                ) {
            /* first or middle key released */
            key_is_part_of_combo = true;

        } else {
            /* The released key was part of an incomplete combo */
            key_is_part_of_combo = false;
        }

        KEY_STATE_UP(combo->state, key_index);
    }

    return key_is_part_of_combo;
}

bool process_combo(uint16_t keycode, keyrecord_t *record) {
    bool is_combo_key          = false;
    bool no_combo_keys_pressed = true;

    if (keycode == CMB_ON && record->event.pressed) {
        combo_enable();
        return true;
    }

    if (keycode == CMB_OFF && record->event.pressed) {
        combo_disable();
        return true;
    }

    if (keycode == CMB_TOG && record->event.pressed) {
        combo_toggle();
        return true;
    }

    if (!is_combo_enabled()) {
        return true;
    }

    for (uint16_t idx = 0; idx < COMBO_LEN; ++idx) {
        combo_t *combo = &key_combos[idx];
        is_combo_key |= process_single_combo(combo, keycode, record, idx);
        no_combo_keys_pressed = no_combo_keys_pressed && (NO_COMBO_KEYS_ARE_DOWN || combo->active || combo->disabled);
    }

    if (record->event.pressed && is_combo_key) {
#ifdef COMBO_STRICT_TIMER
        if (!timer) {
            // timer is set only on the first key
            timer = timer_read();
        }
#else
        timer = timer_read();
#endif

        key_buffer[key_buffer_write] = (queued_record_t){
            .record = *record,
            .keycode = keycode,
            .combo_index = -1, // this will be set when applying combos
        };
        INCREMENT_MOD(key_buffer_write);
    } else {
        if (combo_buffer_read != combo_buffer_write) {
            // some combo is prepared
            apply_combos();
        } else {
            // reset state if there are no combo keys pressed at all
            dump_key_buffer();
            timer = 0;
            clear_combos();
        }
    }
    return !is_combo_key;
}

void matrix_scan_combo(void) {
    if (!b_combo_enable || !timer) {
        return;
    }

    if (timer_elapsed(timer) > longest_term) {
        if (combo_buffer_read != combo_buffer_write) {
            apply_combos();
            longest_term = 0;
            timer = 0;
        } else {
            dump_key_buffer();
            timer = 0;
            clear_combos();
        }
    }
}

void combo_enable(void) { b_combo_enable = true; }

void combo_disable(void) {
    b_combo_enable = false;
    timer                      = 0;
    combo_buffer_read = combo_buffer_write;
    dump_key_buffer();
}

void combo_toggle(void) {
    if (b_combo_enable) {
        combo_disable();
    } else {
        combo_enable();
    }
}

bool is_combo_enabled(void) { return b_combo_enable; }

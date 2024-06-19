
#include "winternebs.h"
// #include "g/keymap_combo.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

const uint16_t PROGMEM qesc[]   = {KC_SPC, KC_Q, COMBO_END};      //    KC_ESC,
const uint16_t PROGMEM deleto[] = {KC_SPC, HOME_A, COMBO_END};    //  KC_DEL,
const uint16_t PROGMEM iqt[]    = {KC_BSPC, HOME_I, COMBO_END};   // KC_QUOT,
const uint16_t PROGMEM bsl[]    = {KC_BSPC, KC_SLSH, COMBO_END};  // KC_BSLS,
const uint16_t PROGMEM btick[]  = {KC_SPC, KC_Z, COMBO_END};      //    KC_GRV,
                                                                  //
combo_t key_combos[] = {
    COMBO(qesc, KC_ESC), COMBO(deleto, KC_DEL), COMBO(iqt, KC_QUOT), COMBO(bsl, KC_BSLS), COMBO(btick, KC_GRV),
};

#ifdef CONSOLE_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uprintf("0x%04X,%u,%u,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state));
        uprintf("%u", _GAME);
    }
    return true;
}
#endif
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("%u", get_highest_layer(layer_state | default_layer_state));
    uprintf("%u", _GAME);
#endif
    if (layer_state_cmp(get_highest_layer(layer_state | default_layer_state), _GAME)) {
        return false;
    }

    return true;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    /*
    enable_combo();
    if (layer_state_cmp(state, _GAME)) {
        disable_combo();
    }*/
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            return false;
        default:
            return true;
    }
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_S:
        case HOME_O:
        case HOME_I:
            return TAPPING_TERM + 50;
        case LOWER:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}
/**
 * TODO:
 * Mouse keys?
 * Game layer
 * move <> onto symbol layers?
 * replace < > with '"
 * replace q ?
 */

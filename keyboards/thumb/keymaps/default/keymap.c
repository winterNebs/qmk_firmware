// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "analog.h"

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(GP26, 0, 512, 1023), JOYSTICK_AXIS_IN(GP27, 0, 512, 819), // bad print LOL
};
enum layers { _DEF = 0, _DL, _RL, _NUM };
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     *     ┌───┬───┬───┬───┐
     * ┌───┤ Q │ W │ E │ R │
     * │TAB├───┼───┼───┼───┤   W
     * ├───┤ A │ S │ D │ F │ A   D
     * │Shf├───┼───┼───┼───┤   S
     * ├───┤ Z │ X │ C │ V │
     * │Ctl├───┼───┼───┼───┘
     * └───┤ESC│   │NUM│   ENT
     *     └───┴───┴───┘
     */
    [_DEF] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_E, KC_R,
                KC_LSFT, KC_A, KC_S, KC_D, KC_F,
                KC_LCTL, KC_Z, KC_X, KC_C, KC_V,
                      KC_ESC, KC_SPC, MO(_NUM), KC_ENT),
    /*
     * ┌───┬───┬───┬───┬───┐
     * │TAB│ Q │ 2 │ E │ R │
     * ├───┼───┼───┼───┼───┤   W
     * │Shf│ 1 │SPC│ 3 │ F │ A   D
     * ├───┼───┼───┼───┼───┤   S
     * │Ctl│ Z │ X │ C │ V │
     * └───┼───┼───┼───┼───┤
     *     │ESC│   │NUM│   │
     *     └───┴───┴───┴───┘
     */
    [_DL] = LAYOUT(KC_TAB, KC_Q, KC_2, KC_E, KC_R,
                KC_LSFT, KC_1, KC_SPC, KC_3, KC_F,
                KC_LCTL, KC_Z, KC_X, KC_C, KC_V,
                      KC_ESC, _______, _______,_______),
    /*
     *     ┌───┬───┬───┬───┐
     * ┌───┤ ^ │R_T│R_S│ △ │
     * │ ≡ ├───┼───┼───┼───┤  LS_X
     * ├───┤ v │L_T│L_S│ ○ │
     * │ < ├───┼───┼───┼───┤  LS_Y
     * ├───┤ > │RIN│ ◻ │ x │
     * │⌥  ├───┼───┼───┼───┘
     * └───┤ ⇒ │ ⌂ │NUM│   LIN
     *     └───┴───┴───┘
     *     Controller
     *      L_SHLD      R_SHLD
     *      L_TRGR      R_TRGR
     *
     *      ⌥  ≡
     *      ⌂ ⇒
     *
     *      DP_U DP_R     △
     *      DP_L DP_D   ◻   ○
     *                    x
     *
     *      LS_X        RS_X
     *      LS_IN       RS_IN
     *      LS_Y        RS_Y
     *
     */
    [_RL] = LAYOUT(JS_0, JS_1, JS_2, JS_3, JS_4,
                    JS_5, JS_6, JS_7, JS_8, JS_9,
                    JS_10, JS_11, JS_12, JS_13, JS_14,
                    JS_15, JS_16, _______, JS_17),

    [_NUM] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5,
                DF(_DL), _______, _______, _______, _______,
                DF(_DEF), _______, _______, _______, _______,
                      DF(_RL),_______, _______, _______ )

    // clang-format on
};
// Firmware inspired by joshinator.de
bool    wasdMode = false;
int16_t xPos     = 0;
int16_t yPos     = 0;

#define _MID 512
#define _DEAD 75
#define _DOWN (_MID - _DEAD)
#define _UP (_MID + _DEAD)

void matrix_scan_user(void) {
    if (wasdMode) {
        // W & S
        xPos = analogReadPin(GP26);
        yPos = analogReadPin(GP27);

        // DOWN --- DEAD ZONE --- UP
        if (yPos >= _UP) {
            register_code(KC_W);
            unregister_code(KC_S);
        } else if (yPos <= _DOWN) {
            register_code(KC_S);
            unregister_code(KC_W);
        } else {
            unregister_code(KC_S);
            unregister_code(KC_W);
        }
        if (xPos >= _UP) {
            register_code(KC_A);
            unregister_code(KC_D);
        } else if (xPos <= _DOWN) {
            register_code(KC_D);
            unregister_code(KC_A);
        } else {
            unregister_code(KC_D);
            unregister_code(KC_A);
        }
    }
}
layer_state_t default_layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _DL:
            wasdMode = true;
            break;
        default:
            wasdMode = false;
            break;
    }
    return state;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {}
    }
    return true;
}

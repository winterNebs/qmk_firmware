// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "analog.h"

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(GP26, 0, 512, 1023),
    JOYSTICK_AXIS_IN(GP27, 0, 512, 1023),
};
enum layers {
    _DEF,
    _DL,
    _RL,
    _NUM,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * ┌───┬───┬───┬───┬───┐
     * │Esc│ Q │ W │ E │ R │
     * ├───┼───┼───┼───┼───┤   W
     * │Shf│ A │ S │ D │ F │ A   D
     * ├───┼───┼───┼───┼───┤   S
     * │Ctl│ Z │ X │ C │ V │
     * └───┼───┼───┼───┼───┤
     *     │Tab│NUM│Spc│   │
     *     └───┴───┴───┴───┘
     */
    [_DEF] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R,
                KC_LSFT, KC_A, KC_S, KC_D, KC_F,
                KC_LCTL, KC_Z, KC_X, KC_C, KC_V,
                      KC_TAB, MO(_NUM), KC_SPC, KC_ENT),
    /*
     * ┌───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ R │
     * ├───┼───┼───┼───┼───┤   W
     * │Shf│   │   │SPC│ F │ A   D
     * ├───┼───┼───┼───┼───┤   S
     * │Ctl│ Z │ X │ C │ V │
     * └───┼───┼───┼───┼───┤
     *     │Tab│NUM│Spc│   │
     *     └───┴───┴───┴───┘
     */
    [_DL] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R,
                KC_LSFT, KC_A, KC_S, KC_D, KC_F,
                KC_LCTL, KC_Z, KC_X, KC_C, KC_V,
                      KC_TAB, MO(_NUM), KC_SPC, KC_SPC),
    /*
     * ┌───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ R │
     * ├───┼───┼───┼───┼───┤   W
     * │Shf│   │   │SPC│ F │ A   D
     * ├───┼───┼───┼───┼───┤   S
     * │Ctl│ Z │ X │ C │ V │
     * └───┼───┼───┼───┼───┤
     *     │Tab│NUM│Spc│   │
     *     └───┴───┴───┴───┘
     */
    [_RL] = LAYOUT(JS_0, JS_1, JS_2, JS_3, JS_4,
                    JS_5, JS_6, JS_7, JS_8, JS_9,
                    JS_10, JS_11, JS_12, JS_13, JS_14,
                    JS_15, MO(_NUM), JS_16, JS_17),

    [_NUM] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5,
                _______, _______, _______, _______, _______,
                DF(_DEF), _______, _______, _______, _______,
                      DF(_RL), MO(_NUM), KC_SPC, KC_SPC)

    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {}
    }
    return true;
}

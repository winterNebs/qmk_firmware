#include "winternebs.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Keymap 0: Alpha layer
     *
     * ,-----------------------------.        ,-----------------------------.
     * |  Q  |  D  |  R  |  W  |  B  |        |  J  |  F  |  U  |  P  |  ;  |
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |GUI/A|ALT/S|CTL/H|SFT/F|  G  |        |  Y  |SFT/N|CTL/E|ALT/O|GUI/I|
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |  Z  |  X  |  M  |  C  |  V  |        |  K  |  L  |  ,  |  .  |  /  |
     * `-----------------------------'        `-----------------------------'
     *   .-------------------.        .------------------.
     *   | TAB/LOWER | SPACE |        | BKSP | ENT/RAISE |
     *   '-------------------'        '------------------'
     */
    [_ALPHA] = LAYOUT_ferris_wrapper(_________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
                                    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
                                    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________,
                                    ____THUMB_L____, ____THUMB_R____),

    /* Keymap 1: Lower layer
     *
     * ,-----------------------------.        ,-----------------------------.
     * |  1  |  2  |  3  |  4  |  5  |        |  6  |  7  |  8  |  9  |  0  |
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |  $  |  +  |  (  |   )  |  @  |        |  |  |  -  |  =  |  _  |  *  |
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |  !  |  #  |  {  |   }  |  ~  |        |  &  |  [  |   ]  |  %  |  ^  |
     * `-----------------------------'        `-----------------------------'
     *    .--------------------------.        .----------------------.
     *    |   `   |       | printscr |        |      |     |    \    |
     *    '--------------------------'        '----------------------'
     */
    [_LOWER] = LAYOUT_ferris_wrapper(_________________SYMBOL_L1_________________, _________________SYMBOL_R1_________________,
                                    _________________SYMBOL_L2_________________, _________________SYMBOL_R2_________________,
                                    _________________SYMBOL_L3_________________, _________________SYMBOL_R3_________________,
                                    _______, KC_PSCR, _______, _______),

    /* Keymap 2: Pad/Function layer
     * ,-----------------------------.          ,-----------------------------.
     * |     |     |     |Word |Back |          |Down |     |     |     |     |
     * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
     * |Appen|     |Right|     |     |          |     |     | End |     |     |
     * |-----+-----+-----+-----+-----|       |-----+-----+-----+-----+-----|
     * |     |     |     |     |     |          | Up  |Left |     |     |     |
     * `-----------------------------'       `-----------------------------'
     *             .-----------------.        .-----------------.
     *             |     |    |      |   |     |     |     |
     *             '-----------------'        '-----------------'
     */
    [_RAISE] = LAYOUT_ferris_wrapper(_________________NAV_L1____________________, _________________NAV_R1____________________,
                                    _________________NAV_L2____________________, _________________NAV_R2____________________,
                                    _________________NAV_L3____________________, _________________NAV_R3____________________,
                                    _______, _______, _______, _______),

    /* Keymap 3: Pad/Function layer
     * ,-----------------------------.          ,-----------------------------.
     * | F1  | F2  | F3  | F4  | F5  |          | F6  | F7  | F8  | F9  | F10 |
     * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
     * | F11 |     |     |     |     |          |     |     |     |     | F12 |
     * |-----+-----+-----+-----+-----|       |-----+-----+-----+-----+-----|
     * |     |     |     | Wrk | Gm  |          |     |     |     |     |     |
     * `-----------------------------'       `-----------------------------'
     *             .-----------------.        .-----------------.
     *             |     |    |      |   |     |     |     |
     *             '-----------------'        '-----------------'
     */
    [_ADJUST] = LAYOUT_ferris_wrapper(_________________ADJUST_L1_________________, _________________ADJUST_R1_________________,
                                        _________________ADJUST_L2_________________, _________________ADJUST_R2_________________,
                                        _________________ADJUST_L3_________________, _________________ADJUST_R3_________________,
                                        _______, _______, _______, _______),
    /* Keymap 2: Pad/Function layer
     * ,-----------------------------.          ,-----------------------------.
     * |     |     |     |     |     |          |     | LMB |  ^  | RMB |     |
     * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
     * |     |     |     |     |     |          |     |  <  |  v  |  >  |     |
     * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
     * |     |     |     |     |     |          |     |     |     |     |     |
     * `-----------------------------'          `-----------------------------'
     *             .-----------------.        .-----------------.
     *             |     |    |      |        |    |     |     |
     *             '-----------------'        '-----------------'
     */
    [_MOUSE] = LAYOUT_ferris_wrapper(_______, _______, _______, _______, _______, _______, _________MOUSE_1_________, _______,
                                    _______, _______, _______, _______, _______, _______, _________MOUSE_2_________, _______,
                                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                    _______, _______, _______, _______),

    /* Keymap 4: Basic layer
     *
     * ,-----------------------------.       ,----------------------------.
     * | Esc |  Q  |  W  |  E  |  R  |      |  T  |  Y  |  U  |  I  |  O  |
     * |-----+-----+-----+-----+-----|      |-----------------------------|
     * | Tab |  A  |  S  |  D  |  F  |      |  G  |  H  |  J  |  K  |  L  |
     * |-----+-----+-----+-----+-----+      |-----------------------------|
     * | Ctrl|  Z  |  X  |  C  |  V  |      |  B  |  N  |  M  |  <  |  P  |
     * `-----+-----+-----+------+----'       `----------------------------'
     *  .-------------------------.           .-----------------.
     *  |  ALT  |  Num   | Space  |           | BKSP | SYM | ?  |
     *  '-------------------------'           '-----------------'
     */
    [_GAME] = LAYOUT_ferris_wrapper(KC_ESC, _________________QWERTY_L1_________________, ______________GAME_R1_____________,
                                    KC_LSFT, _________________QWERTY_L2_________________, ______________GAME_R2_____________,
                                    KC_LCTL, _________________QWERTY_L3_________________, ______________GAME_R3_____________,
                                    ____THUMB_L____, ____THUMB_R____),

    /* Keymap 2: Pad/Function layer
     * ,-----------------------------.          ,-----------------------------.
     * |     |     |     |     |     |          |     |     |     |     |     |
     * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
     * |     |     |     |     |     |          |     |     |     |     |     |
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |     |     |     |     |     |          |     |     |     |     |     |
     * `-----------------------------'        `-----------------------------'
     *              .-----------------.        .-----------------.
     *           |     |    |      |   |     |     |     |
     *            '-----------------'        '-----------------'
     */
    [_OSRS] = LAYOUT_ferris_wrapper( _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                                    C(KC_KP_8), KC_KP_5, C(KC_KP_2), KC_KP_5,   _______, _______,KC_KP_5,C(KC_KP_8), KC_KP_5,_______ ,
                                    KC_NLCK, _______  ,_______,_______,_______,_______, _______,_______,_______,_______,
                                    ____THUMB_L____, ____THUMB_R____)

    /* Keymap 2: Pad/Function layer
     * ,-----------------------------.          ,-----------------------------.
     * |     |     |     |     |     |          |     |     |     |     |     |
     * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
     * |     |     |     |     |     |          |     |     |     |     |     |
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |     |     |     |     |     |          |     |     |     |     |     |
     * `-----------------------------'        `-----------------------------'
     *              .-----------------.        .-----------------.
     *           |     |    |      |   |     |     |     |
     *            '-----------------'        '-----------------'
     */
};

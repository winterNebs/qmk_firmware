/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "keymap.h"

enum layers{
    _ALPHA = 0,   // default
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME
};
enum custom_keycodes {
    ENDW  = SAFE_RANGE
};


// Blank template at the bottom
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
     *   .---------------------------.        .------------------------.
     *   |  ESC  | TAB/LOWER | SPACE |        | BKSP | ENT/RAISE | '   |
     *   '---------------------------'        '------------------------'
     */
    [_ALPHA] = LAYOUT_gergoplex(
         KC_Q,  KC_D, KC_R, KC_W, KC_B,        KC_J, KC_F, KC_U, KC_P, KC_SCLN,
       HOME_A,HOME_S,HOME_H,HOME_T,KC_G,       KC_Y,HOME_N,HOME_E,HOME_O,HOME_I,
         KC_Z,  KC_X, KC_M, KC_C, KC_V,        KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH,
            KC_ESC, LOWER, KC_SPC ,            KC_BSPC, RAISE, KC_QUOT ),

    /* Keymap 1: Lower layer
     *
     * ,-----------------------------.        ,-----------------------------.
     * |  1  |  2  |  3  |  4  |  5  |        |  6  |  7  |  8  |  9  |  0  |
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |  $  |  +  |  (  |  )  |  @  |        |  |  |  -  |  =  |  _  |  *  |
     * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
     * |  !  |  #  |  {  |  }  |  ~  |        |  &  |  [  |  ]  |  %  |  ^  |
     * `-----------------------------'        `-----------------------------'
     *    .--------------------------.        .----------------------.
     *    |   `   |       | printscr |        |      |     |    \    |
     *    '--------------------------'        '----------------------'
     */
    [_LOWER] = LAYOUT_gergoplex(
	 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    
     KC_DLR,  KC_PLUS, KC_LPRN, KC_RPRN, KC_AT,     KC_PIPE, KC_MINS, KC_EQL,  KC_UNDS, KC_ASTR,
     KC_EXLM, KC_HASH, KC_LCBR, KC_RCBR, KC_TILD,   KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, KC_CIRC, 
		                KC_GRV,	_______, KC_PSCR,   _______, _______, KC_BSLS),

/* Keymap 2: Pad/Function layer
 * ,-----------------------------.          ,-----------------------------.
 * |     |     |     |Word |Back |          |Down |     |     |     |     |
 * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
 * |Appen|     |Right|     |     |          |     |     | End |     |     |
 * |-----+-----+-----+-----+-----|	        |-----+-----+-----+-----+-----|
 * |     |     |     |     |     |          | Up  |Left |     |     |     |
 * `-----------------------------'	        `-----------------------------'
 *      		.-----------------.        .-----------------.   
 *  			|     |    |      |		   |     |     |     |
 *      		'-----------------'        '-----------------' 
 */
[_RAISE] = LAYOUT_gergoplex(
    _______, _______, _______, C(KC_RGHT), C(KC_LEFT),      KC_DOWN, _______, _______, _______, _______,
    KC_END,  _______, KC_LEFT, _______, _______,   _______, _______, ENDW,    _______, _______,
    _______, _______, _______, _______, _______,   KC_UP,   KC_RGHT, _______, _______, _______,
    _______, _______, _______,      _______, _______, _______
        ),

/* Keymap 3: Pad/Function layer
 * ,-----------------------------.          ,-----------------------------.
 * | F1  | F2  | F3  | F4  | F5  |          | F6  | F7  | F8  | F9  | F10 |
 * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
 * | F11 |     |     |     |     |          |     |     |     |     | F12 | 
 * |-----+-----+-----+-----+-----|	        |-----+-----+-----+-----+-----|
 * |     |     |     | Wrk | Gm  |          |     |     |     |     |     |
 * `-----------------------------'	        `-----------------------------'
 *      		.-----------------.        .-----------------.   
 *  			|     |    |      |		   |     |     |     |
 *      		'-----------------'        '-----------------' 
 */
[_ADJUST] = LAYOUT_gergoplex(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_F11,  _______, _______, _______, _______,   _______, _______, _______,    _______, KC_F12,
    _______, _______, _______, DF(_ALPHA), DF(_GAME),   _______,   _______, _______, _______, _______,
    _______, _______, _______,      _______, _______, _______
        ),

/* Keymap 4: Basic layer
 *
 * ,-----------------------------.       ,----------------------------.
 * | Esc |  Q  |  W  |  E  |  R  |      |  T  |  Y  |  U  |  I  |  O  |
 * |-----+-----+-----+-----+-----|      |-----------------------------|
 * | Tab |  A  |  S  |  D  |  F  |      |  G  |  H  |  J  |  K  |  L  | 
 * |-----+-----+-----+-----+-----+		|-----------------------------|
 * | Ctrl|  Z  |  X  |  C  |  V  |      |  B  |  N  |  M  |  <  |  P  | 
 * `-----+-----+-----+------+----'		 `----------------------------'
 *  .-------------------------.           .-----------------.   
 *  |  ALT  |  Num   | Space  |           | BKSP | SYM | ?  |
 *  '-------------------------'           '-----------------' 
 */
[_GAME] = LAYOUT_gergoplex(
    KC_ESC, KC_Q, KC_W, KC_E, KC_R,     KC_T, KC_Y, KC_U, KC_I,    KC_O, 	  
    KC_TAB, KC_A, KC_S, KC_D, KC_F,     KC_G, KC_H, KC_J, KC_K,    KC_L, 	 
    KC_LCTL, KC_Z,KC_X, KC_C, KC_V,     KC_B, KC_N, KC_M, KC_COMM, KC_P, 

 		KC_LALT, MO(_LOWER), KC_SPC,									// Left
		KC_BSPC, MO(_RAISE), KC_LSFT																// Right
    )
/* Keymap 2: Pad/Function layer
 * ,-----------------------------.          ,-----------------------------.
 * |     |     |     |     |     |          |     |     |     |     |     |
 * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
 * |     |     |     |     |     |          |     |     |     |     |     |
 * |-----+-----+-----+-----+-----|	        |-----+-----+-----+-----+-----|
 * |     |     |     |     |     |          |     |     |     |     |     |
 * `-----------------------------'	        `-----------------------------'
 *      		.-----------------.        .-----------------.   
 *  			|     |    |      |		   |     |     |     |
 *      		'-----------------'        '-----------------' 
 */
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed) {
        switch (keycode){
            case ENDW:
                register_code(KC_LCTL);
                tap_code(KC_RGHT);
                unregister_code(KC_LCTL);
                tap_code(KC_LEFT);
                return false;
        }
    }
    return true;
 }
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
/**
 * TODO:
 * Mouse keys?
 * Game layer
 * move <> onto symbol layers?
 * replace < > with '"
 * replace q ? 
 */

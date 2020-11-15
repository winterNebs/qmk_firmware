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
    _RAISE
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
    KC_END,  _______, KC_RGHT, _______, _______,   _______, _______, ENDW,    _______, _______,
    _______, _______, _______, _______, _______,   KC_UP,   KC_LEFT, _______, _______, _______,
    _______, _______, _______,      _______, _______, _______
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
/**
 * TODO:
 * Mouse keys?
 * Use combos?
 * Find better spot for esc key?
 * Game layer
 * move <> onto symbol layers?
 * replace < > with '"
 * need a delete key somewhere
 * change mod tap esttings  
 * replace q ? 
 * fkeys
 */

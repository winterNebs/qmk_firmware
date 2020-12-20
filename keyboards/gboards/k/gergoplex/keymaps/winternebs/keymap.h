#include QMK_KEYBOARD_H 
#define RAISE LT(_RAISE, KC_ENT)
#define LOWER LT(_LOWER, KC_TAB)
#define MOUSE TG(_MOUSE)
#define HOME_A GUI_T(KC_A)
#define HOME_S ALT_T(KC_S)
#define HOME_H CTL_T(KC_H) 
#define HOME_T SFT_T(KC_T) 
#define HOME_N RSFT_T(KC_N) 
#define HOME_E RCTL_T(KC_E)
#define HOME_O RALT_T(KC_O)
#define HOME_I RGUI_T(KC_I)

typedef enum {
    ENDW  = SAFE_RANGE,
    SAVEI
}custom_keycodes;

# Combos

The Combo feature is a chording type solution for adding custom actions.  It lets you hit multiple keys at once and produce a different effect.  For instance, hitting `A` and `S` within the tapping term would hit `ESC` instead, or have it perform even more complex tasks.

To enable this feature, you need to add `COMBO_ENABLE = yes` to your `rules.mk`.

Additionally, in your `config.h`, you'll need to specify the number of combos that you'll be using, by adding `#define COMBO_COUNT 1` (replacing 1 with the number that you're using). It is also possible to not define this and instead set the variable `COMBO_LEN` yourself. There's a trick where we don't need to think about this variable at all. More on this later.


Then, in your `keymap.c` file, you'll need to define a sequence of keys, terminated with `COMBO_END`, and a structure to list the combination of keys, and its resulting action.

```c
const uint16_t PROGMEM test_combo[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, KC_ESC)};
```

This will send "Escape" if you hit the A and B keys.

As of [PR#8591](https://github.com/qmk/qmk_firmware/pull/8591/), it is possible to fire combos from ModTap keys and LayerTap keys. So in the above example you could have keys `LSFT_T(KC_A)` and `LT(_LAYER, KC_B)` and it would work. So Home Row Mods and Home Row Combos at same time is now a thing!

It is also now possible to overlap combos. Before, with the example below both combos would activate when all three keys were pressed. Now only the three key combo will activate.

```c
const uint16_t PROGMEM test_combo1[] = {LSFT_T(KC_A), LT(_LAYER, KC_B), COMBO_END};
const uint16_t PROGMEM test_combo2[] = {LSFT_T(KC_A), LT(_LAYER, KC_B), KC_C, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(test_combo1, KC_ESC)
    COMBO(test_combo2, KC_TAB)
};
```

Executing more complex keycodes like ModTaps and LayerTaps is now also possible.

## Examples

If you want to add a list, then you'd use something like this:

```c
enum combos {
  AB_ESC,
  JK_TAB,
  QW_SFT,
  SD_LAYER,
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB),
  [QW_SFT] = COMBO(qw_combo, KC_LSFT)
  [SD_LAYER] = COMBO(layer_combo, MO(_LAYER)),
};
```

For a more complicated implementation, you can use the `process_combo_event` function to add custom handling.
Additionally this example shows how you can leave `COMBO_COUNT` undefined.

```c
enum combo_events {
  ZC_COPY,
  XV_PASTE,
  COMBO_LENGTH
};
uint16_t COMBO_COUNT = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[] = {
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case ZC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}
```

This will send Ctrl+C if you hit Z and C, and Ctrl+V if you hit X and V. But you could change this to do stuff like play sounds or change settings.

# Advanced Configuration
These configuration settings can be set in your `config.h` file.

## Keycodes
You can enable, disable and toggle the Combo feature on the fly.  This is useful if you need to disable them temporarily, such as for a game. The following keycodes are avalible for use in your `keymap.c`

|Keycode   |Description                      |
|----------|---------------------------------|
|`CMB_ON`  |Turns on Combo feature           |
|`CMB_OFF` |Turns off Combo feature          |
|`CMB_TOG` |Toggles Combo feature on and off |

## Combo Term
By default, the timeout for the Combos to be recognized is set to 50ms. This can be changed if accidental combo misfires are happening or if you're having difficulties pressing keys at the same time. For instance `#define COMBO_TERM 40` would set the time out period for combos to 40ms.

## Long Combos
If you're using long combos, or you have a lot of overlapping combos, you may run into issues with this, as the structure may not be large enough to accommodate what you're doing. In this case, you can configure the size of the data structure used. Be aware, larger combo sizes will increase memory usage!

| Keys | Define to be set     |
|------|----------------------|
| 8    | QMK Default          |
| 16   | `#define EXTRA_LONG_COMBOS`  |
| 32   | `#define EXTRA_EXTRA_LONG_COMBOS`|

## Modifier Combos
If a combo resolves to a Modifier, the window for processing the combo can be extended independent from normal combos. By default this is disabled but can be enabled with `#define COMBO_MUST_HOLD_MODS`, and the time window can be configured with `#define COMBO_MOD_TERM 150` (default: 200). With `COMBO_MUST_HOLD_MODS` you cannot tap the combo any more which makes the combo less prone to misfires.

## Per Combo Timing and Holding
Instead of using a blanket `COMBO_TERM` window for every combo, per-combo timings can be set. In order to use this feature the following config options and functions need to be defined. Coming up with useful timings and configuration is left as an exercise for the reader.

| Config Flag                 | Function                                                  | Description                                                                                          |
|-----------------------------|-----------------------------------------------------------|------------------------------------------------------------------------------------------------------|
| `COMBO_MUST_HOLD_PER_COMBO` | bool get_combo_must_hold(uint16_t index, combo_t \*combo) | Controls if a given combo should fire immediately on tap or if it needs to be held. (default: False) |
| `COMBO_TERM_PER_COMBO`      | uint16_t get_combo_term(uint16_t index, combo_t \*combo)  | Optional per-combo timeout window. (default: COMBO_TERM)                                             |

If you set either of the options but like the Modifier Combo settings, you have to define those yourself in the function.

Examples:
```c
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    // decide by combo->keycode
    if (KEYCODE_IS_MOD(combo->keycode)) return COMBO_MOD_TERM; // you have to config this yourself if you're using COMBO_TERM_PER_COMBO

    switch (combo->keycode) {
        case KC_X:
            return 50;
    }

    // or with combo index, i.e. its name from enum.
    switch (index) {
        case COMBO_NAME_HERE:
            return 9001;
    }

    // And if you're feeling adventurous, you can even decide by the keys in the chord,
    // i.e. the exact array of keys you defined for the combo.
    // This can be useful if your combos have a common key and you wan't to apply the
    // same combo term for all of them.
    if (combo->keys[0] == KC_ENTER) { // if first key in the array is KC_ENTER
        return 150;
    }

    return COMBO_TERM;
}

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    // yet again, with keycode and true for Modifiers if so desired.
    if (KEYCODE_IS_MOD(combo->keycode)) return true;

    // or index/name
    switch (index) {
        case COMBO_NAME_HERE:
            return true;
    }

    return false;
}
```

## Variable Length Combos
If you leave `COMBO_COUNT` undefined in `config.h`, it allows the you to programmatically declare the size of the Combo data structure and avoid updating COMBO_COUNT. Instead a variable called `COMBO_LEN` has to be set. It can be set with something similar to the following in `keymap.c`: `uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);` or by adding `COMBO_LENGTH` as the *last* entry in the combo enum and then `uint16_t COMBO_LEN = COMBO_LENGTH;` as such:
```c
enum myCombos {
    ...,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
```
Regardless of the method used to declare `COMBO_LEN`, this also requires to convert the `combo_t key_combos[COMBO_COUNT] = {...};` line to `combo_t key_combos[] = {...};`.

## User callbacks

In addition to the keycodes, there are a few functions that you can use to set the status, or check it:

|Function   |Description                                                         |
|-----------|--------------------------------------------------------------------|
| `combo_enable()`     | Enables the combo feature                               |
| `combo_disable()`    | Disables the combo feature, and clears the combo buffer |
| `combo_toggle()`     | Toggles the state of the combo feature                  |
| `is_combo_enabled()` | Returns the status of the combo feature state (true or false) |


# Dictionary Management

Having 3 places to update when adding new combos or altering old ones does become cumbersome when you have a lot of combos. We can alleviate this with some magic! ... If you consider C macros magic. Add the following `my_combos.h` file to your keymap directory or to you user space directory. Then include it in your `keymap.c` file.

```c
#pragma once
#ifdef COMBO_ENABLE

#ifdef COMB
#undef COMB
#endif

#define COMB(name, action, ...)  ##name,
enum myCombos {
#include "combos.def"
    COMBO_LENGTH
};
#undef COMB
uint16_t COMBO_LEN = COMBO_LENGTH;

#define COMB(name, action, ...)  const uint16_t PROGMEM name##_combo[] = {__VA_ARGS__, COMBO_END};
#include "combos.def"
#undef COMB

#define COMB(name, action, ...)  [##name] = COMBO(name##_combo, action),
combo_t key_combos[] = {
#include "combos.def"
};
#undef COMB

#endif
```

Then write you combos in `combos.def` (in the same directory as `my_combos.h`) file in the following manner:

```c
//   name     result    chord keys
COMB(AB_ESC,  KC_ESC,   KC_A, KC_B)
COMB(JK_TAB,  KC_TAB,   KC_J, KC_K)
COMB(JKL_SPC, KC_SPC,   KC_J, KC_K, KC_L)
COMB(ZC_COPY, KC_NO,    KC_Z, KC_C) // using KC_NO as the resulting keycode is the same as COMBO_ACTION before.
...
```

Now you can update just one place to add or alter combos. And you don't even need to think about updating the `COMBO_COUNT` or the `COMBO_LEN` variable at all. Everything is taken care of. Magic!

For small to huge ready made dictionaries of combos, you can check out http://combos.gboards.ca/.

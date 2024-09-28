#pragma once
#define FORCE_NKRO
// Min 0, max 32
#define JOYSTICK_BUTTON_COUNT 18
// Min 0, max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_COUNT 2
// Min 8, max 16
#define JOYSTICK_AXIS_RESOLUTION 12
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1500U // Timeout window in ms in which the double tap can occur.


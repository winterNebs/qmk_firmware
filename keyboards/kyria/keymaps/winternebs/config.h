/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#pragma once

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#define OLED_FONT_H "keyboards/kyria/keymaps/winternebs/glcdfont.c"
=======
#define OLED_FONT_H "keyboards/kyria/keymaps/winterNebs/glcdfont.c"
>>>>>>> Rename to lowercase
=======
#define OLED_FONT_H "keyboards/kyria/keymaps/winternebs/glcdfont.c"
>>>>>>> fix oled path
=======
#define OLED_FONT_H "keyboards/kyria/keymaps/winternebs/glcdfont.c"
>>>>>>> b02d6a4300ef26ff580e2c4ab6284a529ea0bc10
#define OLED_FONT_END 127
#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#define FORCE_NKRO
#define ENCODER_RESOLUTION 4

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
#define TAPPING_FORCE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

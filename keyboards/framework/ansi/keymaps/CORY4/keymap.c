// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "framework.h"

//  expanded rgb groupings, used get mods   no layer tracking 

enum _layers {
    _BASE,
    _FN,
    _RGB,
    _FN_L,
    _CAPS,
    _SFT,
    _CTRL,
};

// I could not find an RGB equivalent to the Backlight step brightness code
// so i made my own.
enum CUSTOM_KEYCODES {
    RGB_STEP,
};

// these are variables for RGB_STEP. brite_adj is set initially
// to 255 so the rgb is max brightness when keyboard initializes.
static int brite_adj     = 255;
static int rgb_brite_val = 0;

// variable to switch between per key rgb and animations
static int rgb_switch    = 1;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* ANSI/US RGB keyboard key location to LED Index (Zeroed Values)
*
*   row 1      ┌────────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬──────┬────┬───────┐
*    LED's 17  │  0, 1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │ 10  │ 11  │12, 13│ 14 │15, 16 │
*   row 2      ├─────┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───┴─┬──┴───────┤
*    LED's 15  │ 17  │ 18  │ 19  │ 20  │ 21  │ 22  | 23  │ 24  │ 25  │ 26  │ 27  │ 28  │ 29  │  30, 31  │
*   row 3      ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───────┤
*    LED's 15  │ 32, 33 │ 34  │ 35  │ 36  │ 37  │ 38  │ 39  │ 40  │ 41  │ 42  │ 43  │ 44  │ 45  │  46   │
*   row 4      ├────────┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴───────┤
*    LED's 16  │47, 48, 49│ 50  │ 51  │ 52  │ 53  │ 54  │ 55  │ 56  │ 57  │ 58  │ 59  │ 60  │  61, 62   │
*   row 5      ├──────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────────┤
*    LED's 17  │ 63, 64, 65  │ 66  │ 67  │ 68  │ 69  │ 70  │ 71  │ 72  │ 73  │ 74  │ 75  │76, 77, 78, 79│
*              ├────────┬────┴─┬───┴──┬──┴───┬─┴─────┴─────┴─────┴────┬┴─────┼─────┼─────┴┬──────┬──────┤
*   row 6      │        │      │      │      │                        │      │     │      │  95  │      │
*   LED's 17   │ 80, 81 │  82  │  83  │  84  │ 85, 86, 87, 88, 89, 90 │  91  │ 92  │  93  ├──────┤  96  │
*              │        │      │      │      │                        │      │     │      │  94  │      │
*   TOTAL      └────────┴──────┴──────┴──────┴────────────────────────┴──────┴─────┴──────┴──────┴──────┘
*    LED's: 97
*/

/*             ┌────────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬───────┐
*   14 keys    │ ESCAPE │Mute │VolDn│VolUp│Prevs│Play │Next │LghDn│LghUp│Sceen│Airpl│Print│ App │Delete │
*              ├─────┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───┴─┬──┴───────┤
*   14 keys    │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │Backspace │
*              ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───────┤
*   14 keys    │  Tab   │Q, q │W, w │E, e │R, r │T, t │Y, y │U, u │I, i │O, o │P, p │[, { │], } │ \, |  │
*              ├────────┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴───────┤
*   13 keys    │  Caps    │A, a │S, s │D, d │F, f │G, g │H, h │J, j │K, k │L, l │;, : │', " │    Enter  │
*              ├──────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────────┤
*   12 keys    │  Shift      │Z, z │X, x │C, c │V, v │B, b │N, n │M, m │,, < │., > │/, ? │       Shift  │
*              ├────────┬────┴─┬───┴──┬──┴───┬─┴─────┴─────┴─────┴────┬┴─────┼─────┼─────┴┬──────┬──────┤
*              │        │      │      │      │                        │      │     │      │  ↑   │      │
*   11 keys    │Control │Functn│ GUI  │ Alt  │        SpaceBar        │ Alt  │Cntrl│  ←   ├──────┤   →  │
*              │        │      │      │      │                        │      │     │      │  ↓   │      │
*              └────────┴──────┴──────┴──────┴────────────────────────┴──────┴─────┴──────┴──────┴──────┘
*   78 total
*/

    [_BASE] = LAYOUT(
        KC_ESC,    KC_MUTE,  KC_VOLD,  KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        KC_GRV,    KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,   KC_A,     KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,   KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
        KC_LCTL,   MO(_FN),  KC_LGUI,  KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),

   [_FN] = LAYOUT(
        TG(_FN_L), KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,   _______,  KC_MENU,  _______,          _______,                   _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
   ),

   [_RGB] = LAYOUT(
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   RGB_MOD,  RGB_HUI,  RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   RGB_RMOD, RGB_HUD,  RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______,          _______,
        _______,   QK_BOOT,  RGB_STEP, RGB_TOG, BL_STEP, BL_TOGG, _______, _______, _______, _______, _______,                   _______,
        _______,   _______,  KC_MENU,  _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),

    [_FN_L] = LAYOUT(
        TG(_FN_L), KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,   _______,  _______,  _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),
 
    [_CAPS] = LAYOUT(
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,   _______,  _______,  _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),
 
    [_SFT] = LAYOUT(
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,   _______,  _______,  _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),

    [_CTRL] = LAYOUT(
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,   _______,  _______,  _______,          _______,                   _______, _______, _______, _______, _______, _______
    )
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (IS_LAYER_ON(_FN) && rgb_switch == 1) {
        led_min = 0;
        led_max = 2;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }
        led_min = 2;
        led_max = 17;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 128 * brite_adj / 255, 0);
        }
        led_min = 82;
        led_max = 83;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }
        led_min = 84;
        led_max = 92;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 93;
        led_max = 97;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 128 * brite_adj / 255, 0);
        }

    } else if (IS_LAYER_ON(_FN_L) && IS_LAYER_OFF(_FN) && rgb_switch == 1) {
        led_min = 0;
        led_max = 2;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }
        led_min = 2;
        led_max = 17;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 128 * brite_adj / 255, 0);
        }
        led_min = 84;
        led_max = 92;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 93;
        led_max = 97;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }

    } else if (rgb_switch == 1) {
        led_min = 0;
        led_max = 17;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 84;
        led_max = 92;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 93;
        led_max = 97;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
    }

    if (rgb_switch == 1) {
        led_min = 47;
        led_max = 50;
        if (IS_LAYER_OFF(_CAPS)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
            }
        } else {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
            }
        }

        led_min = 63;
        led_max = 66;
        if (IS_LAYER_OFF(_SFT)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
            }
        } else {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
            }
        }

        led_min = 76;
        led_max = 80;
        if (IS_LAYER_OFF(_SFT)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
            }
        } else {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
            }
        }

        led_min = 80;
        led_max = 82;
        if (IS_LAYER_OFF(_CTRL)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
            }
        } else {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
            }
        }

        led_min = 92;
        led_max = 93;
        if (IS_LAYER_OFF(_CTRL)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
            }
        } else {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
            }
        }

        led_min = 82;
        led_max = 83;
        if (IS_LAYER_OFF(_FN)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
            }
        } else {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
            }
        }

        led_min = 83;
        led_max = 84;
        if (IS_LAYER_OFF(_RGB) && IS_LAYER_ON(_FN)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 36 * brite_adj / 255, 0);
            }
        } else if (IS_LAYER_ON(_RGB)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
            }
        } else {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
            }
        }
    }

    if (get_highest_layer(layer_state) == _BASE && rgb_switch == 1) {
        led_min = 0;
        led_max = 47;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }
        led_min = 50;
        led_max = 63;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }
        led_min = 66;
        led_max = 76;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }
        led_min = 83;
        led_max = 92;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }



    } else if ((get_highest_layer(layer_state) == _FN || get_highest_layer(layer_state) == _FN_L) && IS_LAYER_OFF(_RGB) && IS_LAYER_OFF(_CAPS) && IS_LAYER_OFF(_SFT) && IS_LAYER_OFF(_CTRL) && rgb_switch == 1) {
        led_min = 17;
        led_max = 47;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 50;
        led_max = 63;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 66;
        led_max = 76;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }



    } else if ((get_highest_layer(layer_state) == _RGB || (IS_LAYER_ON(_RGB) && ((IS_LAYER_ON(_FN) && IS_LAYER_OFF(_FN_L)) || (IS_LAYER_ON(_FN_L) && IS_LAYER_OFF(_FN)) || (IS_LAYER_ON(_FN) && IS_LAYER_ON(_FN_L))) && IS_LAYER_OFF(_CAPS) && IS_LAYER_OFF(_SFT) && IS_LAYER_OFF(_CTRL))) && rgb_switch == 1) {
        led_min = 17;
        led_max = 34;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }
        led_min = 34;
        led_max = 39;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
        }
        led_min = 39;
        led_max = 47;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }
        led_min = 50;
        led_max = 55;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
        }
        led_min = 55;
        led_max = 63;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }
        led_min = 66;
        led_max = 71;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
        }
        led_min = 71;
        led_max = 76;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 255 * brite_adj / 255);
        }
        led_min = 83;
        led_max = 84;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }



    } else if (get_highest_layer(layer_state) == _CAPS && rgb_switch == 1) {
        led_min = 17;
        led_max = 34;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 34;
        led_max = 44;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 255 * brite_adj / 255, 255 * brite_adj / 255);
        }
        led_min = 44;
        led_max = 47;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 47;
        led_max = 50;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }
        led_min = 50;
        led_max = 59;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 255 * brite_adj / 255, 255 * brite_adj / 255);
        }
        led_min = 59;
        led_max = 63;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 66;
        led_max = 73;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 255 * brite_adj / 255, 255 * brite_adj / 255);
        }
        led_min = 73;
        led_max = 76;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }



    } else if (get_highest_layer(layer_state) == _SFT && rgb_switch == 1) {
        led_min = 17;
        led_max = 30;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 36 * brite_adj / 255, 0);
        }
        led_min = 30;
        led_max = 34;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 34;
        led_max = 44;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 255 * brite_adj / 255, 255 * brite_adj / 255);
        }
        led_min = 44;
        led_max = 47;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 36 * brite_adj / 255, 0);
        }
        led_min = 50;
        led_max = 59;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 255 * brite_adj / 255, 255 * brite_adj / 255);
        }
        led_min = 59;
        led_max = 61;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 36 * brite_adj / 255, 0);
        }
        led_min = 61;
        led_max = 63;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 63;
        led_max = 66;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }
        led_min = 66;
        led_max = 73;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 255 * brite_adj / 255, 255 * brite_adj / 255);
        }
        led_min = 73;
        led_max = 76;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 36 * brite_adj / 255, 0);
        }
        led_min = 76;
        led_max = 80;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }



    } else if (get_highest_layer(layer_state) == _CTRL && rgb_switch == 1) {
        led_min = 17;
        led_max = 39;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 39;
        led_max = 44; 
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
        }
        led_min = 44;
        led_max = 47;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 50;
        led_max = 51;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 51;
        led_max = 52;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
        }
        led_min = 52;
        led_max = 63;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 66;
        led_max = 72;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 72 * brite_adj / 255);
        }
        led_min = 72;
        led_max = 76;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 60 * brite_adj / 255, 0, 255 * brite_adj / 255);
        }
        led_min = 80;
        led_max = 82;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }
        led_min = 92;
        led_max = 93;
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 255 * brite_adj / 255, 0, 0);
        }
    }
    return false;
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) == _CAPS) {
        if (IS_LAYER_ON(_SFT)) {
            if (get_mods() == MOD_BIT(KC_LSFT)) {
                unregister_code(KC_LSFT);
            }
        }
    }

    switch (keycode) {
        case RGB_STEP:
            if (record->event.pressed) {
                if (rgb_brite_val <= 0) {
                    rgb_brite_val = 1;
                } else if (rgb_brite_val <= 10) {
                    rgb_brite_val = rgb_brite_val + 1;
                    if (rgb_brite_val == 11) {
                        rgb_switch = 0;
                    }
                } else if (rgb_brite_val > 10) {
                    rgb_brite_val = 0;
                    rgb_switch    = 1;
                }
                // rgbv[x]: x =  0    1    2    3    4    5    6    7   8   9   10 11
                int rgbv[]    = {255, 230, 204, 178, 153, 128, 102, 77, 51, 26, 0, 255};
                brite_adj     = rgbv[rgb_brite_val];
            }
            return brite_adj && rgb_brite_val;

        case KC_MENU:
            if (record->event.pressed) {
                if (IS_LAYER_OFF(_RGB)) {
                    layer_on(_RGB);
                    if (IS_LAYER_ON(_CAPS) && host_keyboard_led_state().caps_lock) {
                        register_code(KC_CAPS);
                        unregister_code(KC_CAPS);
                    }
                    return false;
                } else {
                    layer_off(_RGB);
                    return false;
                }
            }

        case KC_CAPS:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_CAPS)) {
                    layer_off(_CAPS);
                    return true;
                } else {
                    layer_on(_CAPS);
                    return true;
                }
            }

        case KC_LSFT:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_SFT)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && host_keyboard_led_state().caps_lock) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_on(_SFT);
                return true;
            } else {
                if (IS_LAYER_OFF(_SFT)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && !host_keyboard_led_state().caps_lock && IS_LAYER_OFF(_CTRL)) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_off(_SFT);
                return true;
            }

        case KC_RSFT:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_SFT)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && host_keyboard_led_state().caps_lock) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_on(_SFT);
                return true;
            } else {
                if (IS_LAYER_OFF(_SFT)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && !host_keyboard_led_state().caps_lock && IS_LAYER_OFF(_CTRL)) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_off(_SFT);
                return true;
            }

        case KC_LCTL:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_CTRL)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && host_keyboard_led_state().caps_lock) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_on(_CTRL);
                return true;
            } else {
                if (IS_LAYER_OFF(_CTRL)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && !host_keyboard_led_state().caps_lock && IS_LAYER_OFF(_SFT)) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_off(_CTRL);
                return true;
            }

        case KC_RCTL:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_CTRL)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && host_keyboard_led_state().caps_lock) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_on(_CTRL);
                return true;
            } else {
                if (IS_LAYER_OFF(_CTRL)) {
                    return false;
                }
                if (IS_LAYER_ON(_CAPS) && !host_keyboard_led_state().caps_lock && IS_LAYER_OFF(_SFT)) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }
                layer_off(_CTRL);
                return true;
            }
    
    }
    return false;
}

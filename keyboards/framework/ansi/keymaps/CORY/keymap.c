// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later
// Written by Shandower 2024

#include QMK_KEYBOARD_H
#include "framework.h"

enum _layers {
  _BASE,
  _FN_LOCK,
  _FN,
};
//
//                               [ Default Layers ]    \|/ Virtual Layers \|/  Full Layer    # of ACTIVE  ACTIVE RGB   Current Defualt   X_val Challenge
//                               [_BASE] [_FN_LOCK]    caps_XX sft_XX ctrl_XX    fn_XX       Layers       LAYER        Layer             Value
//  ARRAY POSITION VALUES:   x =  0      1             2       3      4          5           6            7            8                 9
static int  HOLD_L[10]         = {1,     0,            0,      0,     0,         0,          0,           2,           0,                0               };
static bool HOLD_RC[6]         = {true,  false,        false,  false, false,     false};
static bool HOLD_TF[6]         = {true,  false,        false,  false, false,     false};
static int  X_val              = 0;
static int  brite_adj          = 255;
static int  rgb_brite_val      = 0;


// If anyone can fix the size issue when i had each row different sizes
// when i give the min and max limits for the rgb it would not work as it kept asking if
// this was an array or size error. then we can remove all the placeholder values "50".
const uint8_t rgb_array[8][18] = {
    {0, 5, 43, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
    {1, 2, 5,  44, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
    {3, 6, 8,  10, 12, 14, 16, 17, 22, 24, 30, 32, 34, 36, 41, 50, 50, 50},
    {3, 7, 10, 13, 18, 19, 22, 27, 28, 30, 32, 34, 36, 41, 50, 50, 50, 50},
    {4, 7, 11, 12, 18, 20, 21, 23, 27, 29, 31, 32, 34, 36, 41, 50, 50, 50},
    {3, 6, 9,  10, 12, 14, 15, 17, 22, 25, 26, 28, 30, 33, 34, 36, 42, 50},
    {3, 6, 8,  10, 12, 14, 16, 17, 22, 24, 30, 32, 35, 37, 38, 39, 40, 41} };


// I could not find an RGB equivalent to the Backlight step brightness code
// so i made my own.
enum Custom_Keycodes {
    RGB_STEP,
};



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
       KC_ESC,       KC_MUTE, KC_VOLD, KC_VOLU,  KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
       KC_GRV,       KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
       KC_TAB,       KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
       KC_CAPS,      KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
       KC_LSFT,      KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
       KC_LCTL,      MO(_FN), KC_LGUI, KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
   ),

   [_FN_LOCK] = LAYOUT(
       DF(_BASE),    KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
       KC_GRV,       KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
       KC_TAB,       KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
       KC_CAPS,      KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
       KC_LSFT,      KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
       KC_LCTL,      MO(_FN), KC_LGUI, KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_HOME, KC_PGUP, KC_PGDN, KC_END
   ),
/*
   [_FN] = LAYOUT(
       DF(_FN_LOCK), KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
       _______,      _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,      _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,      _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,          _______,
       _______,      _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,                   _______,
       _______,      _______, QK_BOOT, RGB_STEP,          RGB_TOG,                  _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
   ),
*/
   [_FN] = LAYOUT(
       DF(_FN_LOCK), KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
       _______,      _______, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______,
       _______,      _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______,
       _______,      _______, _______, BL_STEP,  BL_BRTG, BL_TOGG, _______, _______, _______, _______, _______, _______,          _______,
       _______,      _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,                   _______,
       _______,      _______, QK_BOOT, RGB_STEP,          RGB_TOG,                   _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    )
};


// I kept having to repeat portions so i condensed it as much as possible
// in this snippet although a few hiccups stopped me from getting it more condensed
// without another month researching so i stopped it here to get something out.

bool LAYER_CHANGE_X(int X_val) {
    if (HOLD_L[9] != X_val) {
        HOLD_L[9] = X_val;
        if (X_val > 5 && HOLD_L[X_val - 4] > 0 && HOLD_TF[X_val - 4]) {
            X_val          = X_val - 4;
            HOLD_TF[X_val] = false;
            HOLD_L[X_val]  = 0;
            HOLD_L[6]      = HOLD_L[6] - 1;
            if (default_layer_state == 1) {
                HOLD_L[8] = 0;
            } else if (default_layer_state == 2) {
                HOLD_L[8] = 1;
            }
            if (HOLD_RC[X_val]) {
                HOLD_RC[X_val] = false;
            }
            if (HOLD_L[6] == 0) {
                HOLD_L[7] = 2;
            } else if (HOLD_L[6] > 0) {
                for (int a = 2; a < 6; a++) {
                    if (HOLD_L[a] == HOLD_L[6] && X_val != a) {
                        if (a == 2 && !HOLD_RC[2]) {
                            register_code(KC_CAPS);
                            unregister_code(KC_CAPS);
                            HOLD_RC[2] = true;
                            HOLD_L[7]  = 3;
                        } else if (a == 3) {
                            HOLD_L[7] = 4;
                        } else if (a == 4) {
                            HOLD_L[7] = 5;
                        } else if (a == 5) {
                            HOLD_L[8] = 1;
                            HOLD_L[7] = 6;
                        }
                    }
                }
            }
            if (X_val == 2) {
                if (!HOLD_RC[3] && HOLD_TF[3] && get_mods() != MOD_BIT(KC_LSFT)) {
                    add_mods(MOD_BIT(KC_LSFT));
                    HOLD_RC[3] = true;
                }
                if (!HOLD_RC[4] && HOLD_TF[4] && get_mods() != MOD_BIT(KC_LCTL)) {
                    add_mods(MOD_BIT(KC_LCTL));
                    HOLD_RC[4] = true;
                }
            }
        } else if (X_val < 6 && !HOLD_RC[X_val] && !HOLD_TF[X_val] && HOLD_L[X_val] == 0) {
            HOLD_TF[X_val] = true;
            HOLD_RC[X_val] = true;
            if (X_val < 2) {
                if (HOLD_L[6] == 0) {
                    HOLD_L[7] = X_val;
                }
            } else if (X_val > 1) {
                HOLD_L[6]     = HOLD_L[6] + 1;
                HOLD_L[7]     = X_val + 1;
                HOLD_L[X_val] = HOLD_L[6];
            }
            if (HOLD_RC[2] && HOLD_L[2] < HOLD_L[6]) {
                register_code(KC_CAPS);
                unregister_code(KC_CAPS);
                HOLD_RC[2] = false;
            }
            if (HOLD_RC[3] && HOLD_TF[3] && X_val == 2 && get_mods() == MOD_BIT(KC_LSFT)) {
                HOLD_RC[3] = false;
                del_mods(MOD_BIT(KC_LSFT));
            }
            if (HOLD_RC[4] && HOLD_TF[4] && X_val == 2 && get_mods() == MOD_BIT(KC_LCTL)) {
                HOLD_RC[4] = false;
                del_mods(MOD_BIT(KC_LCTL));
            }
            if (HOLD_L[7] == 6) {
                HOLD_L[8] = 1;
            }
        }
    }
    return false;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_STEP:
            if (record->event.pressed) {
                if (rgb_brite_val <= 0) {
                    rgb_brite_val = 1;
                } else if (rgb_brite_val <= 9) {
                    rgb_brite_val = rgb_brite_val + 1;
                } else if (rgb_brite_val > 9) {
                    rgb_brite_val = 0;
                }
                // rgbv[x]: x =  0    1    2    3    4    5    6    7   8   9   10
                int rgbv[]    = {255, 230, 204, 178, 153, 128, 102, 77, 51, 26, 0};
                brite_adj     = rgbv[rgb_brite_val];
            }
            return brite_adj && rgb_brite_val;

        case DF(_BASE):
            if (record->event.pressed) {
                X_val      = 0;
                HOLD_L[0]  = 1;
                HOLD_L[1]  = 0;
                HOLD_L[8]  = 0;
                HOLD_RC[1] = false;
                HOLD_TF[1] = false;
                LAYER_CHANGE_X(X_val);
                return true;
            }
            return false;

        case DF(_FN_LOCK):
            if (record->event.pressed) {
                X_val      = 1;
                HOLD_L[0]  = 0;
                HOLD_L[1]  = 1;
                HOLD_L[8]  = 1;
                HOLD_RC[0] = false;
                HOLD_TF[0] = false;
                LAYER_CHANGE_X(X_val);
                return true;
            }
            return false;

        case KC_CAPS:
            if (record->event.pressed) {
                if (!HOLD_TF[2]) {
                    X_val = 2;
                    LAYER_CHANGE_X(X_val);
                    return true;
                } else if (HOLD_TF[2]) {
                    X_val = 6;
                    LAYER_CHANGE_X(X_val);
                    return true;
                }
            }
            return false;

        case KC_LSFT:
            if (record->event.pressed) {
                X_val = 3;
                LAYER_CHANGE_X(X_val);
                return true;
            } else {
                X_val = 7;
                LAYER_CHANGE_X(X_val);
                return true;
            }
            return false;

        case KC_LCTL:
            if (record->event.pressed) {
                X_val = 4;
                LAYER_CHANGE_X(X_val);
                return true;
            } else {
                X_val = 8;
                LAYER_CHANGE_X(X_val);
                return true;
            }
            return false;

        case MO(_FN):
            if (record->event.pressed) {
                X_val = 5;
                HOLD_L[8] = 1;
                LAYER_CHANGE_X(X_val);
                return true;
            } else {
                X_val     = 9;
                HOLD_L[8] = 0;
                LAYER_CHANGE_X(X_val);
                return true;
            }
            return false;
    }
    return false;
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // rgb_array[][x]: x =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44
    int lmin[]           = {0,   0,   2,   17,  17,  30,  34,  34,  39,  39,  44,  44,  47,  47,  50,  51,  51,  52,  50,  59,  59,  61,  63,  63,  66,  66,  72,  66,  73,  73,  76,  76,  80,  80,  82,  82,  83,  83,  84,  85,  86,  92,  92,  93,  93};
    int lmax[]           = {17,  2,   17,  30,  30,  34,  39,  44,  44,  44,  47,  47,  50,  50,  51,  52,  52,  63,  59,  63,  61,  63,  66,  66,  76,  72,  73,  73,  76,  76,  80,  80,  82,  82,  83,  83,  92,  84,  85,  86,  92,  93,  93,  97,  97};
    int color[]          = {3,   8,   7,   1,   0,   1,   1,   5,   1,   0,   1,   0,   2,   8,   1,   0,   1,   1,   5,   1,   0,   1,   2,   8,   1,   0,   1,   5,   1,   0,   2,   8,   2,   8,   2,   8,   1,   8,   0,   8,   1,   2,   8,   3,   7 };
    // color[x]: x =  0       1     2        3       4     5     6       7      8
    // color name  =  pinker  blue  magenta  violet  rose  cyan  orange  burnt  red
    int LEDr[]     = {255,    0,    255,     60,     255,  0,    255,    255,   255};
    int LEDg[]     = {0,      0,    0,       0,      40,   255,  128,    36,    0  };
    int LEDb[]     = {72,     255,  255,     255,    150,  255,  0,      0,     0  };

    static int max_array = 18;
    static int b         = 0;
    for (int a = 0; a < 2; a++) {
        // default layer rgb
        if (a == 0) {
            b = HOLD_L[8];
        // active rgb "layer"
        } else if (a == 1) {
            b = HOLD_L[7];
        }
        // find the size of the array row
        for (int c = 0; c < 18; c++) {
            if (rgb_array[b][c] != 50) {
                max_array = (c + 1);
            }
        }
        for (int d = 0; d < max_array; d++) {
            int e   = rgb_array[b][d];
            led_min = lmin[e];
            led_max = lmax[e];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[color[e]] * brite_adj / 255, LEDg[color[e]] * brite_adj / 255, LEDb[color[e]] * brite_adj / 255);
            }
        }
    }
    return true;
}



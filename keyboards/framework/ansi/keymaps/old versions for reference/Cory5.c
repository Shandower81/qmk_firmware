// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "framework.h"
#include "print.h"

enum _layers {
  _BASE,
  _FN_LOCK,
  _CAPS,
  _SFT,
  _CTRL,
  _FN,
};

static int  brite_adj     = 255;
static int  rgb_brite_val = 0;

static int  CAPS_L        = 0;
static int  SFT_L         = 0;
static int  CTRL_L        = 0;
static int  FN_L          = 0;
static int  TOT_L         = 0;

static bool CAPS_RC       = false;
static bool SFT_RC        = false;
static bool CTRL_RC       = false;

static bool CAPS_TF       = false;
static bool FN_LOCK_TF    = false;
static bool SFT_TF        = false;
static bool CTRL_TF       = false;
static bool FN_TF         = false;

static int    array_0_l              = 0;
static int    array_1_l              = 1;

const uint8_t rgb_array[8][18] = { 
    {0, 5, 43, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
    {3, 6, 8,  10, 12, 14, 16, 17, 22, 24, 30, 32, 34, 36, 41, 50, 50, 50},
    {1, 2, 5,  44, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
    {3, 6, 8,  10, 12, 14, 16, 17, 22, 24, 30, 32, 34, 36, 41, 50, 50, 50},
    {3, 7, 10, 13, 18, 19, 22, 27, 28, 30, 32, 34, 36, 41, 50, 50, 50, 50},
    {4, 7, 11, 12, 18, 20, 21, 23, 27, 29, 31, 32, 34, 36, 41, 50, 50, 50},
    {3, 6, 9,  10, 12, 14, 15, 17, 22, 25, 26, 28, 30, 33, 34, 36, 42, 50},
    {3, 6, 8,  10, 12, 14, 16, 17, 22, 24, 30, 32, 35, 37, 38, 39, 40, 41}};



enum Custom_Keycodes {
    RGB_STEP,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │ESC  │Mut│vDn│vUp│Prv│Ply│Nxt│bDn│bUp│Scn│Air│Prt│App│Del │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backsp│
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \  │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  Shift  │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     *         │    │   │   │   │                   │   │   │    │↑  │    │
     * 11 keys │Ctrl│FN │GUI│Alt│                   │Alt│Ctl│ ←  ├───┤  → │
     *         │    │   │   │   │                   │   │   │    │  ↓│    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     * 78 total     */

    [_BASE] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),

    [_FN_LOCK] = LAYOUT(
        FN_LOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),

    [_CAPS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),

    [_SFT] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),

    [_CTRL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT(
        FN_LOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, QK_BOOT, RGB_STEP,          RGB_TOG,                  _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_STEP:
            if (record->event.pressed) {
                int test_val = rgb_brite_val;
                if (test_val <= 0) {
                    test_val = 1;
                } else if (test_val <= 9) {
                    test_val = test_val + 1;
                } else if (test_val > 9) {
                    test_val = 0;
                }
//              rgb_brite_val =  0    1    2    3    4    5    6    7   8   9   10
                int rgbv[]    = {255, 230, 204, 178, 153, 128, 102, 77, 51, 26, 0};
                brite_adj     = rgbv[test_val];
                rgb_brite_val = test_val;
            }
            return brite_adj && rgb_brite_val;



        case FN_LOCK:
            if (record->event.pressed) {
                if (!FN_LOCK_TF) {
                    FN_LOCK_TF = !FN_LOCK_TF;
                    default_layer_set(_FN_LOCK);
                    layer_off(_BASE);
                    layer_on(_FN_LOCK);
                    return true;
                } else {
                    FN_LOCK_TF = !FN_LOCK_TF;
                    default_layer_set(_BASE);
                    layer_off(_FN_LOCK);
                    layer_on(_BASE);
                    return true;
                }
                return false;
            }
            return false;



        case KC_CAPS:
            if (record->event.pressed) {
                if (!CAPS_TF) {                 
                    CAPS_TF = !CAPS_TF;                 
                    if (!CAPS_RC && IS_LAYER_OFF(_CAPS)) {
                        if (TOT_L > 0) {
                            if ((FN_L > 0) && FN_TF) {
                                if (IS_LAYER_ON(_FN)) {
                                    layer_off(_FN);
                                }
                            }
                            if ((SFT_L > 0) && SFT_TF) {
                                if (IS_LAYER_ON(_SFT)) {
                                    layer_off(_SFT);
                                }
                                if (SFT_RC) {
                                    unregister_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                            }
                            if ((CTRL_L > 0) && CTRL_TF) {
                                if (IS_LAYER_ON(_CTRL)) {
                                    layer_off(_CTRL);
                                }
                                if (CTRL_RC) {
                                    unregister_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                            }
                        }
                        CAPS_RC = !CAPS_RC;
                        TOT_L   = TOT_L + 1;
                        CAPS_L  = TOT_L;
                        layer_on(_CAPS);
                        array_1_l   = 4;
                    }
                    return true;
                } else {
                    if (CAPS_TF) {
                        CAPS_TF = !CAPS_TF;
                        if (IS_LAYER_ON(_CAPS) && CAPS_RC) {
                            layer_off(_CAPS);
                            CAPS_RC = !CAPS_RC;
                            if (CAPS_L == TOT_L) {
                                if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                    layer_on(_FN);
                                    array_1_l   = 7;
                                    if ((SFT_L > 0) && !SFT_RC && SFT_TF) {
                                        register_code(KC_LSFT);
                                        SFT_RC = !SFT_RC;
                                    }
                                    if ((CTRL_L > 0) && !CTRL_RC && CTRL_TF) {
                                        register_code(KC_LCTL);
                                        CTRL_RC = !CTRL_RC;
                                    }
                                }
                                if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                    layer_on(_SFT);
                                    array_1_l   = 5;
                                    if (!SFT_RC) {
                                        register_code(KC_LSFT);
                                        SFT_RC = !SFT_RC;
                                    }
                                }
                                if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                    layer_on(_CTRL);
                                    array_1_l   = 6;
                                    if (!CTRL_RC) {
                                        register_code(KC_LCTL);
                                        CTRL_RC = !CTRL_RC;
                                    }
                                }
                            }
                        } else {
                            if ((CAPS_L > 0) && (CAPS_L < TOT_L)) {
                                if (FN_L > CAPS_L) {
                                    FN_L = FN_L - 1;
                                }
                                if (SFT_L > CAPS_L) {
                                    SFT_L = SFT_L - 1;
                                }
                                if (CTRL_L > CAPS_L) {
                                    CTRL_L = CTRL_L - 1;
                                }
                            }
                        }
                        TOT_L  = TOT_L - 1;
                        CAPS_L = 0;
                    }
                    return true;
                }
            }
            return false;

        case KC_LSFT:
            if (record->event.pressed) {
                if (!SFT_TF) {
                    SFT_TF = !SFT_TF;
                    if (!SFT_RC && IS_LAYER_OFF(_SFT)) {
                        if (TOT_L > 0) {
                            if ((CAPS_L > 0) && CAPS_TF) {
                                if (IS_LAYER_ON(_CAPS)) {
                                    layer_off(_CAPS);
                                }
                                if (CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                            }
                            if ((FN_L > 0) && FN_TF) {
                                if (IS_LAYER_ON(_FN)) {
                                    layer_off(_FN);
                                }
                            }
                            if ((CTRL_L > 0) && CTRL_TF) {
                                if (IS_LAYER_ON(_CTRL)) {
                                    layer_off(_CTRL);
                                }
                                if ((CTRL_L > CAPS_L) && !CTRL_RC) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                            }
                        }
                        layer_on(_SFT);
                        register_code(KC_LSFT);
                        SFT_RC = !SFT_RC;
                    }
                    TOT_L = TOT_L + 1;
                    SFT_L       = TOT_L;
                    array_1_l   = 5;
                }
                return true;
            } else {
                if (SFT_TF) {
                    SFT_TF = !SFT_TF;
                    if (SFT_RC && IS_LAYER_ON(_SFT)) {
                        layer_off(_SFT);
                        unregister_code(KC_LSFT);
                        SFT_RC = !SFT_RC;
                        if (SFT_L == TOT_L) {
                            if ((CAPS_L == TOT_L - 1) && CAPS_TF && !CAPS_RC && IS_LAYER_OFF(_CAPS)) {
                                layer_on(_CAPS);
                                register_code(KC_CAPS);
                                unregister_code(KC_CAPS);
                                CAPS_RC     = !CAPS_RC;
                                array_1_l   = 4;
                            } else if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                layer_on(_FN);
                                array_1_l   = 7;
                                if ((CTRL_L > CAPS_L) && CTRL_TF && !CTRL_RC && IS_LAYER_OFF(_CTRL)) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                            } else if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                layer_on(_CTRL);
                                array_1_l   = 6;
                                if (!CTRL_RC) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                            }
                        }
                    } else {
                        if ((SFT_L > 0) && (SFT_L < TOT_L)) {
                            if (CAPS_L > SFT_L) {
                                CAPS_L = CAPS_L - 1;
                            }
                            if (FN_L > SFT_L) {
                                FN_L = FN_L - 1;
                            }
                            if (CTRL_L > SFT_L) {
                                CTRL_L = CTRL_L - 1;
                            }
                        }
                    }
                    TOT_L = TOT_L - 1;
                    SFT_L = 0;
                }
                return true;
            }
            return false;

        case KC_LCTL:
            if (record->event.pressed) {
                if (!CTRL_TF) {
                    CTRL_TF = !CTRL_TF;
                    if (!CTRL_RC && IS_LAYER_OFF(_CTRL)) {
                        if (TOT_L > 0) {
                            if ((CAPS_L > 0) && CAPS_TF) {
                                if (IS_LAYER_ON(_CAPS)) {
                                    layer_off(_CAPS);
                                }
                                if (CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                            }
                            if ((FN_L > 0) && FN_TF) {
                                if (IS_LAYER_ON(_FN)) {
                                    layer_off(_FN);
                                }
                            }
                            if ((SFT_L > 0) && SFT_TF) {
                                if (IS_LAYER_ON(_SFT)) {
                                    layer_off(_SFT);
                                }
                                if ((SFT_L > CAPS_L) && !SFT_RC) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                            }
                        }
                        layer_on(_CTRL);
                        CTRL_RC = !CTRL_RC;
                    }
                    TOT_L  = TOT_L + 1;
                    CTRL_L      = TOT_L;
                    array_1_l   = 6;
                }
                return true;
            } else {
                if (CTRL_TF) {
                    CTRL_TF = !CTRL_TF;
                    if (CTRL_RC && IS_LAYER_ON(_CTRL)) {
                        layer_off(_CTRL);
                        unregister_code(KC_LCTL);
                        CTRL_RC = !CTRL_RC;
                        if (CTRL_L == TOT_L) {
                            if ((CAPS_L == TOT_L - 1) && CAPS_TF && IS_LAYER_OFF(_CAPS)) {
                                layer_on(_CAPS);
                                array_1_l   = 4;
                                if (!CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                            } else if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                layer_on(_FN);
                                array_1_l   = 7;
                                if ((SFT_L > CAPS_L) && SFT_TF && !SFT_RC && IS_LAYER_OFF(_SFT)) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                            } else if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                layer_on(_SFT);
                                array_1_l   = 5;
                                if (!SFT_RC) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                            }
                        }
                    } else {
                        if ((CTRL_L > 0) && (CTRL_L < TOT_L)) {
                            if (CAPS_L > CTRL_L) {
                                CAPS_L = CAPS_L - 1;
                            }
                            if (FN_L > CTRL_L) {
                                FN_L = FN_L - 1;
                            }
                            if (SFT_L > CTRL_L) {
                                SFT_L = SFT_L - 1;
                            }
                        }
                    }
                    TOT_L  = TOT_L - 1;
                    CTRL_L = 0;
                }
                return true;
            }
            return false;



        case MO(_FN):
            if (record->event.pressed) {
                if (!FN_TF) {
                    FN_TF = !FN_TF;
                    if (IS_LAYER_OFF(_FN)) {
                        if (TOT_L > 0) {
                            if ((CAPS_L > 0) && CAPS_TF) {
                                if (IS_LAYER_ON(_CAPS)) {
                                    layer_off(_CAPS);
                                }
                                if (CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                            }
                            if ((SFT_L > 0) && SFT_TF) {
                                if (IS_LAYER_ON(_SFT)) {
                                    layer_off(_SFT);
                                }
                            }
                            if ((CTRL_L > 0) && CTRL_TF) {
                                if (IS_LAYER_ON(_CTRL)) {
                                    layer_off(_CTRL);
                                }
                            }
                        }
                        layer_on(_FN);
                    }
                    TOT_L = TOT_L + 1;
                    FN_L      = TOT_L;
                    array_0_l = 2;
                    array_1_l = 7;
                }
                return true;
            } else {
                if (FN_TF) {
                    FN_TF = !FN_TF;
                    if (IS_LAYER_ON(_FN)) {
                        layer_off(_FN);
                        if (FN_L == TOT_L) {
                            if ((CAPS_L == TOT_L - 1) && CAPS_TF && IS_LAYER_OFF(_CAPS)) {
                                layer_on(_CAPS);
                                array_1_l   = 4;
                                if (!CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                            } else if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                layer_on(_SFT);
                                array_1_l   = 5;
                                if (!SFT_RC) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                                if ((CTRL_L > CAPS_L) && CTRL_TF && !CTRL_RC && IS_LAYER_OFF(_CTRL)) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                            } else if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                layer_on(_CTRL);
                                array_1_l   = 6;
                                if (!CTRL_RC) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                                if ((SFT_L > CAPS_L) && SFT_TF && !SFT_RC && IS_LAYER_OFF(_SFT)) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                            }
                        }
                    } else {
                        if ((FN_L > 0) && (FN_L < TOT_L)) {
                            if (CAPS_L > FN_L) {
                                CAPS_L = CAPS_L - 1;
                            }
                            if (SFT_L > FN_L) {
                                SFT_L = SFT_L - 1;
                            }
                            if (CTRL_L > FN_L) {
                                CTRL_L = CTRL_L - 1;
                            }
                        }
                    }
                    TOT_L = TOT_L - 1;
                    FN_L  = 0;
                }
                return true;
            }
            return false;



    }
    return false;
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_LAYER_ON(_BASE)) {
        array_0_l = 0;
        if (TOT_L == 0) {
            array_1_l = 1;
        }
    } else if (IS_LAYER_ON(_FN_LOCK)) {
        array_0_l = 2;
        if (TOT_L == 0) {
            array_1_l = 3;
        }
    }
        //rgb_array[][]  =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44 
        int lmin[]       = {0,   0,   2,   17,  17,  30,  34,  34,  39,  39,  44,  44,  47,  47,  50,  51,  51,  52,  50,  59,  59,  61,  63,  63,  66,  66,  72,  66,  73,  73,  76,  76,  80,  80,  82,  82,  83,  83,  84,  85,  86,  92,  92,  93,  93 };
        int lmax[]       = {17,  2,   17,  30,  30,  34,  39,  44,  44,  44,  47,  47,  50,  50,  51,  52,  52,  63,  59,  63,  61,  63,  66,  66,  76,  72,  73,  73,  76,  76,  80,  80,  82,  82,  83,  83,  92,  84,  85,  86,  92,  93,  93,  97,  97 };
        int color[]      = {3,   8,   7,   1,   0,   1,   1,   5,   1,   0,   1,   0,   2,   8,   1,   0,   1,   1,   5,   1,   0,   1,   2,   8,   1,   0,   1,   5,   1,   0,   2,   8,   2,   8,   2,   8,   1,   8,   0,   8,   1,   2,   8,   3,   7  };
        //  color[]  =  0      1     2        3       4     5     6       7      8
        //color name =  pinkr  blue  magenta  violet  rose  cyan  orange  burnt  red 
        int LEDr[]   = {255,   0,    255,     60,     255,  0,    255,    255,   255};
        int LEDg[]   = {0,     0,    0,       0,      40,   255,  128,    36,    0  };
        int LEDb[]   = {72,    255,  255,     255,    150,  255,  0,      0,     0  };

        int array_l = 0;
        int max_array = 18;

        for (int a = 0; a < 2; a++) {
            if (a == 0) {
                array_l = array_0_l;
                for (int d = 0; d < 18; d++) {
                    if (rgb_array[array_l][d] != 50) {
                        max_array = d + 1;
                    }
                }
            } else {
                array_l = array_1_l;
                for (int d = 0; d < 18; d++) {
                    if (rgb_array[array_l][d] != 50) {
                        max_array = d + 1;
                    }
                }
            }
            for (int b = 0; b < max_array; b++) {
                int c   = rgb_array[array_l][b];
                led_min = lmin[c];
                led_max = lmax[c];
                for (uint8_t i = led_min; i < led_max; i++) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[color[c]] * brite_adj / 255, LEDg[color[c]] * brite_adj / 255, LEDb[color[c]] * brite_adj / 255);
                }
            }
        }
        return true;
}


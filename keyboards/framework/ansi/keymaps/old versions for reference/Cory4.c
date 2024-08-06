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
        _______, _______, QK_BOOT, RGB_STEP,          RGB_TOG,                  DB_TOGG, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
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
                    if (FN_L == TOT_L) {
                        layer_state = 32;
                    } else if (TOT_L == 0) {
                        layer_state = 0;
                    }
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
                                    if (!SFT_RC) {
                                        register_code(KC_LSFT);
                                        SFT_RC = !SFT_RC;
                                    }
                                }
                                if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                    layer_on(_CTRL);
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
                    SFT_L = TOT_L;
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
                                CAPS_RC = !CAPS_RC;
                            } else if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                layer_on(_FN);
                                if ((CTRL_L > CAPS_L) && CTRL_TF && !CTRL_RC && IS_LAYER_OFF(_CTRL)) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                            } else if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                layer_on(_CTRL);
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
                    CTRL_L = TOT_L;
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
                                if (!CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                            } else if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                layer_on(_FN);
                                if ((SFT_L > CAPS_L) && SFT_TF && !SFT_RC && IS_LAYER_OFF(_SFT)) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                            } else if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                layer_on(_SFT);
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
                    FN_L  = TOT_L;
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
                                if (!CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                            } else if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                layer_on(_SFT);
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

    if (IS_LAYER_ON(_BASE) && (TOT_L == 0)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10    
        int lmin[] = {0,   17,  47,  50,  63,  66,  76,  83,  92,  93 };
        int lmax[] = {17,  47,  50,  63,  66,  76,  83,  92,  93,  97 };
        int a;
        int LEDr[] = {60,  0,   255, 0,   255, 0,   255, 0,   255, 60 };
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0  };
        int LEDb[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
        for (a = 0; a < 10; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;



    } else if (IS_LAYER_ON(_FN_LOCK) && (TOT_L == 0)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10
        int lmin[] = {0,   2,   17,  47,  50,  63,  66,  76,  83,  93 };
        int lmax[] = {2,   17,  47,  50,  63,  66,  76,  83,  93,  97 };
        int a;
        int LEDr[] = {255, 255, 0,   255, 0,   255, 0,   255, 0,   255};
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0  };
        int LEDb[] = {0,   72,  255, 255, 255, 255, 255, 255, 255, 72 };
        for (a = 0; a < 10; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    } else if (IS_LAYER_ON(_CAPS)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   
        int lmin[] = {0,   17,  34,  44,  47,  50,  59,  63,  66,  73,  76,  83,  92,  93 };
        int lmax[] = {17,  34,  44,  47,  50,  59,  63,  66,  73,  76,  83,  92,  93,  97 };
        int a;
        int LEDr[] = {60,  0,   0,   0,   255, 0,   0,   255, 0,   0,   255, 0,   255, 60 };
        int LEDg[] = {0,   0,   255, 0,   0,   255, 0,   0,   255, 0,   0,   0,   0,   0  };
        int LEDb[] = {255, 255, 255, 255, 0,   255, 255, 255, 255, 255, 255, 255, 255, 255};
        for (a = 0; a < 14; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;

    } else if (IS_LAYER_ON(_SFT)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   
        int lmin[] = {0,   17,  30,  34,  44,  47,  50,  59,  61,  63,  66,  73,  76,  80,  83,  92,  93 };
        int lmax[] = {17,  30,  34,  44,  47,  50,  59,  61,  63,  66,  73,  76,  80,  83,  92,  93,  97 };
        int a;
        int LEDr[] = {60,  255, 0,   0,   255, 255, 0,   255, 0,   255, 0,   255, 255, 255, 0,   255, 60 };
        int LEDg[] = {0,   0,   0,   255, 0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   0,   0,   0  };
        int LEDb[] = {255, 72,  255, 255, 72,  255, 255, 72,  255, 0,   255, 72,  0,   255, 255, 255, 255};
        for (a = 0; a < 17; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    } else if (IS_LAYER_ON(_CTRL)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
        int lmin[] = {0,   17,  39,  44,  47,  50,  51,  52,  63,  66,  72,  76,  80,  82,  83,  92,  93 };
        int lmax[] = {17,  39,  44,  47,  50,  51,  52,  63,  66,  72,  76,  80,  82,  83,  92,  93,  97 };
        int a;
        int LEDr[] = {60,  0,   255, 0,   255, 0,   255, 0,   255, 255, 0,   255, 255, 255, 0,   255, 60 };
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  };
        int LEDb[] = {255, 255, 72,  255, 255, 255, 72,  255, 255, 72,  255, 255, 0,   255, 255, 0,   255};
        for (a = 0; a < 17; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;

    } else if (IS_LAYER_ON(_FN)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15
        int lmin[] = {0,   2,   17,  47,  50,  63,  66,  76,  82,  83,  84,  85,  86,  92,  93 };
        int lmax[] = {2,   17,  47,  50,  63,  66,  76,  82,  83,  84,  85,  86,  92,  93,  97 };
        int a;
        int LEDr[] = {255, 255, 0,   255, 0,   255, 0,   255, 255, 255, 255, 255, 0,   255, 255};
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   36,  0,   0,   0  };
        int LEDb[] = {0,   72,  255, 255, 255, 255, 255, 255, 0,   0,   72,  0,   255, 255, 72 };
        for (a = 0; a < 15; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;



    }
    return false;
}


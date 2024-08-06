// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "framework.h"


enum _layers {
  _BASE,
  _CAPS,
  _FN,
  _SFT,
  _FN_SFT,
  _CTRL
};

static int  brite_adj     = 255;
static int  rgb_brite_val = 0;
static int  CAPS_L        = 0;
static int  FN_L          = 0;
static int  SFT_L         = 0;
static int  FN_SFT_L      = 0;
static int  CTRL_L        = 0;
static int  TOT_L         = 0;
static bool CAPS_RC       = false;
static bool SFT_RC        = false;
static bool FN_SFT_RC     = false;
static bool CTRL_RC       = false;
static bool CAPS_TF       = false;
static bool FN_TF         = false;
static bool SFT_TF        = false;
static bool FN_SFT_TF     = false;
static bool CTRL_TF       = false;
static bool RGB_BASE      = false;
static bool RGB_CAPS      = false;
static bool RGB_FN        = false;
static bool RGB_SFT       = false;
static bool RGB_FN_SFT    = false;
static bool RGB_CTRL      = false;


enum RGB_BRIGHTNESS {
    RGB_STEP,
};

enum Custom_Keycodes {
    FN_SFT,
    LYR_SWP,
    CC_CAPS,
    CC_LSFT,
    CC_LCTL,
    CC_FN,
};

enum KEY_SWAP {
    CC_ESC,
    CC_F1,
    CC_F2,
    CC_F3,
    CC_F4,
    CC_F5,
    CC_F6,
    CC_F7,
    CC_F8,
    CC_F9,
    CC_F10,
    CC_F11,
    CC_F12,
    CC_DEL,
    CC_LGUI,
    CC_LALT,
    CC_SPC,
    CC_LEFT,
    CC_UP,
    CC_DOWN,
    CC_RGHT,
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
        CC_ESC,      CC_F1,   CC_F2,   CC_F3,   CC_F4,   CC_F5,   CC_F6,   CC_F7,   CC_F8,   CC_F9,   CC_F10,  CC_F11,  CC_F12,  CC_DEL,
        KC_GRV,      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        CC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
        CC_LCTL,     CC_FN,   CC_LGUI, CC_LALT,          CC_SPC,                    KC_RALT, KC_RCTL, CC_LEFT, CC_UP,   CC_DOWN, CC_RGHT
    ),

    [_CAPS] = LAYOUT(
        _______,     KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,     _______, KC_LGUI, _______,          KC_SPC,                    _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        FN_SFT,      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,     _______, QK_BOOT, RGB_STEP,          RGB_TOG,                   _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),

    [_SFT] = LAYOUT(
        FN_SFT,      KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,     _______, KC_LGUI, _______,          KC_SPC,                    _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),

    [_FN_SFT] = LAYOUT(
        FN_SFT,      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,     _______, KC_LGUI, _______,          KC_SPC,                    _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),

    [_CTRL] = LAYOUT(
        KC_ESC,     KC_MUTE,  KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        _______,    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,    _______,  KC_LGUI, _______,          KC_SPC,                    _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
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
                // rgb_brite_val =  0    1    2    3    4    5    6    7   8   9   10
                int rgbv[]    = {255, 230, 204, 178, 153, 128, 102, 77, 51, 26, 0};
                brite_adj     = rgbv[test_val];
                rgb_brite_val = test_val;
            }
            return true;

        case KEY_SWAP[0]... KEY_SWAP[20]:
            //      key_num        0       1        2        3        4        5        6        7        8        9        10       11       12       13      14       15        16       17       18       19       20
            int            MAIN_KEYS[]    = {KC_ESC, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL, KC_LGUI, KC_LALT, KC_SPC, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT};
            int            UP_KEYS[]      = {FN_SFT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, QK_BOOT, RGB_STEP, RGB_TOG, KC_HOME, KC_PGUP, KC_PGDN, KC_END};
            int            BASE_KEYS[]    = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
            int            FN_KEYS[]      = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
            int            SFT_KEYS[]     = {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
            int            FN_SFT_KEYS[]  = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2};
            int            key_num        = KEY_SWAP();
            static bool    KEY_LVL        = true;
            static uint8_t registered_key = KC_NO;
            if (record->event.pressed) {
                if (RGB_BASE || RGB_CAPS || RGB_CTRL) {
                    if (BASE_KEYS[key_num] == 1) {
                        KEY_LVL = true;
                    } else {
                        KEY_LVL = false;
                    }
                } else if (RGB_FN) {
                    if (FN_KEYS[key_num] == 1) {
                        KEY_LVL = true;
                    } else {
                        KEY_LVL = false;
                    }
                } else if (RGB_SFT) {
                    if (SFT_KEYS[key_num] == 1) {
                        KEY_LVL = true;
                    } else {
                        KEY_LVL = false;
                    }
                } else if (RGB_FN_SFT) {
                    if (BASE_KEYS[key_num] == 1) {
                        KEY_LVL = true;
                    } else {
                        KEY_LVL = false;
                    }
                }
                registered_key = (KEY_LVL) ? MAIN_KEYS[key_num] : UP_KEYS[key_num];
                register_code(registered_key);
            } else {
                unregister_code(registered_key);
            }
            return true;

        case LYR_SWP:
            if (record->event.pressed) {
                if (CAPS_L > 0) {
                    if (CAPS_L == TOT_L) {
                        if (IS_LAYER_OFF(_CAPS)) {
                            layer_on(_CAPS);
                            return true;
                        }
                        if (CAPS_RC == false) {
                            CAPS_RC = true;
                            register_code(KC_CAPS);
                            unregister_code(KC_CAPS);
                            return false;
                        }
                        return false;
                    } else if (CAPS_L < TOT_L) {
                        if (IS_LAYER_ON(_CAPS)) {
                            layer_off(_CAPS);
                            return false;
                        }
                        if (CAPS_RC == true) {
                            CAPS_RC = false;
                            register_code(KC_CAPS);
                            unregister_code(KC_CAPS);
                            return false;
                        }
                        return false;
                    }
                }
                return false;

                if (FN_L > 0) {
                    if (FN_L == TOT_L) {
                        if (IS_LAYER_OFF(_FN)) {
                            layer_on(_FN);
                            return false;
                        }
                    } else if (FN_L < TOT_L) {
                        if (IS_LAYER_ON(_FN)) {
                            layer_off(_FN);
                            return false;
                        }
                    }
                }
                return false;

                if (SFT_L > 0) {
                    if (SFT_L == TOT_L) {
                        if (IS_LAYER_OFF(_SFT)) {
                            layer_on(_SFT);
                            return false;
                        }
                        if (SFT_RC == false) {
                            SFT_RC = true;
                            register_code(KC_LSFT);
                            return false;
                        }
                        return false;
                    } else if (SFT_L < TOT_L) {
                        if (IS_LAYER_ON(_SFT)) {
                            layer_off(_SFT);
                            return false;
                        }
                        if ((SFT_RC == false) && (SFT_L > CAPS_L) && (SFT_L > FN_SFT_L)) {
                            SFT_RC = true;
                            if (CTRL_L == 0) {
                                register_code(KC_LSFT);
                                return false;
                            } else if ((SFT_L > CTRL_L) && (CTRL_L > CAPS_L) && (CTRL_L > FN_SFT_L)) {
                                if (CTRL_RC == true) {
                                    register_code(KC_LSFT);
                                    return false;
                                } else if (CTRL_RC == false) {
                                    register_code(KC_LCTL);
                                    register_code(KC_LSFT);
                                    return false;
                                }
                            }
                        }
                        if ((SFT_RC == true) && (CAPS_L > SFT_L)) {
                            SFT_RC = false;
                            unregister_code(KC_LSFT);
                            return false;
                        }
                        if ((SFT_RC == true) && (FN_SFT_L > SFT_L)) {
                            SFT_RC = false;
                            unregister_code(KC_LSFT);
                            return false;
                        }
                        return false;
                    }
                }
                return false;

                if (FN_SFT_L > 0) {
                    if (FN_SFT_L == TOT_L) {
                        if (IS_LAYER_OFF(_FN_SFT)) {
                            layer_on(_FN_SFT);
                            return false;
                        }
                        if (FN_SFT_RC == false) {
                            FN_SFT_RC = true;
                            return false;
                            if (SFT_RC == true) {
                                SFT_RC = false;
                                return false;
                            } else {
                                register_code(KC_LSFT);
                                return false;
                            }
                        }
                        return false;
                    } else if (FN_SFT_L < TOT_L) {
                        if (IS_LAYER_ON(_FN_SFT)) {
                            layer_off(_FN_SFT);
                            return false;
                        }
                        if (FN_SFT_RC == true) {
                            FN_SFT_RC = false;
                            if (SFT_TF == false) {
                                unregister_code(KC_LSFT);
                                return false;
                            } else if ((SFT_TF == true) && (SFT_RC == false)) {
                                SFT_RC = true;
                                return false;
                            }
                        }
                        return false;
                    }
                }
                return false;

                if (CTRL_L > 0) {
                    if (CTRL_L == TOT_L) {
                        if (IS_LAYER_OFF(_CTRL)) {
                            layer_on(_CTRL);
                            return false;
                        }
                        if (CTRL_RC == false) {
                            CTRL_RC = true;
                            register_code(KC_LCTL);
                            return false;
                        }
                        return false;
                    } else if (CTRL_L < TOT_L) {
                        if (IS_LAYER_ON(_CTRL)) {
                            layer_off(_CTRL);
                            return false;
                        }
                        if ((CTRL_RC == false) && (CTRL_L > CAPS_L) && (CTRL_L > FN_SFT_L)) {
                            CTRL_RC = true;
                            if (SFT_L == 0) {
                                register_code(KC_LCTL);
                                return false;
                            } else if ((CTRL_L > SFT_L) && (SFT_L > CAPS_L) && (SFT_L > FN_SFT_L)) {
                                if (SFT_RC == true) {
                                    register_code(KC_LCTL);
                                    return false;
                                } else if (SFT_RC == false) {
                                    register_code(KC_LSFT);
                                    register_code(KC_LCTL);
                                    return false;
                                }
                            }
                        }
                        if ((CTRL_RC == true) && (CAPS_L > CTRL_L)) {
                            CTRL_RC = false;
                            unregister_code(KC_LCTL);
                            return false;
                        }
                        if ((CTRL_RC == true) && (FN_SFT_L > CTRL_L)) {
                            CTRL_RC = false;
                            unregister_code(KC_LCTL);
                            return false;
                        }
                        return false;
                    }
                }
                return false;
            }
            return true;

        case CC_CAPS:
            if (record->event.pressed) {
                if (CAPS_TF == false) {
                    if (RGB_CAPS == false) {
                        RGB_CAPS = true;
                        CAPS_TF  = true;
                        TOT_L    = TOT_L + 1;
                        CAPS_L   = TOT_L;
                        LYR_SWP;
                        return true;
                    }
                } else {
                    if (RGB_CAPS == true) {
                        RGB_CAPS = false;
                    } else {
                        if ((CAPS_L > 0) && (CAPS_L < TOT_L)) {
                            if (FN_L > CAPS_L) {
                                FN_L = FN_L - 1;
                            }
                            if (SFT_L > CAPS_L) {
                                SFT_L = SFT_L - 1;
                            }
                            if (FN_SFT_L > CAPS_L) {
                                FN_SFT_L = FN_SFT_L - 1;
                            }
                            if (CTRL_L > CAPS_L) {
                                CTRL_L = CTRL_L - 1;
                            }
                        }
                    }
                    TOT_L   = TOT_L - 1;
                    CAPS_L  = 0;
                    CAPS_TF = false;
                    LYR_SWP;
                    return true;
                }
                return false;
            }
            return false;

        case CC_FN:
            if (record->event.pressed) {
                if (FN_TF == false) {
                    FN_TF  = true;
                    RGB_FN = true;
                    TOT_L  = TOT_L + 1;
                    FN_L   = TOT_L;
                    LYR_SWP;
                    return false;
                }
            } else {
                if (FN_TF == true) {
                    if (RGB_FN == true) {
                        RGB_FN = false;
                    } else {
                        if ((FN_L > 0) && (FN_L < TOT_L)) {
                            if (CAPS_L > FN_L) {
                                CAPS_L = CAPS_L - 1;
                            }
                            if (SFT_L > FN_L) {
                                SFT_L = SFT_L - 1;
                            }
                            if (FN_SFT_L > FN_L) {
                                FN_SFT_L = FN_SFT_L - 1;
                            }
                            if (CTRL_L > FN_L) {
                                CTRL_L = CTRL_L - 1;
                            }
                        }
                    }
                    FN_TF = false;
                    TOT_L = TOT_L - 1;
                    FN_L  = 0;
                    LYR_SWP;
                    return true;
                }
            }
            return false;

        case CC_LSFT:
            if (record->event.pressed) {
                if (SFT_TF == false) {
                    if (RGB_SFT == false) {
                        RGB_SFT = true;
                        SFT_TF  = true;
                        TOT_L   = TOT_L + 1;
                        SFT_L   = TOT_L;
                        LYR_SWP;
                        return false;
                    }
                }
            } else {
                if (SFT_TF == true) {
                    if (RGB_SFT == true) {
                        RGB_SFT = false;
                    } else {
                        if ((SFT_L > 0) && (SFT_L < TOT_L)) {
                            if (CAPS_L > SFT_L) {
                                CAPS_L = CAPS_L - 1;
                            }
                            if (FN_L > SFT_L) {
                                FN_L = FN_L - 1;
                            }
                            if (FN_SFT_L > SFT_L) {
                                FN_SFT_L = FN_SFT_L - 1;
                            }
                            if (CTRL_L > SFT_L) {
                                CTRL_L = CTRL_L - 1;
                            }
                        }
                    }
                    SFT_TF = false;
                    TOT_L  = TOT_L - 1;
                    SFT_L  = 0;
                    LYR_SWP;
                    return true;
                }
            }
            return false;





        case FN_SFT:
            if (record->event.pressed) {
                if (FN_SFT_TF == true) {
                    FN_SFT_TF = false;
                    if (RGB_FN_SFT) {
                        RGB_FN_SFT = false;
                    }
                    if ((FN_SFT_L > 0) && (FN_SFT_L < TOT_L)) {
                        if (CAPS_L > FN_SFT_L) {
                            CAPS_L = CAPS_L - 1;
                        }
                        if (FN_L > FN_SFT_L) {
                            FN_L = FN_L - 1;
                        }
                        if (SFT_L > FN_SFT_L) {
                            SFT_L = SFT_L - 1;
                        }
                        if (CTRL_L > FN_SFT_L) {
                            CTRL_L = CTRL_L - 1;
                        }
                    }
                    TOT_L  = TOT_L - 1;
                    FN_SFT_L = 0;
                    LYR_SWP;
                    return true;
                } else {
                    FN_SFT_TF = true;
                    RGB_FN_SFT = true;
                    TOT_L  = TOT_L + 1;
                    CAPS_L = TOT_L;
                    LYR_SWP;
                    return true;
                }
                return false;
            }
            return false;



        case KC_LCTL:
            if (record->event.pressed) {
                CTRL_TF = true;
                layer_on(_CTRL);
                TOT_L = TOT_L + 1;
                CTRL_L = TOT_L;
                register_code(LYR_SWP);
                return false;
            } else {
                if (CTRL_TF == true) {
                    CTRL_TF = false;
                    layer_off(_CTRL);
                    if ((CTRL_L > 0) && (CTRL_L < TOT_L)) {
                        if (CAPS_L > CTRL_L) {
                            CAPS_L = CAPS_L - 1;
                        }
                        if (FN_L > CTRL_L) {
                            FN_L = FN_L - 1;
                        }
                        if (FN_SFT_L > SFT_L) {
                            FN_SFT_L = FN_SFT_L - 1;
                        }
                        if (SFT_L > CTRL_L) {
                            SFT_L = SFT_L - 1;
                        }
                    }
                    TOT_L  = TOT_L - 1;
                    CTRL_L = 0;
                    register_code(LYR_SWP);
                    return true;
                }
                return false;
            }
            return false;




    }
    return true;
};


layer_state_t layer_state_set_user(layer_state_t state) {
    // Use `static` variable to remember the previous status.
    static bool adjust_on = false;

    if (CAPS_TF != IS_LAYER_ON_STATE(state, _CAPS)) {
        adjust_on = !adjust_on;
        if (adjust_on) { // Just entered the ADJUST layer.

        } else { // Just exited the ADJUST layer.

        }
    }
    switch (get_highest_layer(state)) {
        case _CAPS:
            
            break;
        case _FN:
            
            break;


            return state;
    };


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {


    if (RGB_BASE) {
        //  a      =  0    1    2    3    4    5    6    7    8    9
        int lmin[] = {0,   47,  50,  63,  66,  76,  83,  92,  93 };
        int lmax[] = {47,  50,  63,  66,  76,  83,  92,  93,  97 };
        int a;
        int LEDr[] = {0,   255, 0,   255, 0,   255, 0,   255, 0  };
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0  };
        int LEDb[] = {255, 255, 255, 255, 255, 255, 255, 255, 255};
        for (a = 0; a < 9; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    } else if (RGB_CAPS) {
        //  a      =  0    1    2    3    4    5    6    7    8
        int lmin[] = {0,   34,  44,  47,  50,  59,  66,  73 };
        int lmax[] = {34,  44,  47,  50,  59,  66,  73,  97 };
        int a;
        int LEDr[] = {0,   0,   0,   255, 0,   0,   0,   0  };
        int LEDg[] = {0,   255, 0,   0,   255, 0,   255, 0  };
        int LEDb[] = {255, 255, 255, 0,   255, 255, 255, 255};
        for (a = 0; a < 8; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    } else if (RGB_FN) {
        //  a      =  0    1    2    3    4    5    6    7    8    9    10   11   12
        int lmin[] = {0,   2,   17,  63,  66,  76,  80,  82,  84,  85,  86,  93 };
        int lmax[] = {2,   17,  63,  66,  76,  80,  82,  84,  85,  86,  93,  97 };
        int a;
        int LEDr[] = {0,   255, 0,   255, 0,   255, 0,   255, 0,   255, 0,   255};
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  };
        int LEDb[] = {255, 72,  255, 0,   255, 0,   255, 0,   255, 0,   255, 72 };
        for (a = 0; a < 12; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    } else if (RGB_SFT) {
        //  a      =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
        int lmin[] = {0,   2,   17,  30,  34,  44,  47,  50,  59,  61,  63,  66,  73,  76,  80,  82,  83 };
        int lmax[] = {2,   17,  30,  34,  44,  47,  50,  59,  61,  63,  66,  73,  76,  80,  82,  83,  97 };
        int a;
        int LEDr[] = {255, 0,   255, 0,   0,   255, 0,   0,   255, 0,   255, 0,   255, 255, 0,   255, 0  };
        int LEDg[] = {0,   0,   36,  0,   255, 36,  0,   255, 36,  0,   0,   255, 36,  0,   0,   0,   0  };
        int LEDb[] = {0,   255, 0,   255, 255, 0,   255, 255, 0,   255, 0,   255, 0,   0,   255, 0,   255};
        for (a = 0; a < 17; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    } else if (RGB_FN_SFT) {
        //  a      =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18
        int lmin[] = {0,   2,   17,  30,  34,  44,  47,  50,  59,  61,  63,  66,  73,  76,  80,  82,  83,  93 };
        int lmax[] = {2,   17,  30,  34,  44,  47,  50,  59,  61,  63,  66,  73,  76,  80,  82,  83,  93,  97 };
        int a;
        int LEDr[] = {255, 255, 255, 0,   0,   255, 0,   0,   255, 0,   255, 0,   255, 255, 0,   255, 0,   255};
        int LEDg[] = {0,   0,   36,  0,   255, 36,  0,   255, 36,  0,   0,   255, 36,  0,   0,   0,   0,   0  };
        int LEDb[] = {0,   72,  0,   255, 255, 0,   255, 255, 0,   255, 0,   255, 0,   0,   255, 0,   255, 72 };
        for (a = 0; a < 18; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    } else if (RGB_CTRL) {
        //  a      =  0    1    2    3    4    5    6    7    8    9    10   11
        int lmin[] = {0,   39,  44,  51,  52,  66,  72,  80,  82,  92,  93 };
        int lmax[] = {39,  44,  51,  52,  66,  72,  80,  82,  92,  93,  97 };
        int a;
        int LEDr[] = {0,   255, 0,   255, 0,   255, 0,   255, 0,   255, 0  };
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  };
        int LEDb[] = {255, 72,  255, 72,  255, 72,  255, 0,   255, 0,   255};
        for (a = 0; a < 11; a++) {
            led_min = lmin[a];
            led_max = lmax[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[a] * brite_adj / 255, LEDg[a] * brite_adj / 255, LEDb[a] * brite_adj / 255);
            }
        }
        return true;


    }
    return true;
}




/*





            if (SFT_L == 0) {
                if (IS_LAYER_ON(_SFT)) {
                    layer_off(_SFT);
                };
                if (SFT_TF) {
                    SFT_TF = !SFT_TF;
                };
                if (SFT_RC) {
                    SFT_RC = !SFT_RC;
                    unregister_code(KC_LSFT);
                };
                return true;
            } else



                if (FN_L == 0) {
                    if (IS_LAYER_ON(_FN)) {
                        layer_off(_FN);
                    }
                    return true;
                } else



                if (CAPS_L == 0) {
                    if (IS_LAYER_ON(_CAPS)) {
                        layer_off(_CAPS);
                    };
                    if (CAPS_TF) {
                        CAPS_TF = !CAPS_TF;
                    };
                    if (CAPS_RC) {
                        CAPS_RC = !CAPS_RC;
                    };
                    return true;
                } else

                    if (CAPS_RC && (SFT_L > CAPS_L)) {
                        CAPS_RC = !CAPS_RC;
                        register_code(KC_CAPS);
                        unregister_code(KC_CAPS);
                    };
                    if (!CAPS_RC && (CAPS_L > SFT_L)) {
                        CAPS_RC = !CAPS_RC;
                        register_code(KC_CAPS);
                        unregister_code(KC_CAPS);
                        if (SFT_RC) {
                            SFT_RC = !SFT_RC;
                            unregister_code(KC_LSFT);
                        }
                    };



                    if (CAPS_RC) {
                        CAPS_RC = !CAPS_RC;
                        register_code(KC_CAPS);
                        unregister_code(KC_CAPS);
                    };

                        if (SFT_TF && CTRL_TF) {
                            if (SFT_L > CTRL_L) {
                                if (!SFT_RC && !CTRL_RC) {
                                    if (CTRL_L > FN_SFT_L) {
                                        register_code(KC_LCTL);
                                        register_code(KC_LSFT);
                                    } else if ((CTRL_L < FN_SFT_L) && (FN_SFT_L > 0)) {
                                        register_code(KC_LSFT);
                                    }
                                } else if (SFT_RC && !CTRL_RC) {
                                    if (CTRL_L > FN_SFT_L) {
                                        unregister_code(KC_LSFT);
                                        register_code(KC_LCTL);
                                        register_code(KC_LSFT);
                                    }
                                } else if (!SFT_RC && CTRL_RC) {
                                    if (CTRL_L > FN_SFT_L) {
                                        register_code(KC_LSFT);
                                    } else if ((CTRL_L < FN_SFT_L) && (FN_SFT_L > 0)) {
                                        unregister_code(KC_LCTL);
                                        register_code(KC_LSFT);
                                    }
                                }
                            } else if (CTRL_L > SFT_L) {
                                if (!SFT_RC && !CTRL_RC) {
                                    if (SFT_L > FN_SFT_L) {
                                        register_code(KC_LSFT);
                                        register_code(KC_LCTL);
                                    } else if ((SFT_L < FN_SFT_L) && (FN_SFT_L > 0)) {
                                        register_code(KC_LCTL);
                                    }
                                } else if (SFT_RC && !CTRL_RC) {
                                    if (SFT_L > FN_SFT_L) {
                                        register_code(KC_LCTL);
                                    }
                                } else if (!SFT_RC && CTRL_RC) {
                                    if (CTRL_L > FN_SFT_L) {
                                        register_code(KC_LSFT);
                                    } else if (CTRL_L < FN_SFT_L) {
                                        unregister_code(KC_LCTL);
                                        register_code(KC_LSFT);
                                    }
                                }

                            }
                        } else if (!SFT_RC && (SFT_TF || FN_SFT_TF)) {
                            SFT_RC = !SFT_RC;
                            register_code(KC_LSFT);
                        };
                        if (!CTRL_RC && CTRL_TF && (CTRL_L > FN_SFT_L)) {
                            CTRL_RC = !CTRL_RC;
                            register_code(KC_LCTL);
                        };




                        if (SFT_RC) {
                            SFT_RC = !SFT_RC;
                            unregister_code(KC_LSFT);
                        };
                        if (CTRL_RC) {
                            CTRL_RC = !CTRL_RC;
                            unregister_code(KC_LCTL);
                        };

                         else {
                    CAPS_TF   = true;
                    MOD_V     = MOD_V + 1;
                    MOD_TOTAL = MOD_TOTAL + 1;
                    layer_on(_CAPS);
                    if (MOD_TOTAL == 2) {
                        if (MOD_V == 6) {
                            unregister_code(KC_LCTL);
                            MOD_V     = MOD_V - 5;
                            MOD_TOTAL = MOD_TOTAL - 1;
                            return true;
                        } else if (MOD_V == 4) {
                            unregister_code(KC_LSFT);
                            MOD_V     = MOD_V - 3;
                            MOD_TOTAL = MOD_TOTAL - 1;
                            return true;
                        }
                        return false;
                    } else if ((MOD_V == 9) && (MOD_TOTAL == 3)) {
                        unregister_code(KC_LCTL);
                        unregister_code(KC_LSFT);
                        MOD_V     = MOD_V - 8;
                        MOD_TOTAL = MOD_TOTAL - 2;
                        return true;
                    }
                    return true;
                }


                if (CAPS_TF) {
                    CAPS_TF   = false;
                    if (SFT_TF) {
                        if (layer_state_is(_SFT)) {
                            register_code(KC_LSFT);
                            MOD_V     = MOD_V + 3;
                            MOD_TOTAL = MOD_TOTAL + 1;
                            return true;
                        } else if (layer_state_is(_CTRL)) {
                            register_code(KC_LSFT);
                            register_code(KC_LCTL);
                            MOD_V     = MOD_V + 8;
                            MOD_TOTAL = MOD_TOTAL + 2;
                            return true;
                        }
                    } else if (CTRL_TF) {
                        if (layer_state_is(_CTRL)) {
                            register_code(KC_LCTL);
                            MOD_V     = MOD_V + 5;
                            MOD_TOTAL = MOD_TOTAL + 1;
                            return true;
                        }
                    }
                    return true;
                }


                                            } else {
                                CAPS_TF = !CAPS_TF;
                                layer_on(_CAPS);
                                if (TOT_L == 0) {
                                    CAPS_L = 1;
                                } else if (TOT_L > 0) {
                                    CAPS_L = TOT_L + 1;
                                }
                                TOT_L = TOT_L + 1;
                                return true;
                            }
                            return false;
                        }
                        return false;
                            if (CAPS_TF) {
                                if (layer_state_is(_CAPS)) {
                                    layer_off(_CAPS);
                                    if ((MOD_V == 1) && (MOD_TOTAL == 1)) {
                                        register_code(KC_CAPS);
                                        unregister_code(KC_CAPS);
                                        MOD_V     = MOD_V - 1;
                                        MOD_TOTAL = MOD_TOTAL - 1;
                                    }
                                }
                            };
                            layer_on(_SFT);
                            MOD_V     = MOD_V + 3;
                            MOD_TOTAL = MOD_TOTAL + 1;
                            SFT_TF = true;
                            return false;
                        } else {
                            layer_off(_SFT);
                            SFT_TF    = false;
                            MOD_V     = MOD_V - 3;
                            MOD_TOTAL = MOD_TOTAL - 1;
                            if ((MOD_V == 0) && (MOD_TOTAL == 0)) {
                                if (CAPS_TF) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    MOD_V     = MOD_V + 1;
                                    MOD_TOTAL = MOD_TOTAL + 1;
                                    return true;
                                } else if (layer_state_is(_CTRL)) {
                                    register_code(KC_LCTL);
                                    MOD_V     = MOD_V + 5;
                                    MOD_TOTAL = MOD_TOTAL + 1;
                                    return true;
                                }
                            };
                            return true;
                        }
                        return false;





            if (record->event.pressed) {
                if (layer_state_is(_FN_SFT)) {
                    layer_off(_FN_SFT);
                    if (!SFT_TF) {
                        unregister_code(KC_LSFT);
                        MOD_V     = MOD_V - 3;
                        MOD_TOTAL = MOD_TOTAL - 1;
                    }
                    if (CTRL_TF) {
                        register_code(KC_LCTL);
                        MOD_V     = MOD_V + 5;
                        MOD_TOTAL = MOD_TOTAL + 1;
                    }
                    if (CAPS_TF) {
                        register_code(KC_CAPS);
                        MOD_V     = MOD_V + 1;
                        MOD_TOTAL = MOD_TOTAL + 1;
                    }
                    return true;
                } else {
                    if (!SFT_TF && (MOD_V == 0) && (MOD_TOTAL == 0)) {
                        register_code(KC_LSFT);
                        MOD_V     = MOD_V + 3;
                        MOD_TOTAL = MOD_TOTAL + 1;
                    } else if ((MOD_V == 1) && (MOD_TOTAL == 1)) {
                        unregister_code(KC_CAPS);
                        register_code(KC_LSFT);
                        MOD_V     = MOD_V - 1 + 3;
                    } else if (((MOD_V == 5) && (MOD_TOTAL == 1)) || ((MOD_V == 8) && (MOD_TOTAL == 2))) {
                        unregister_code(KC_LCTL);
                        MOD_V     = MOD_V - 5;
                        MOD_TOTAL = MOD_TOTAL - 1;
                    }
                    layer_on(_FN_SFT);
                    return true;
                }
            }
            return false;




                                    if (record->event.pressed) {
                            if (CAPS_TF && (MOD_V == 1) && (MOD_TOTAL == 1)) {
                                register_code(KC_CAPS);
                                unregister_code(KC_CAPS);
                                layer_off(_CAPS);
                                MOD_V     = MOD_V - 1;
                                MOD_TOTAL = MOD_TOTAL - 1;
                            };
                            CTRL_TF   = true;
                            MOD_V     = MOD_V + 5;
                            MOD_TOTAL = MOD_TOTAL + 1;
                            layer_on(_CTRL);
                            return false;
                        } else {
                            CTRL_TF   = false;
                            MOD_V     = MOD_V - 5;
                            MOD_TOTAL = MOD_TOTAL - 1;
                            layer_off(_CTRL);
                            if (get_highest_layer(layer_state) > 1)
                            if (CAPS_TF && (MOD_V == 0) && (MOD_TOTAL == 0)) {
                                register_code(KC_CAPS);
                                unregister_code(KC_CAPS);
                                MOD_V     = MOD_V + 1;
                                MOD_TOTAL = MOD_TOTAL + 1;
                            };
                            return true;
                        }
                        return false;






*/

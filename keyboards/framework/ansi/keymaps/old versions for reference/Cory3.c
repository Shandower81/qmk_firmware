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
static int  FN_LOCK_L     = 0;
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
                    uprintf("CC_FN_LOCK_on_1  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_FN_LOCK_on_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_FN_LOCK_on_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_FN_LOCK_on_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_FN_LOCK_on_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_FN_LOCK_on_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_FN_LOCK_on_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    FN_LOCK_TF = !FN_LOCK_TF;
                    default_layer_set(_FN_LOCK);
                    layer_off(_BASE);
                    layer_on(_FN_LOCK);
                    uprintf("CC_FN_LOCK_end_1  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_FN_LOCK_end_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_FN_LOCK_end_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_FN_LOCK_end_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_FN_LOCK_end_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_FN_LOCK_end_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_FN_LOCK_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    return true;
                } else {
                    uprintf("CC_FN_LOCK_off_1  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                     \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_FN_LOCK_off_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:   %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_FN_LOCK_0ff_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:     %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_FN_LOCK_off_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:    %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_FN_LOCK_off_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:   %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_FN_LOCK_off_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d              \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_FN_LOCK_off_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    FN_LOCK_TF = !FN_LOCK_TF;
                    default_layer_set(_BASE);
                    layer_off(_FN_LOCK);
                    layer_on(_BASE);
                    layer_state = 0;
                    uprintf("CC_FN_LOCK_end_1  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_FN_LOCK_end_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_FN_LOCK_end_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_FN_LOCK_end_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_FN_LOCK_end_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_FN_LOCK_end_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_FN_LOCK_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    return true;
                }
                return false;
            }
            return false;



        case KC_CAPS:
            if (record->event.pressed) {
                if (!CAPS_TF) {
                    uprintf("CC_CAPS_on_1  IS_LAYER_ON(_CAPS):    %d,  CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_CAPS_on_2  IS_LAYER_ON(_FN):      %d,  FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_CAPS_on_3  IS_LAYER_ON(_SFT):     %d,  SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_CAPS_on_4  IS_LAYER_ON(_FN_LOCK): %d,  FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_CAPS_on_5  IS_LAYER_ON(_CTRL):    %d,  CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_CAPS_on_6    kc: %d,   Layer: %d,      TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_CAPS_on_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    
                    CAPS_TF = !CAPS_TF;
                    uprintf("CC_CAPS_on_8 CAPS_TF: %d\n", CAPS_TF);
                   
                    if (!CAPS_RC && IS_LAYER_OFF(_CAPS)) {
                        if (TOT_L > 0) {
                            if ((FN_L > 0) && FN_TF) {
                                if (IS_LAYER_ON(_FN)) {
                                    layer_off(_FN);
                                    uprintf("CC_CAPS_on_9 IS_LAYER_ON(_FN): %d\n", IS_LAYER_ON(_FN));
                                }
                            }
                            if ((SFT_L > 0) && SFT_TF) {
                                if (IS_LAYER_ON(_SFT)) {
                                    layer_off(_SFT);
                                    uprintf("CC_CAPS_on_10 IS_LAYER_ON(_SFT): %d\n", IS_LAYER_ON(_SFT));
                                }
                                if (SFT_RC) {
                                    unregister_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                    uprintf("CC_CAPS_on_11 SFT_RC: %d\n", SFT_RC);
                                }
                            }
                            if ((CTRL_L > 0) && CTRL_TF) {
                                if (IS_LAYER_ON(_CTRL)) {
                                    layer_off(_CTRL);
                                    uprintf("CC_CAPS_on_14 IS_LAYER_ON(_CTRL): %d\n", IS_LAYER_ON(_CTRL));
                                }
                                if (CTRL_RC) {
                                    unregister_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                    uprintf("CC_CAPS_on_15 CTRL_RC: %d\n", CTRL_RC);
                                }
                            }
                        }
                        uprintf("CC_CAPS_on_16 CAPS_RC: %d, CAPS_L: %d, TOT_L: %d, IS_LAYER_ON(_CAPS): %d\n", CAPS_RC, CAPS_L, TOT_L, IS_LAYER_ON(_CAPS));
                        CAPS_RC = !CAPS_RC;
                        TOT_L   = TOT_L + 1;
                        CAPS_L  = TOT_L;
                        layer_on(_CAPS);
                        uprintf("CC_CAPS_on_17 CAPS_RC: %d, CAPS_L: %d, TOT_L: %d, IS_LAYER_ON(_CAPS): %d\n", CAPS_RC, CAPS_L, TOT_L, IS_LAYER_ON(_CAPS));
                        uprintf("CC_CAPS_on_18        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    }
                    uprintf("CC_CAPS_end_1  IS_LAYER_ON(_CAPS):    %d,  CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_CAPS_end_2  IS_LAYER_ON(_FN):      %d,  FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_CAPS_end_3  IS_LAYER_ON(_SFT):     %d,  SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_CAPS_end_4  IS_LAYER_ON(_FN_LOCK): %d,  FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_CAPS_end_5  IS_LAYER_ON(_CTRL):    %d,  CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_CAPS_end_6    kc: %d,   Layer: %d,      TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_CAPS_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    return true;
                } else {
                    if (CAPS_TF) {
                        uprintf("CC_CAPS_off_1  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                        uprintf("CC_CAPS_off_2  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                        uprintf("CC_CAPS_off_3  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                        uprintf("CC_CAPS_off_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                        uprintf("CC_CAPS_off_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                        uprintf("CC_CAPS_off_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                        uprintf("CC_CAPS_off_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");

                        CAPS_TF = !CAPS_TF;
                        uprintf("CC_CAPS_off_8 CAPS_TF: %d\n", CAPS_TF);
                        if (IS_LAYER_ON(_CAPS) && CAPS_RC) {
                            layer_off(_CAPS);
                            CAPS_RC = !CAPS_RC;
                            uprintf("CC_CAPS_off_9 CAPS_RC: %d, layer_state: %d, Layer: %d IS_LAYER_ON(_CAPS): %d\n", CAPS_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CAPS));
                            if (CAPS_L == TOT_L) {
                                if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                    layer_on(_FN);
                                    uprintf("CC_CAPS_off_10 layer_state: %d, Layer: %d, IS_LAYER_ON(_FN): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_FN));
                                }
                                if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                    layer_on(_SFT);
                                    uprintf("CC_CAPS_off_13 layer_state: %d, Layer: %d, IS_LAYER_ON(_SFT): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_SFT));
                                    if (!SFT_RC) {
                                        register_code(KC_LSFT);
                                        SFT_RC = !SFT_RC;
                                        uprintf("CC_CAPS_off_12 SFT_RC: %d\n", SFT_RC);
                                    }
                                }
                                if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                    layer_on(_CTRL);
                                    uprintf("CC_CAPS_off_15 layer_state: %d, Layer: %d, IS_LAYER_ON(_CTRL): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CTRL));
                                    if (!CTRL_RC) {
                                        register_code(KC_LCTL);
                                        CTRL_RC = !CTRL_RC;
                                        uprintf("CC_CAPS_off_14 kc: %d, CTRL_RC: %d\n", keycode, CTRL_RC);
                                    }
                                }
                            }
                        } else {
                            uprintf("CC_CAPS_off_16 CAPS_L: %d, FN_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", CAPS_L, FN_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
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
                            uprintf("CC_CAPS_off_17 CAPS_L: %d, FN_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", CAPS_L, FN_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
                        }
                        TOT_L  = TOT_L - 1;
                        CAPS_L = 0;
                        uprintf("CC_CAPS_off_18 TOT_L: %d, CAPS_L: %d, layer_state: %d, Layer: %d\n", TOT_L, CAPS_L, layer_state, get_highest_layer(layer_state));
                        uprintf("CC_CAPS_off_19        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    }
                    uprintf("CC_CAPS_end_1  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_CAPS_end_2  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_CAPS_end_3  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_CAPS_end_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_CAPS_end_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_CAPS_end_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_CAPS_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    return true;
                }
            }
            return false;

        case KC_LSFT:
            if (record->event.pressed) {
                if (!SFT_TF) {
                    uprintf("CC_SFT_on_1  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_SFT_on_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_SFT_on_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_SFT_on_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_SFT_on_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_SFT_on_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_SFT_on_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    SFT_TF = !SFT_TF;
                    uprintf("CC_SFT_on_8 SFT_TF: %d\n", SFT_TF);
                    if (!SFT_RC && IS_LAYER_OFF(_SFT)) {
                        if (TOT_L > 0) {
                            if ((CAPS_L > 0) && CAPS_TF) {
                                if (IS_LAYER_ON(_CAPS)) {
                                    layer_off(_CAPS);
                                    uprintf("CC_SFT_on_9 IS_LAYER_ON(_CAPS): %d\n", IS_LAYER_ON(_CAPS));
                                }
                                if (CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                    uprintf("CC_SFT_on_11 kc: %d, CAPS_RC: %d\n", keycode, CAPS_RC);
                                }
                            }
                            if ((FN_L > 0) && FN_TF) {
                                if (IS_LAYER_ON(_FN)) {
                                    layer_off(_FN);
                                    uprintf("CC_SFT_on_12 IS_LAYER_ON(_FN): %d\n", IS_LAYER_ON(_FN));
                                }
                            }
                            if ((CTRL_L > 0) && CTRL_TF) {
                                if (IS_LAYER_ON(_CTRL)) {
                                    layer_off(_CTRL);
                                    uprintf("CC_SFT_on_17 IS_LAYER_ON(_CTRL): %d\n", IS_LAYER_ON(_CTRL));
                                }
                                if ((CTRL_L > CAPS_L) && !CTRL_RC) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                    uprintf("CC_SFT_on_19 kc: %d, CTRL_RC: %d\n", keycode, CTRL_RC);
                                }
                            }
                        }
                        layer_on(_SFT);
                        register_code(KC_LSFT);
                        SFT_RC = !SFT_RC;
                        uprintf("CC_SFT_on_20 kc: %d,, SFT_RC: %d, IS_LAYER_ON(_SFT): %d\n", keycode, SFT_RC, IS_LAYER_ON(_SFT));
                    }
                    TOT_L = TOT_L + 1;
                    SFT_L = TOT_L;
                    uprintf("CC_SFT_on_21 SFT_L: %d, TOT_L: %d\n", SFT_L, TOT_L);
                    uprintf("CC_SFT_on_22        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                }
                uprintf("CC_SFT_end_1  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                uprintf("CC_SFT_end_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                uprintf("CC_SFT_end_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                uprintf("CC_SFT_end_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                uprintf("CC_SFT_end_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                uprintf("CC_SFT_end_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                uprintf("CC_SFT_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                return true;
            } else {
                if (SFT_TF) {
                    uprintf("CC_SFT_off_1  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_SFT_off_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_SFT_off_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_SFT_off_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_SFT_off_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_SFT_off_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_SFT_off_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    SFT_TF = !SFT_TF;
                    uprintf("CC_SFT_off_8 SFT_TF: %d\n", SFT_TF);
                    if (SFT_RC && IS_LAYER_ON(_SFT)) {
                        layer_off(_SFT);
                        unregister_code(KC_LSFT);
                        SFT_RC = !SFT_RC;
                        uprintf("CC_SFT_off_9 kc: %d, SFT_RC: %d, layer_state: %d, Layer: %d, IS_LAYER_ON(_SFT): %d\n", keycode, SFT_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_SFT));
                        if (SFT_L == TOT_L) {
                            if ((CAPS_L == TOT_L - 1) && CAPS_TF && !CAPS_RC && IS_LAYER_OFF(_CAPS)) {
                                layer_on(_CAPS);
                                register_code(KC_CAPS);
                                unregister_code(KC_CAPS);
                                CAPS_RC = !CAPS_RC;
                                uprintf("CC_SFT_off_11 kc: %d, CAPS_RC: %d, layer_state: %d, Layer: %d, IS_LAYER_ON(_CAPS): %d\n", keycode, CAPS_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CAPS));
                            } else if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                layer_on(_FN);
                                uprintf("CC_SFT_off_12 layer_state: %d, Layer: %d, IS_LAYER_ON(_FN): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_FN));
                                if ((CTRL_L > CAPS_L) && CTRL_TF && !CTRL_RC && IS_LAYER_OFF(_CTRL)) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                    uprintf("CC_SFT_off_13 kc: %d, CTRL_RC: %d\n", keycode, CTRL_RC);
                                }
                            } else if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                layer_on(_CTRL);
                                if (!CTRL_RC) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                                uprintf("CC_SFT_off_15 layer_state: %d, Layer: %d, IS_LAYER_ON(_CTRL): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CTRL));
                            }
                        }
                    } else {
                        uprintf("CC_SFT_off_17 FN_L: %d, CAPS_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", FN_L, CAPS_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
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
                        uprintf("CC_SFT_off_18 FN_L: %d, CAPS_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", FN_L, CAPS_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
                    }
                    TOT_L = TOT_L - 1;
                    SFT_L = 0;
                    uprintf("CC_SFT_off_19 TOT_L: %d, SFT_L: %d, layer_state: %d, Layer: %d\n", TOT_L, SFT_L, layer_state, get_highest_layer(layer_state));
                    uprintf("CC_SFT_off_20        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                }
                uprintf("CC_SFT_end_1  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                uprintf("CC_SFT_end_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                uprintf("CC_SFT_end_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                uprintf("CC_SFT_end_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                uprintf("CC_SFT_end_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                uprintf("CC_SFT_end_6    kc: %d,   Layer: %d        TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                uprintf("CC_SFT_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                return true;
            }
            return false;

        case KC_LCTL:
            if (record->event.pressed) {
                if (!CTRL_TF) {
                    uprintf("CC_CTRL_on_1  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_CTRL_on_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_CTRL_on_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_CTRL_on_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_CTRL_on_5  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_CTRL_on_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_CTRL_on_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    CTRL_TF = !CTRL_TF;
                    uprintf("CC_CTRL_on_8 CTRL_TF: %d\n", CTRL_TF);
                    if (!CTRL_RC && IS_LAYER_OFF(_CTRL)) {
                        if (TOT_L > 0) {
                            if ((CAPS_L > 0) && CAPS_TF) {
                                if (IS_LAYER_ON(_CAPS)) {
                                    layer_off(_CAPS);
                                    uprintf("CC_CTRL_on_9 IS_LAYER_ON(_CAPS): %d\n", IS_LAYER_ON(_CAPS));
                                }
                                if (CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                    uprintf("CC_CTRL_on_11 kc: %d, CAPS_RC: %d\n", keycode, CAPS_RC);
                                }
                            }
                            if ((FN_L > 0) && FN_TF) {
                                if (IS_LAYER_ON(_FN)) {
                                    layer_off(_FN);
                                    uprintf("CC_CTRL_on_12 IS_LAYER_ON(_FN): %d\n", IS_LAYER_ON(_FN));
                                }
                            }
/*                          if ((FN_SFT_L > 0) && FN_SFT_TF) {
                                if (IS_LAYER_ON(_FN_SFT)) {
                                    layer_off(_FN_SFT);
                                    uprintf("CC_CTRL_on_14 IS_LAYER_ON(_FN_SFT): %d\n", IS_LAYER_ON(_FN_SFT));
                                }
                                if (FN_SFT_RC) {
                                    unregister_code(KC_LSFT);
                                    FN_SFT_RC = !FN_SFT_RC;
                                    uprintf("CC_CTRL_on_16 kc: %d, FN_SFT_RC: %d\n", keycode, FN_SFT_RC);
                                }
                            }
*/                          if ((SFT_L > 0) && SFT_TF) {
                                if (IS_LAYER_ON(_SFT)) {
                                    layer_off(_SFT);
                                    uprintf("CC_CTRL_on_17 IS_LAYER_ON(_SFT): %d\n", IS_LAYER_ON(_SFT));
                                }
                                if ((SFT_L > CAPS_L) /* && (SFT_L > FN_SFT_L)*/ && !SFT_RC) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                    uprintf("CC_CTRL_on_19 kc: %d, SFT_RC: %d\n", keycode, SFT_RC);
                                }
                            }
                        }
                        layer_on(_CTRL);
                        CTRL_RC = !CTRL_RC;
                        uprintf("CC_CTRL_on_20 kc: %d, CTRL_RC: %d, IS_LAYER_ON(_CTRL): %d\n", keycode, CTRL_RC, IS_LAYER_ON(_CTRL));
                    }
                    TOT_L  = TOT_L + 1;
                    CTRL_L = TOT_L;
                    uprintf("CC_CTRL_on_21 CTRL_L: %d, TOT_L: %d\n", CTRL_L, TOT_L);
                    uprintf("CC_CTRL_on_22        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                }
                uprintf("CC_CTRL_end_1  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                uprintf("CC_CTRL_end_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                uprintf("CC_CTRL_end_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                uprintf("CC_CTRL_end_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                uprintf("CC_CTRL_end_5  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                uprintf("CC_CTRL_end_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                uprintf("CC_CTRL_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                return true;
            } else {
                if (CTRL_TF) {
                    uprintf("CC_CTRL_off_1  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_CTRL_off_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_CTRL_off_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_CTRL_off_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_CTRL_off_5  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_CTRL_off_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_CTRL_off_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    CTRL_TF = !CTRL_TF;
                    uprintf("CC_CTRL_off_8 CTRL_TF: %d\n", CTRL_TF);
                    if (CTRL_RC && IS_LAYER_ON(_CTRL)) {
                        layer_off(_CTRL);
                        unregister_code(KC_LCTL);
                        CTRL_RC = !CTRL_RC;
                        uprintf("CC_CTRL_off_9 kc: %d, CTRL_RC: %d, layer_state: %d, Layer: %d, IS_LAYER_ON(_CTRL): %d\n", keycode, CTRL_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CTRL));
                        if (CTRL_L == TOT_L) {
                            if ((CAPS_L == TOT_L - 1) && CAPS_TF && IS_LAYER_OFF(_CAPS)) {
                                layer_on(_CAPS);
                                if (!CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                                uprintf("CC_CTRL_off_11 kc: %d, CAPS_RC: %d, layer_state: %d, Layer: %d, IS_LAYER_ON(_CAPS): %d\n", keycode, CAPS_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CAPS));
                            } else if ((FN_L == TOT_L - 1) && FN_TF && IS_LAYER_OFF(_FN)) {
                                layer_on(_FN);
                                uprintf("CC_CTRL_off_12 layer_state: %d, Layer: %d, IS_LAYER_ON(_FN): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_FN));
                                if ((SFT_L > CAPS_L) && /* (SFT_L > FN_SFT_L) &&*/ SFT_TF && !SFT_RC && IS_LAYER_OFF(_SFT)) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                    uprintf("CC_CTRL_off_13 kc: %d, SFT_RC: %d\n", keycode, SFT_RC);
                                }
                            } else if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                layer_on(_SFT);
                                uprintf("CC_CTRL_off_14 layer_state: %d, Layer: %d, IS_LAYER_ON(_SFT): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_SFT));
                                if (!SFT_RC) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                    uprintf("CC_CTRL_off_15 kc: %d, SFT_RC: %d\n", keycode, SFT_RC);
                                }
                            } /* else if ((FN_SFT_L == TOT_L - 1) && FN_SFT_TF && IS_LAYER_OFF(_FN_SFT)) {
                                layer_on(_FN_SFT);
                                if (!FN_SFT_RC && !SFT_RC) {
                                    register_code(KC_LSFT);
                                    FN_SFT_RC = !FN_SFT_RC;
                                } else if (!FN_SFT_RC && SFT_RC) {
                                    SFT_RC    = !SFT_RC;
                                    FN_SFT_RC = !FN_SFT_RC;
                                }
                                uprintf("CC_CTRL_off_16 kc: %d, FN_SFT_RC: %d, layer_state: %d, Layer: %d, IS_LAYER_ON(_FN_SFT): %d\n", keycode, FN_SFT_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_FN_SFT));
                            }
*/                      }
                    } else {
                        uprintf("CC_CTRL_off_17 FN_L: %d, CAPS_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", FN_L, CAPS_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
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
/*                          if (FN_SFT_L > CTRL_L) {
                                FN_SFT_L = FN_SFT_L - 1;
                            }
*/                      }
                        uprintf("CC_CTRL_off_18 FN_L: %d, CAPS_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", FN_L, CAPS_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
                    }
                    TOT_L  = TOT_L - 1;
                    CTRL_L = 0;
                    uprintf("CC_CTRL_off_19 TOT_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", TOT_L, CTRL_L, layer_state, get_highest_layer(layer_state));
                    uprintf("CC_CTRL_off_20        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                }
                uprintf("CC_CTRL_end_1  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                uprintf("CC_CTRL_end_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                uprintf("CC_CTRL_end_3  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                uprintf("CC_CTRL_end_4  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                uprintf("CC_CTRL_end_5  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                uprintf("CC_CTRL_end_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                uprintf("CC_CTRL_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                return true;
            }
            return false;



        case MO(_FN):
            if (record->event.pressed) {
                if (!FN_TF) {
                    uprintf("CC_FN_on_1  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_FN_on_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_FN_on_3  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_FN_on_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_FN_on_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_FN_on_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_FN_on_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    FN_TF = !FN_TF;
                    uprintf("CC_FN_on_8 FN_TF: %d\n", FN_TF);
                    if (IS_LAYER_OFF(_FN)) {
                        if (TOT_L > 0) {
                            if ((CAPS_L > 0) && CAPS_TF) {
                                if (IS_LAYER_ON(_CAPS)) {
                                    layer_off(_CAPS);
                                    uprintf("CC_FN_on_9 IS_LAYER_ON(_CAPS): %d\n", IS_LAYER_ON(_CAPS));
                                }
                                if (CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                    uprintf("CC_FN_on_11 kc: %d, CAPS_RC: %d\n", keycode, CAPS_RC);
                                }
                            }
                            if ((SFT_L > 0) && SFT_TF) {
                                if (IS_LAYER_ON(_SFT)) {
                                    layer_off(_SFT);
                                    uprintf("CC_FN_on_12 IS_LAYER_ON(_SFT): %d\n", IS_LAYER_ON(_SFT));
                                }
                            }
/*                          if ((FN_SFT_L > 0) && FN_SFT_TF) {
                                if (IS_LAYER_ON(_FN_SFT)) {
                                    layer_off(_FN_SFT);
                                    uprintf("CC_FN_on_14 IS_LAYER_ON(_FN_SFT): %d\n", IS_LAYER_ON(_FN_SFT));
                                }
                                if (FN_SFT_RC && !SFT_RC) {
                                    unregister_code(KC_LSFT);
                                    FN_SFT_RC = !FN_SFT_RC;
                                    uprintf("CC_FN_on_16 kc: %d, FN_SFT_RC: %d\n", keycode, FN_SFT_RC);
                                }
                            }
*/                          if ((CTRL_L > 0) && CTRL_TF) {
                                if (IS_LAYER_ON(_CTRL)) {
                                    layer_off(_CTRL);
                                    uprintf("CC_FN_on_17 IS_LAYER_ON(_CTRL): %d\n", IS_LAYER_ON(_CTRL));
                                }
                            }
                        }
                        layer_on(_FN);
                        uprintf("CC_FN_on_19 IS_LAYER_ON(_FN): %d\n", IS_LAYER_ON(_FN));
                    }
                    TOT_L = TOT_L + 1;
                    FN_L  = TOT_L;
                    uprintf("CC_FN_on_20 FN_L: %d, TOT_L: %d\n", FN_L, TOT_L);
                    uprintf("CC_FN_on_21        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                }
                uprintf("CC_FN_end_1  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                uprintf("CC_FN_end_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                uprintf("CC_FN_end_3  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                uprintf("CC_FN_end_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                uprintf("CC_FN_end_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                uprintf("CC_FN_end_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                uprintf("CC_FN_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                return true;
            } else {
                if (FN_TF) {
                    uprintf("CC_FN_off_1  IS_LAYER_ON(_FN):      %d,   FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                    uprintf("CC_FN_off_2  IS_LAYER_ON(_CAPS):    %d,   CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                    uprintf("CC_FN_off_3  IS_LAYER_ON(_SFT):     %d,   SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                    uprintf("CC_FN_off_4  IS_LAYER_ON(_FN_LOCK): %d,   FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                    uprintf("CC_FN_off_5  IS_LAYER_ON(_CTRL):    %d,   CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                    uprintf("CC_FN_off_6    kc: %d,   Layer: %d,       TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                    uprintf("CC_FN_off_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                    FN_TF = !FN_TF;
                    uprintf("CC_FN_off_8 FN_TF: %d\n", FN_TF);
                    if (IS_LAYER_ON(_FN)) {
                        layer_off(_FN);
                        uprintf("CC_FN_off_9 layer_state: %d, Layer: %d, IS_LAYER_ON(_FN): %d\n", layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_FN));
                        if (FN_L == TOT_L) {
                            if ((CAPS_L == TOT_L - 1) && CAPS_TF && IS_LAYER_OFF(_CAPS)) {
                                layer_on(_CAPS);
                                if (!CAPS_RC) {
                                    register_code(KC_CAPS);
                                    unregister_code(KC_CAPS);
                                    CAPS_RC = !CAPS_RC;
                                }
                                uprintf("CC_FN_off_10 kc: %d, CAPS_RC: %d layer_state: %d, Layer: %d, IS_LAYER_ON(_CAPS): %d\n", keycode, CAPS_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CAPS));
                            } else if ((SFT_L == TOT_L - 1) && SFT_TF && IS_LAYER_OFF(_SFT)) {
                                layer_on(_SFT);
                                if (!SFT_RC) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                }
                                uprintf("CC_FN_off_11 kc: %d, SFT_RC: %d layer_state: %d, Layer: %d, IS_LAYER_ON(_SFT): %d\n", keycode, SFT_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_SFT));
                                if ((CTRL_L > CAPS_L) && /* (CTRL_L > FN_SFT_L) &&*/ CTRL_TF && !CTRL_RC && IS_LAYER_OFF(_CTRL)) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                    uprintf("CC_FN_off_12 kc: %d, CTRL_RC: %d\n", keycode, CTRL_RC);
                                }
                            }/* else if ((FN_SFT_L == TOT_L - 1) && FN_SFT_TF && IS_LAYER_OFF(_FN_SFT)) {
                                layer_on(_FN_SFT);
                                if (!FN_SFT_RC && !SFT_RC) {
                                    register_code(KC_LSFT);
                                    FN_SFT_RC = !FN_SFT_RC;
                                } else if (!FN_SFT_RC && SFT_RC) {
                                    FN_SFT_RC = !FN_SFT_RC;
                                    SFT_RC    = !SFT_RC;
                                }
                                uprintf("CC_FN_off_13 kc: %d, FN_SFT_RC: %d, layer_state: %d, Layer: %d, IS_LAYER_ON(_FN_SFT): %d\n", keycode, FN_SFT_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_FN_SFT));
                            }*/ else if ((CTRL_L == TOT_L - 1) && CTRL_TF && IS_LAYER_OFF(_CTRL)) {
                                layer_on(_CTRL);
                                if (!CTRL_RC) {
                                    register_code(KC_LCTL);
                                    CTRL_RC = !CTRL_RC;
                                }
                                uprintf("CC_FN_off_14 kc: %d, CTRL_RC: %d, layer_state: %d, Layer: %d, IS_LAYER_ON(_CTRL): %d\n", keycode, CTRL_RC, layer_state, get_highest_layer(layer_state), IS_LAYER_ON(_CTRL));
                                if ((SFT_L > CAPS_L) &&/* (SFT_L > FN_SFT_L) &&*/ SFT_TF && !SFT_RC && IS_LAYER_OFF(_SFT)) {
                                    register_code(KC_LSFT);
                                    SFT_RC = !SFT_RC;
                                    uprintf("CC_FN_off_15 kc: %d, SFT_RC: %d\n", keycode, SFT_RC);
                                }
                            }
                        }
                    } else {
                        uprintf("CC_FN_off_16 FN_L: %d, CAPS_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", FN_L, CAPS_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
                        if ((FN_L > 0) && (FN_L < TOT_L)) {
                            if (CAPS_L > FN_L) {
                                CAPS_L = CAPS_L - 1;
                            }
                            if (SFT_L > FN_L) {
                                SFT_L = SFT_L - 1;
                            }
/*                          if (FN_SFT_L > FN_L) {
                                FN_SFT_L = FN_SFT_L - 1;
                            }
*/                          if (CTRL_L > FN_L) {
                                CTRL_L = CTRL_L - 1;
                            }
                        }
                        uprintf("CC_FN_off_17 FN_L: %d, CAPS_L: %d, SFT_L: %d, FN_LOCK_L: %d, CTRL_L: %d, layer_state: %d, Layer: %d\n", FN_L, CAPS_L, SFT_L, FN_LOCK_L, CTRL_L, layer_state, get_highest_layer(layer_state));
                    }
                    TOT_L = TOT_L - 1;
                    FN_L  = 0;
                    uprintf("CC_FN_off_18 TOT_L: %d, FN_L: %d, layer_state: %d, Layer: %d\n", TOT_L, FN_L, layer_state, get_highest_layer(layer_state));
                    uprintf("CC_FN_on_19        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                }
                uprintf("CC_FN_end_1  IS_LAYER_ON(_FN):      %d,  FN_L:      %d,   FN_TF:      %d                      \n", IS_LAYER_ON(_FN), FN_L, FN_TF);
                uprintf("CC_FN_end_2  IS_LAYER_ON(_CAPS):    %d,  CAPS_L:    %d,   CAPS_TF:    %d,   CAPS_RC:   %d     \n", IS_LAYER_ON(_CAPS), CAPS_L, CAPS_TF, CAPS_RC);
                uprintf("CC_FN_end_3  IS_LAYER_ON(_SFT):     %d,  SFT_L:     %d,   SFT_TF:     %d,   SFT_RC:    %d     \n", IS_LAYER_ON(_SFT), SFT_L, SFT_TF, SFT_RC);
                uprintf("CC_FN_end_4  IS_LAYER_ON(_FN_LOCK): %d,  FN_LOCK_L: %d,   FN_LOCK_TF: %d                      \n", IS_LAYER_ON(_FN_LOCK), FN_LOCK_L, FN_LOCK_TF);
                uprintf("CC_FN_end_5  IS_LAYER_ON(_CTRL):    %d,  CTRL_L:    %d,   CTRL_TF:    %d,   CTRL_RC:   %d     \n", IS_LAYER_ON(_CTRL), CTRL_L, CTRL_TF, CTRL_RC);
                uprintf("CC_FN_end_6    kc: %d,   Layer: %d,      TOT_L:     %d,         layer_state: %d               \n", keycode, get_highest_layer(layer_state), TOT_L, layer_state);
                uprintf("CC_FN_end_7        #####################          &&&&&&&&&&&&&&&&&&&&&&&&&&          @@@@@@@@@@@@@@@@@@@@@@@\n");
                return true;
            }
            return false;




    }
    return false;
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (IS_LAYER_ON(_BASE) && (TOT_L == 0)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10    11
        int lmin[] = {0,   2,   15,  47,  50,  63,  66,  76,  83,  92,  93 };
        int lmax[] = {2,   15,  47,  50,  63,  66,  76,  83,  92,  93,  97 };
        int a;
        int LEDr[] = {0,   60,  0,   255, 0,   255, 0,   255, 0,   255, 0  };
        int LEDg[] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  };
        int LEDb[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
        for (a = 0; a < 11; a++) {
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
//          a      =  0    1    2    3    4    5    6    7    8
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

    } else if (IS_LAYER_ON(_SFT)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
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


    } else if (IS_LAYER_ON(_CTRL)) {
//          a      =  0    1    2    3    4    5    6    7    8    9    10   11
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

    } else if (IS_LAYER_ON(_FN)) {
        //          a      =  0    1    2    3    4    5    6    7    8    9    10   11   12
        int lmin[] = {0, 2, 17, 63, 66, 76, 80, 82, 84, 85, 86, 93};
        int lmax[] = {2, 17, 63, 66, 76, 80, 82, 84, 85, 86, 93, 97};
        int a;
        int LEDr[] = {0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255};
        int LEDg[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int LEDb[] = {255, 72, 255, 0, 255, 0, 255, 0, 255, 0, 255, 72};
        for (a = 0; a < 12; a++) {
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


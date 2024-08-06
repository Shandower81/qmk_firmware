// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "framework.h"
#include "print.h"

enum _layers {
  _BASE,
  _FN_LOCK,
  //_CAPS,
  //_SFT,
  //_CTRL,
  _FN,
};
//                            0     1          2 3 6   3 4 7  4 5 8   5 6 9     6          7                8     9                 10           11           12
//                            base  fn_lock    caps_XX sft_XX ctrl_XX fn_XX     # of layer ACTIVE_RGB_LAYER X_val DEFUALT_LAYER_val X_change_val update?_val
static int  HOLD_L[12]     = {1,    0,         0,      0,     0,      0,        0,         2,               0,    0,                0,           0         };
static bool HOLD_RC[6]     = {true, false,     false,  false, false,  false};
static bool HOLD_TF[6]     = {true, false,     false,  false, false,  false};
static int  X_val          = 0;
static int  brite_adj      = 255;
static int  rgb_brite_val = 0;

const uint8_t rgb_array[8][18] = {
    {0, 5, 43, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
    {1, 2, 5,  44, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
    {3, 6, 8,  10, 12, 14, 16, 17, 22, 24, 30, 32, 34, 36, 41, 50, 50, 50},
    {3, 7, 10, 13, 18, 19, 22, 27, 28, 30, 32, 34, 36, 41, 50, 50, 50, 50},
    {4, 7, 11, 12, 18, 20, 21, 23, 27, 29, 31, 32, 34, 36, 41, 50, 50, 50},
    {3, 6, 9,  10, 12, 14, 15, 17, 22, 25, 26, 28, 30, 33, 34, 36, 42, 50},
    {3, 6, 8,  10, 12, 14, 16, 17, 22, 24, 30, 32, 35, 37, 38, 39, 40, 41} };



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
       KC_ESC,       KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
       KC_GRV,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
       KC_TAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
       KC_CAPS,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
       KC_LSFT,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
       KC_LCTL,      MO(_FN), KC_LGUI, KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
   ),

   [_FN_LOCK] = LAYOUT(
       DF(_BASE),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
       KC_GRV,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
       KC_TAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
       KC_CAPS,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
       KC_LSFT,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
       KC_LCTL,      MO(_FN), KC_LGUI, KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_HOME, KC_PGUP, KC_PGDN, KC_END
   ),
/*
   [_CAPS] = LAYOUT(
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
       _______,     _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
   ),

   [_SFT] = LAYOUT(
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
       _______,     _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
   ),

   [_CTRL] = LAYOUT(
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
       _______,     _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
   ),
*/
   [_FN] = LAYOUT(
       DF(_FN_LOCK), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
       _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
       _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
       _______,      _______, QK_BOOT, RGB_STEP,          RGB_TOG,                  _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
   ),
};



bool LAYER_CHANGE_X(int X_val) {
    uprintf("0  X_val: %u, HOLD_L[6]: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u\n", X_val, HOLD_L[6], get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK));
    X_val = HOLD_L[8];
    uprintf("\nINIT HOLD_L[12]       0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
    uprintf("INIT HOLD_TF[6]       0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
    uprintf("INIT HOLD_RC[6]       0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
    uprintf("\n1  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, default_layer_state: %u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), default_layer_state);
    if (HOLD_L[10] != X_val) {
        uprintf("\nBEGIN HOLD_L[12]                                                            8: %u,       10: %u\n", HOLD_L[8], HOLD_L[10]);
        uprintf("\n0  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK));
        HOLD_L[10] = X_val;
        uprintf("1  X_val: %u, HOLD_L[12]                                                     8: %u,       10: %u\n", X_val, HOLD_L[8], HOLD_L[10]);
        if ((X_val > 5) && (HOLD_L[X_val - 4] > 0)) {
            uprintf("\nOFF_BEGIN HOLD_L[12]  0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
            uprintf("OFF_BEGIN HOLD_TF[6]  0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            uprintf("OFF_BEGIN HOLD_RC[6]  0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            X_val = (X_val - 4);
            uprintf("\n0  X_val: %u, (HOLD_L[X_val]: %u, HOLD_L[12]                                                      11: %u,\n", X_val, HOLD_L[X_val], HOLD_L[11]);
            HOLD_L[11] = 1;
            uprintf("0  HOLD_L[12]                                                                                   11: %u\n", HOLD_L[11]);
            if (HOLD_TF[X_val]) {
                uprintf("\n1  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                HOLD_TF[X_val] = false;
                uprintf("1  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            }
            /*          if (HOLD_RC[2] && (HOLD_L[X_val] == HOLD_L[6]) && (HOLD_L[2] > 0) && (X_val == 2)) {
                            uprintf("\n3  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                            register_code(KC_CAPS);
                            unregister_code(KC_CAPS);
                            // host_keyboard_led_state().caps_lock = false;
                            HOLD_L[X_val] = 0;
                            uprintf("\n3  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                        } else
            */
            if (!HOLD_RC[2] && (HOLD_L[X_val] == HOLD_L[6]) && (HOLD_L[2] > 0) && (HOLD_L[2] == HOLD_L[6] - 1)) {
                uprintf("\n4  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                register_code(KC_CAPS);
                unregister_code(KC_CAPS);
                // host_keyboard_led_state().caps_lock = true;
                HOLD_L[X_val] = 0;
                HOLD_RC[2]    = true;
                uprintf("4  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("4  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u, X_val: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5], X_val);
            }
            if (HOLD_RC[X_val]) {
                uprintf("\n2  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                HOLD_RC[X_val] = false;
                uprintf("2  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                if (HOLD_TF[3] && (HOLD_L[3] > 0) && (HOLD_L[3] > HOLD_L[2]) && (!HOLD_RC[3]) && (get_mods() != (MOD_BIT(KC_LSFT)))) {
                    uprintf("\n5  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("5  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("5  HOLD_RC[6]                      2: %u, 3: %u\n", HOLD_RC[2], HOLD_RC[3]);
                    uprintf("\n5  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    add_mods(MOD_BIT(KC_LSFT));
                    HOLD_RC[3] = true;
                    uprintf("5  HOLD_RC[6]                            3: %u\n", HOLD_RC[3]);
                    uprintf("\n5  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                }
                if (HOLD_TF[4] && (HOLD_L[4] > 0) && (HOLD_L[4] > HOLD_L[2]) && (!HOLD_RC[4]) && (get_mods() != (MOD_BIT(KC_LCTL)))) {
                    uprintf("\n6  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("6  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("6  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                    uprintf("\n6  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    add_mods(MOD_BIT(KC_LCTL));
                    HOLD_RC[4] = true;
                    uprintf("\n6  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("6  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("6  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                    uprintf("\n6  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                }
                if ((HOLD_L[7] == 6) && (HOLD_L[9] == 1)) {
                    HOLD_L[9] = 0;
                }
            }
            if (HOLD_L[X_val] > 0) {
                uprintf("\n7  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("7  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("7  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                uprintf("\n7  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                HOLD_L[X_val] = 0;
              uprintf("7  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
            }
            if (HOLD_L[6] > 0) {
                uprintf("\n8  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("8  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("8  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                uprintf("\n8  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                for (int a = 2; a < 6; a++) {
                    if (HOLD_L[a] == (HOLD_L[6] - 1)) {
                        if ((HOLD_L[6] - 1) == 0) {
                            if (HOLD_L[0] == 1) {
                                HOLD_L[7] = 0;
                            } else if (HOLD_L[1] == 1) {
                                HOLD_L[7] = 1;
                            }
                        } else {
                            HOLD_L[7] = (a + 4);
                        }
                    }
                }
                HOLD_L[6] = HOLD_L[6] - 1;
                uprintf("8  HOLD_L[12]                                                      6: %u\n", HOLD_L[6]);
            } else {
                if (HOLD_TF[0]) {
                    uprintf("\n9  HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("9  HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("9  HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                    uprintf("\n9  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    HOLD_L[9] = 0;
                    uprintf("9  HOLD_L[12]                                                                      9: %u\n", HOLD_L[9]);
                }
                if (HOLD_TF[1]) {
                    uprintf("\n10 HOLD_L[12]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("10 HOLD_TF[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("10 HOLD_RC[6]          0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                    uprintf("\n10 X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    HOLD_L[9] = 1;
                    uprintf("10 HOLD_L[12]                                                                      9: %u\n", HOLD_L[9]);
                }
            }
            if (HOLD_L[6] == 0) {
                HOLD_L[7] = 2;
            }
            uprintf("\nOFF_END HOLD_L[12]    0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
            uprintf("OFF_END HOLD_TF[6]    0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            uprintf("OFF_END HOLD_RC[6]    0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            uprintf("11 X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK));
        } else if ((X_val < 6) && !HOLD_TF[X_val] && (HOLD_L[X_val] == 0)) {
            HOLD_L[11] = 2;
            uprintf("\nON_BEGIN HOLD_L[12]   0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
            uprintf("ON_BEGIN HOLD_TF[6]   0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            uprintf("ON_BEGIN HOLD_RC[6]   0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            uprintf("\n0  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
            if (X_val > 1) {
                uprintf("\n1  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("1  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("1  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                HOLD_L[6]     = HOLD_L[6] + 1;
                HOLD_L[7]     = X_val + 1;
                HOLD_L[X_val] = HOLD_L[6];
                uprintf("\n1  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("1  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("1  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            }
            if (X_val == 0) {
                uprintf("\n2  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("2  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("2  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                HOLD_L[0]  = 1;
                HOLD_L[1]  = 0;
                HOLD_L[9]  = 0;
                HOLD_RC[1] = false;
                HOLD_TF[1] = false;
                uprintf("\n2  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("2  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("2  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            } else if (X_val == 1) {
                uprintf("\n3  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("3  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("3  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                HOLD_L[0]  = 0;
                HOLD_L[1]  = 1;
                HOLD_L[9]  = 1;
                HOLD_RC[0] = false;
                HOLD_TF[0] = false;
                uprintf("\n3  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("3  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("3  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            }
            if (HOLD_L[6] == 0) {
                uprintf("\n4  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("4  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("4  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                HOLD_L[7] = X_val;
                uprintf("\n4  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("4  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("4  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            }
            HOLD_TF[X_val]     = true;
            uprintf("5  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
            if (!HOLD_RC[X_val]) {
                uprintf("\n6  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                HOLD_RC[X_val] = true;
                uprintf("6  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                if ((host_keyboard_led_state().caps_lock) && (HOLD_L[2] == HOLD_L[6]) && HOLD_RC[2]) {
                    uprintf("\n7  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("7  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("7  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                    //host_keyboard_led_state().caps_lock = false;
                    HOLD_RC[2] = false;
                    uprintf("\n7  HOLD_RC[6]                     2: %u\n", HOLD_RC[2]);
                    uprintf("\n7  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                }
                if (HOLD_TF[3] && (HOLD_L[3] == 0) && (get_mods() == (MOD_BIT(KC_LSFT))) && HOLD_RC[3]) {
                    uprintf("\n8  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("8  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("8  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                    uprintf("\n8  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    HOLD_RC[3] = false;
                    del_mods(MOD_BIT(KC_LSFT));
                    uprintf("8  HOLD_RC[6]                           3: %u,                                                 get_mods(): %9u\n", HOLD_RC[3], get_mods());
                }
                if (HOLD_TF[4] && (HOLD_L[4] == 0) && (get_mods() == (MOD_BIT(KC_LCTL))) && HOLD_RC[4]) {
                    uprintf("\n9  HOLD_L[12]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("9  HOLD_TF[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                    uprintf("9  HOLD_RC[6]         0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                    uprintf("9  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    HOLD_RC[4] = false;
                    del_mods(MOD_BIT(KC_LCTL));
                    uprintf("9  HOLD_RC[6]                     2: %u,                                      get_mods(): %9u\n", HOLD_RC[2], get_mods());
                }
                if (HOLD_L[7] == 6) {
                    HOLD_L[9]  = 1;
                }
            }
            uprintf("\nON_END HOLD_L[12]     0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
            uprintf("ON_END HOLD_TF[6]     0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            uprintf("ON_END HOLD_RC[6]     0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            uprintf("2  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
        }
    } else {
        HOLD_L[11] = 0;
    }
    uprintf("\nEND HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
    uprintf("END HOLD_TF[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
    uprintf("END HOLD_RC[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
    uprintf("2  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
    return false;
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

        case DF(_BASE):
            if (record->event.pressed) {
                uprintf("\nDF(_BASE) HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nDF(_BASE)  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                if (HOLD_L[1] == 1) {
                    HOLD_L[8] = 0;
                    LAYER_CHANGE_X(X_val);
                    uprintf("\nDF(_BASE) HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("\nDF(_BASE)  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    return true;
                }
            }
            return false;

        case DF(_FN_LOCK):
            if (record->event.pressed) {
                uprintf("\nDF(_FN_LOCK) HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nDF(_FN_LOCK)  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                if (HOLD_L[0] == 1) {
                    HOLD_L[8] = 1;
                    LAYER_CHANGE_X(X_val);
                    uprintf("\nDF(_FN_LOCK) HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("\nDF(_FN_LOCK)  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    return true;
                }
            }
            return false;

        case KC_CAPS:
            if (record->event.pressed) {
                if (!HOLD_TF[2]) {
                    uprintf("\nKC_CAPS_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("\nKC_CAPS_ON X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    HOLD_L[8] = 2;
                    LAYER_CHANGE_X(X_val);
                    uprintf("\nKC_CAPS_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("\nKC_CAPS_ON X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    return true;
                } else if (HOLD_TF[2]) {
                    uprintf("\nKC_CAPS_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("\nKC_CAPS_OFF X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    HOLD_L[8] = 6;
                    LAYER_CHANGE_X(X_val);
                    uprintf("\nKC_CAPS_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                    uprintf("\nKC_CAPS_OFF X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                    return true;
                }
            }
            return false;

        case KC_LSFT:
            if (record->event.pressed) {
                uprintf("\nKC_LSFT_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LSFT_ON X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                HOLD_L[8] = 3;
                LAYER_CHANGE_X(X_val);
                uprintf("\nKC_LSFT_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LSFT_ON  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                return true;
            } else {
                uprintf("\nKC_LSFT_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LSFT_OFF  X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                HOLD_L[8] = 7;
                LAYER_CHANGE_X(X_val);
                uprintf("\nKC_LSFT_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LSFT_OFF X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                return true;
            }
            return false;

        case KC_LCTL:
            if (record->event.pressed) {
                uprintf("\nKC_LCTL_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LCTL_ON X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                HOLD_L[8] = 4;
                LAYER_CHANGE_X(X_val);
                uprintf("\nKC_LCTL_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LCTL_ON X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                return true;
            } else {
                uprintf("\nKC_LCTL_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LCTL_OFF X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                HOLD_L[8] = 8;
                LAYER_CHANGE_X(X_val);
                uprintf("\nKC_LCTL_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nKC_LCTL_OFF X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                return true;
            }
            return false;

        case MO(_FN):
            if (record->event.pressed) {
                uprintf("\nMO(_FN)_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nMO(_FN)_ON X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                HOLD_L[8] = 5;
                LAYER_CHANGE_X(X_val);
                uprintf("\nMO(_FN)_ON HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nMO(_FN)_ON X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                return true;
            } else {
                uprintf("\nMO(_FN)_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nMO(_FN)_OFF X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                HOLD_L[8] = 9;
                LAYER_CHANGE_X(X_val);
                uprintf("\nMO(_FN)_OFF HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("\nMO(_FN)_OFF X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
                return true;
            }
            return false;
    }
    return false;
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (HOLD_L[11] != 0) {
        uprintf("\nRGB_0 HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
        uprintf("RGB_0 HOLD_TF[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
        uprintf("RGB_0 HOLD_RC[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
        uprintf("\nRGB_0 X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
    }
    // rgb_array[][]  =  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44
    int lmin[]  = {0, 0, 2, 17, 17, 30, 34, 34, 39, 39, 44, 44, 47, 47, 50, 51, 51, 52, 50, 59, 59, 61, 63, 63, 66, 66, 72, 66, 73, 73, 76, 76, 80, 80, 82, 82, 83, 83, 84, 85, 86, 92, 92, 93, 93};
    int lmax[]  = {17, 2, 17, 30, 30, 34, 39, 44, 44, 44, 47, 47, 50, 50, 51, 52, 52, 63, 59, 63, 61, 63, 66, 66, 76, 72, 73, 73, 76, 76, 80, 80, 82, 82, 83, 83, 92, 84, 85, 86, 92, 93, 93, 97, 97};
    int color[] = {3, 8, 7, 1, 0, 1, 1, 5, 1, 0, 1, 0, 2, 8, 1, 0, 1, 1, 5, 1, 0, 1, 2, 8, 1, 0, 1, 5, 1, 0, 2, 8, 2, 8, 2, 8, 1, 8, 0, 8, 1, 2, 8, 3, 7};
    //  color[]  =  0      1     2        3       4     5     6       7      8
    // color name =  pinkr  blue  magenta  violet  rose  cyan  orange  burnt  red
    int LEDr[] = {255, 0, 255, 60, 255, 0, 255, 255, 255};
    int LEDg[] = {0, 0, 0, 0, 40, 255, 128, 36, 0};
    int LEDb[] = {72, 255, 255, 255, 150, 255, 0, 0, 0};

    static int max_array = 18;
    static int a         = 0;
    static int b         = 0;
    static int c         = 0;
    for (a = 0; a < 2; a++) {
        if (a == 0) {
            b = HOLD_L[9];
            if (HOLD_L[11] != 0) {
                uprintf("\nRGB_1 HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("RGB_1 HOLD_TF[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("RGB_1 HOLD_RC[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                uprintf("RGB_1            a: %u, b: %u,       max_array: %2u\n", a, b, max_array);
            }
        } else if (a == 1) {
            b = HOLD_L[7];
            if (HOLD_L[11] != 0) {
                uprintf("\nRGB_2 HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
                uprintf("RGB_2 HOLD_TF[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
                uprintf("RGB_2 HOLD_RC[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
                uprintf("RGB_2            a: %u, b: %u,       max_array: %2u\n", a, b, max_array);
            }
        }
        for (c = 0; c < 18; c++) {
            if (rgb_array[b][c] != 50) {
                max_array = (c + 1);
            }
        }
        for (int d = 0; d < max_array; d++) {
            int e   = rgb_array[b][d];
            led_min = lmin[e];
            led_max = lmax[e];
            if (HOLD_L[11] != 0) {
                uprintf("_\nRGB_3  a: %u, b: %u, c: %2u, d: %2u, e: %2u,       led_min: %2u, led_max: %2u, max_array: %2u\n", a, b, c, d, e, led_min, led_max, max_array);
            }
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, LEDr[color[e]] * brite_adj / 255, LEDg[color[e]] * brite_adj / 255, LEDb[color[e]] * brite_adj / 255);
            }
        }
    }
    if (HOLD_L[11] != 0) {
        uprintf("\nRGB_4 HOLD_L[12]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u,       6: %u, 7: %u, 8: %u, 9: %u, 10: %u, 11: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7], HOLD_L[8], HOLD_L[9], HOLD_L[10], HOLD_L[11]);
        uprintf("RGB_4 HOLD_TF[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
        uprintf("RGB_4 HOLD_RC[6]        0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
        uprintf("\nRGB_4 X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u, get_mods(): %9u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK), get_mods());
        HOLD_L[11] = 0;
    }
    return true;
}

/*      if (!HOLD_TF[X_val]) {
            HOLD_TF[X_val] = true;
            if (HOLD_L[X_val] == 0) {
                if (IS_LAYER_ON(_BASE)) {
                    Y_val      = 0;
                    HOLD_TF[1] = false;
                    HOLD_RC[1] = false;
                    HOLD_L[0]  = 1;
                    HOLD_L[1]  = 0;
                }
                if (IS_LAYER_ON(_FN_LOCK)) {
                    Y_val      = 1;
                    HOLD_TF[0] = false;
                    HOLD_RC[0] = false;
                    HOLD_L[0]  = 0;
                    HOLD_L[1]  = 1;
                }
                if (X_val > 1) {
                    if (HOLD_RC[2] && HOLD_TF[2] && (HOLD_L[2] == HOLD_L[6])) {
                        register_code(KC_CAPS);
                        unregister_code(KC_CAPS);
                        HOLD_RC[2] = false;
                        uprintf("1 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                    }
                    if (HOLD_RC[3] && HOLD_TF[3] && ((X_val == 2) || (HOLD_L[3] < HOLD_L[2]))) {
                        unregister_code(KC_LSFT);
                        HOLD_RC[3] = false;
                        uprintf("2 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                    }
                    if (HOLD_RC[4] && HOLD_TF[4] && ((X_val == 2) || (HOLD_L[4] < HOLD_L[2]))) {
                        unregister_code(KC_LCTL);
                        HOLD_RC[4] = false;
                        uprintf("3 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                    }
                    uprintf("4 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                    HOLD_L[6]     = HOLD_L[6] + 1;
                    HOLD_L[X_val] = HOLD_L[6];
                }
                HOLD_RC[X_val] = true;
                layer_on(X_val);
                HOLD_L[7] = X_val;
                uprintf(" HOLD_RC[X_val]: %u, HOLD_L[X_val]: %u, ACTIVE_LYR: %u, HOLD_L[7]: %u, IS_LAYER_ON(X_val): %u\n", HOLD_RC[X_val], HOLD_L[X_val], get_highest_layer(layer_state), HOLD_L[7], IS_LAYER_ON(X_val));
            }
            uprintf("END_ON HOLD_L[]       0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u, 6: %u, 7: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7]);
            uprintf("END_ON HOLD_TF[]      0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            uprintf("END_ON HOLD_RC[]      0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            uprintf("X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK));
            return false;
        } else if (HOLD_TF[X_val]) {
            uprintf("BEGIN_OFF HOLD_L[]    0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u, 6: %u, 7: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7]);
            uprintf("BEGIN_OFF HOLD_TF[]   0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            uprintf("BEGIN_OFF HOLD_RC[]   0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            uprintf("0 X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK));
            HOLD_TF[X_val] = false;
            if (IS_LAYER_ON(X_val)) {
                uprintf("1 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                layer_off(X_val);
                uprintf("2 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                for (int a = 0; a < 6; a++) {
                    uprintf("3 X_val: %u, a: %u, LYR_ON: %u, ACTIVE_LYR: %u\n", X_val, a, IS_LAYER_ON(a), get_highest_layer(layer_state));
                    if ((a < 2) && (X_val < 2) && (X_val != a)) {
                        layer_on(a);
                        uprintf("4 X_val: %u, a: %u, LYR_ON: %u, ACTIVE_LYR: %u\n", X_val, a, IS_LAYER_ON(a), get_highest_layer(layer_state));
                    } else if (HOLD_L[a] == (HOLD_L[6] - 1)) {
                        layer_on(a);
                        uprintf("5 X_val: %u, a: %u, LYR_ON: %u, ACTIVE_LYR: %u\n", X_val, a, IS_LAYER_ON(a), get_highest_layer(layer_state));
                    }
                }
                if (!HOLD_RC[2] && (get_highest_layer(layer_state) == 2)) {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                    HOLD_RC[2] = true;
                    uprintf("6 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                }
                if (!HOLD_RC[3] && HOLD_TF[3] && ((X_val == 2) || (HOLD_L[3] > HOLD_L[2]))) {
                    register_code(KC_LSFT);
                    HOLD_RC[3] = true;
                    uprintf("7 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                }
                if (!HOLD_RC[4] && HOLD_TF[4] && ((X_val == 2) || (HOLD_L[4] > HOLD_L[2]))) {
                    register_code(KC_LCTL);
                    HOLD_RC[4] = true;
                    uprintf("8 X_val: %u, ACTIVE_LYR: %u\n", X_val, get_highest_layer(layer_state));
                }
            }
            if ((HOLD_L[X_val] > 0) && (HOLD_L[X_val] < HOLD_L[6])) {
                for (int b = 2; b < 6; b++) {
                    if ((X_val != b) && (HOLD_L[b] > HOLD_L[X_val])) {
                        HOLD_L[b] = HOLD_L[b] - 1;
                    }
                }
            }
            if (X_val > 1) {
                HOLD_L[6] = HOLD_L[6] - 1;
            }
            HOLD_RC[X_val] = false;
            HOLD_L[X_val]  = 0;
            HOLD_L[7]      = get_highest_layer(layer_state);
            X_val          = HOLD_L[7];
            uprintf("END_OFF HOLD_L[]      0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u, 6: %u, 7: %u\n", HOLD_L[0], HOLD_L[1], HOLD_L[2], HOLD_L[3], HOLD_L[4], HOLD_L[5], HOLD_L[6], HOLD_L[7]);
            uprintf("END_OFF HOLD_TF[]     0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_TF[0], HOLD_TF[1], HOLD_TF[2], HOLD_TF[3], HOLD_TF[4], HOLD_TF[5]);
            uprintf("END_OFF HOLD_RC[]     0: %u, 1: %u, 2: %u, 3: %u, 4: %u, 5: %u\n", HOLD_RC[0], HOLD_RC[1], HOLD_RC[2], HOLD_RC[3], HOLD_RC[4], HOLD_RC[5]);
            uprintf("9 X_val: %u, ACTIVE_LYR: %u, IS_LAYER_ON(_BASE): %u, IS_LAYER_ON(_FN_LOCK): %u\n", X_val, get_highest_layer(layer_state), IS_LAYER_ON(_BASE), IS_LAYER_ON(_FN_LOCK));
            return false;
        }
    }
*/

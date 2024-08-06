// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "factory.h"

enum _layers {
    _NUMLOCK_OFF,
    _NUMLOCK_ON,
    _MOUSE_KEYS,
};

enum Custom_Keys {
    L0,
    L1,
};

#define L0 TO(_NUMLOCK_OFF)
#define L1 TO(_MOUSE_KEYS)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
        ┌───────-┬───────-┬───────-┬───────-┐
 4 keys │ LAYER  │ OPEN   │FUNCTION│ ESCAPE │
        │    3   │CALC APP│  TWO   │        │
        ├───────-┼───────-┼───────-┼───────-┤
 4 keys │Numlock │ DIVIDE │MULTIPLY│ COMMA  │
        │        │        │        │        │
        ├──────-─┼───────-┼───────-┼───────-┤
 4 keys │ Home   │   ↑    │ Page   │ MINUS  │
        │        │        │ Up     │        │
        ├──────-─┼───────-┼───────-┼───────-┤
 4 keys │  ←     │ CLEAR  │   →    │  PLUS  │
        │        │        │        │        │
        ├──────-─┼───────-┼───────-┼───────-┤
 4 keys │ End    │    ↓   │ Page   │ EQUAL  │
        │        │        │ Down   │        │
        ├──────-─┼───────-┼───────-┼───────-┤
 4 keys │ BACK-  │ Insert │ Delete │ NUMPAD │
        │  SPACE │        │        │  ENTER │
        └──────-─┴──────-─┴───────-┴───────-┘
 24 total
*/


    [_NUMLOCK_OFF] = LAYOUT(
        L1,      KC_CALC, KC_F2,   KC_ESC,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PCMM,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_EQL,
        KC_BSPC, KC_P0,   KC_PDOT, KC_PENT
    ),



/*
        ┌───────-┬───────-┬───────-┬───────-┐
        │ ESCAPE │ OPEN   │ EQUAL  │ BACK-  │
        │        │CALC APP│        │  SPACE │
        ├───────-┼───────-┼───────-┼───────-┤
        │Numlock │ COMMA  │FUNCTION│ DIVIDE │
        │        │        │  TWO   │        │
        ├───────-┼───────-┼───────-┼───────-┤
        │ NUMBER │ NUMBER │ NUMBER │MULTIPLY│
        │ SEVEN  │ EIGHT  │  NINE  │        │
        ├───────-┼───────-┼───────-┼───────-┤
        │ NUMBER │ NUMBER │ NUMBER │ MINUS  │
        │  FOUR  │  FIVE  │   SIX  │        │
        ├───────-┼───────-┼───────-┼───────-┤
        │ NUMBER │ NUMBER │ NUMBER │  PLUS  │
        │  ONE   │   TWO  │  THREE │        │
        ├───────-┼───────-┼───────-┼───────-┤
        │ OPEN   │ NUMBER │ PERIOD │ NUMPAD │
        │MOUSEHEY│  ZERO  │        │ ENTER  │
        └───────-┴───────-┴───────-┴───────-┘
*/


    [_NUMLOCK_ON] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),

 
  
/*
       ┌───────-┬───────-┬───────-┬───────-┐
       │ SWITCH │SWITCH  │FUNCTION| ESCAPE │
       │APP WNDW│ WINDOW │  TWO   |        │
       ├───────-┼───────-┼───────-┼───────-┤
       │ LAYER  │ UNDO   │  REDO  │  SAVE  │
       │    0   │        │        │        │
       ├───────-┼───────-┼───────-┼───────-┤
       │ MOUSE  │MSWHEEL │ MOUSE  │  CUT   │
       │ BTTN 1 │   UP   │ BTTN 2 │        │
       ├───────-┼───────-┼───────-┼───────-┤
       │MSWHEEL │MSCURSER│MSWHEEL │ PASTE  │
       │   LEFT │   UP   │  RIGHT │        │
       ├───────-┼───────-┼───────-┼───────-┤
       │MSCURSER│MSWHEEL │MSCURSER│  COPY  │
       │   LEFT │   DOWN │  RIGHT │        │
       ├───────-┼───────-┼───────-┼───────-┤
       │ BACK-  │MSCURSER│  TAB   │ QK-    │
       │  SPACE │  DOWN  │        │   BOOT │
       └───────-┴───────-┴───────-┴──────-─┘
*/


    [_MOUSE_KEYS] = LAYOUT(
        A(KC_TAB), A(KC_F6),  KC_F2,        KC_ESC,
        L0,        C(KC_Z),   C(KC_Y),      C(KC_S),
        KC_BTN1,   KC_WH_U,   KC_BTN2,      C(KC_X),
        KC_WH_L,   KC_MS_U,   KC_WH_R,      C(KC_V),
        KC_MS_L,   KC_WH_D,   KC_MS_R,      C(KC_C),
        KC_BSPC,   KC_MS_D,   KC_TAB,        QK_BOOT
    ),
};



bool led_update_user(led_t led_state) {
    // Change layer if numlock state changes, either triggered by OS or
    // by numlock key on this keyboard
    if (led_state.num_lock) {
        layer_on(_NUMLOCK_ON);
    } else {
        layer_off(_NUMLOCK_ON);
    }
    return true;
}



bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case (L0):
        if (record->event.pressed) {
            if (layer_state_is(_MOUSE_KEYS)) {
                layer_move(_NUMLOCK_OFF);
                return true;
                break;
            }
            else {
                return true;
                break;
            }
        }
    case (L1):
        if (record->event.pressed) {
            if (layer_state_is(_NUMLOCK_OFF)) {
                layer_move(_MOUSE_KEYS);
                return true;
                break;
            }
            else {
                return true;
                break;
            }
        }
        else if (record->event.pressed) {
            if (layer_state_is(_NUMLOCK_ON)) {
                layer_move(_MOUSE_KEYS);
                return true;
                break;
            } else {
                return true;
                break;
            }
        }
        return true;
        break;
    }
    return false;
};



/*  Zeroed Key Numbers for Assigning LED Colors
          ┌───-┬───-┬───-┬───-┐
          │ 0  │ 1  │ 2  │ 3  │
          ├───-┼──-─┼───-┼───-┤
          │ 4  │ 5  │ 6  │ 7  │
          ├────┼-──-┼───-┼───-┤
          │ 8  │ 9  │ 10 │ 11 │
          ├─-──┼────┼───-┼─-──┤
          │ 12 │ 13 │ 14 │ 15 │
          ├──-─┼──-─┼──-─┼──-─┤
          │ 16 │ 17 │ 18 │ 19 │
          ├───-┼──-─┼──-─┼───-┤
          │ 20 │ 21 │ 22 │ 23 │
          └──-─┴───-┴───-┴──-─┘

 RGB_MATRIX_INDICATOR_SET_COLOR( [LED INDEX from above diagram] , RED (Range 0 to 243) , GREEN (Range 0 to 243) , BLUE (Range 0 to 2543) )

      KS0[] = { Zeroed Key Numbers used here }

      KS1[] = { UnZeroed Key Numbers used here }
*/


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is(_NUMLOCK_OFF)) {

    { // ROW 1 COL 1  |  ROW 2 COL 1
            int KS0[] = {0, 4};
            int KS1[] = {1, 5};
            int a;
            for (a = 0; a < 2; a++) {
                led_min = KS0[a];
                led_max = KS1[a];
                for (uint8_t i = led_min; i < led_max; i++) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, 3, 0, 3); }}}

    // ROW 1 COL 2
    led_min = 1;
    led_max = 2;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 3); }

        { // ROW 1 COL 3,4  |  ROW 2 COL 4  |  ROW 5 COL 4  |  ROW 6 COL 1,3
        int KS0[] = {2, 3, 7, 19, 20, 22};
        int KS1[] = {3, 4, 8, 20, 21, 23};
        int a;
        for (a = 0; a < 6; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 3, 3); }}}

    { // ROW 2 COL 1  |  ROW 6 COL 1
        int KS0[] = {5, 6};
        int KS1[] = {6, 7};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 3, 9, 0); }}}

    { // ROW 3 COL 1  |  ROW 5 COL 1
        int KS0[] = {8, 16};
        int KS1[] = {9, 17};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 2, 0); }}}

    { // ROW 3 COL 2  |  ROW 4 COL 1,3  |  ROW 5 COL 2
        int KS0[] = {9, 12, 14, 17};
        int KS1[] = {10, 13, 15, 18};
        int a;
        for (a = 0; a < 4; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 8); }}}

    { // ROW 3 COL 3  |  ROW 5 COL 3
        int KS0[] = {10, 18};
        int KS1[] = {11, 19};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 7, 7, 0); }}}

    { // ROW 3 COL 4  |  ROW 5 COL 4
        int KS0[] = {11, 15};
        int KS1[] = {12, 16};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 2, 0); }}}

    // ROW 4    COL 2
    led_min = 13;
    led_max = 14;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 0, 0); }

    // ROW 6    COL 2
    led_min = 21;
    led_max = 22;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 4, 6); }

    // ROW 6    COL 4
    led_min = 23;
    led_max = 24;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 8, 0); }}


    if (layer_state_is(_NUMLOCK_ON)) {

    { // ROW 1 COL 1  |  ROW 2 COL 1
            int KS0[] = {0, 4};
            int KS1[] = {1, 5};
            int a;
            for (a = 0; a < 2; a++) {
                led_min = KS0[a];
                led_max = KS1[a];
                for (uint8_t i = led_min; i < led_max; i++) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, 3, 0, 3); }}}

    // ROW 1    COL 2
    led_min = 1;
    led_max = 2;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 3); }

    { // ROW 1 COL 3,4  |  ROW 2 COL 4  |  ROW 5 COL 4  |  ROW 6 COL 1,3
        int KS0[] = {2, 3, 7, 19, 20, 22};
        int KS1[] = {3, 4, 8, 20, 21, 23};
        int a;
        for (a = 0; a < 6; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 2, 5); }}}

    { // ROW 2 COL 2,3
        int KS0[] = {5, 6};
        int KS1[] = {6, 7};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 7, 7, 0); }}}

    { // ROW 3 COL 1,3  |  ROW 5 COL 1,3
        int KS0[] = {8, 10, 16, 18};
        int KS1[] = {9, 11, 17, 19};
        int a;  
        for (a = 0; a < 4; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 1, 1); }}}

    { // ROW 3 COL 2  |  ROW 4 COL 1,3  |  ROW 5 COL 2
        int KS0[] = {9, 12, 14, 17};
        int KS1[] = {10, 13, 15, 18};
        int a;
        for (a = 0; a < 4; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 2, 0); }}}

    { // ROW 3 COL 4  |  ROW 5 COL 4
        int KS0[] = {11, 15};
        int KS1[] = {12, 16};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 1, 1, 0); }}}

    // ROW 4    COL 2
    led_min = 13;
    led_max = 14;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 0, 0); }

    // ROW 6    COL 2
    led_min = 21;
    led_max = 22;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 7, 6); }

    // ROW 6    COL 4
    led_min = 23;
    led_max = 24;
    for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 8, 0); }}


    if (layer_state_is(_MOUSE_KEYS)) {

    { // ROW 1 COL 1,2
        int KS0[] = {0, 1};
        int KS1[] = {1, 2};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 8); }}}

    { // ROW 1 COL 3,4  |  ROW 6 COL 1,3
        int KS0[] = {2, 3, 20, 22};
        int KS1[] = {3, 4, 21, 23};
        int a;
        for (a = 0; a < 4; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 3, 3); }}}

    { // ROW 2 COL 1  |  ROW 6 COL 4
        int KS0[] = {4, 23};
        int KS1[] = {5, 24};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 0, 0); }}}

    // ROW 2 COL 2
    led_min = 5;
    led_max = 6;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 7, 7, 0); }

     // ROW 2 COL 3
    led_min = 6;
    led_max = 7;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 3, 3, 0); }

    { // ROW 2 COL 4  |  ROW 4 COL 4
        int KS0[] = {7, 15};
        int KS1[] = {8, 16};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 0, 3); }}}

    { // ROW 3 COL 1,3
        int KS0[] = {8, 10};
        int KS1[] = {9, 11};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 2, 8); }}}

    { // ROW 3 COL 2  |  ROW 4 COL 1,3  |  ROW 5 COL 2
        int KS0[] = {9, 12, 14, 17};
        int KS1[] = {10, 13, 15, 18};
        int a;
        for (a = 0; a < 4; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 8, 1, 0); }}}

    { // ROW 3 COL 4  |  ROW 5 COL 4
        int KS0[] = {11, 19};
        int KS1[] = {12, 20};
        int a;
        for (a = 0; a < 2; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 2, 2, 5); }}}

    { // ROW 4 COL 2  |  ROW 5 COL 1,3  |  ROW 6 COL 2
        int KS0[] = {13, 16, 18, 21};
        int KS1[] = {14, 17, 19, 22};
        int a;
        for (a = 0; a < 4; a++) {
            led_min = KS0[a];
            led_max = KS1[a];
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 8, 0); }}}

    }
    return false;
};



// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(RGB_MATRIX_ENABLE)
const is31_led g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |   R location
 *   |   |         G location
 *   |   |         |         B location
 *   |   |         |         | */
    // Re-arranged in LED ID order so it matches with the physical location array
    //                             LED ID'S:  NEW   (OLD)
    //                                       ORDER  ORDER
    {0,  CS6_SW3,  CS5_SW3,  CS4_SW3}, // LED 1     (6) 
    {0,  CS3_SW3,  CS2_SW3,  CS1_SW3}, // LED 2     (3)
    {0, CS18_SW3, CS17_SW3, CS16_SW3}, // LED 3     (23)
    {0, CS15_SW3, CS14_SW3, CS13_SW3}, // LED 4     (18)
    {0,  CS6_SW1,  CS5_SW1,  CS4_SW1}, // LED 5     (5)
    {0,  CS3_SW1,  CS2_SW1,  CS1_SW1}, // LED 6     (1)
    {0, CS18_SW1, CS17_SW1, CS16_SW1}, // LED 7     (21)
    {0, CS15_SW1, CS14_SW1, CS13_SW1}, // LED 8     (19)
    {0,  CS6_SW2,  CS5_SW2,  CS4_SW2}, // LED 9     (8)
    {0,  CS3_SW2,  CS2_SW2,  CS1_SW2}, // LED 10    (2)
    {0, CS18_SW2, CS17_SW2, CS16_SW2}, // LED 11    (22)
    {0, CS15_SW2, CS14_SW2, CS13_SW2}, // LED 12    (17)
    {0,  CS6_SW4,  CS5_SW4,  CS4_SW4}, // LED 13    (7)
    {0,  CS3_SW4,  CS2_SW4,  CS1_SW4}, // LED 14    (4)
    {0, CS18_SW4, CS17_SW4, CS16_SW4}, // LED 15    (24)
    {0, CS15_SW4, CS14_SW4, CS13_SW4}, // LED 16    (20)
    {0,  CS9_SW2,  CS8_SW2,  CS7_SW2}, // LED 17    (10)
    {0,  CS9_SW4,  CS8_SW4,  CS7_SW4}, // LED 18    (12)
    {0, CS12_SW4, CS11_SW4, CS10_SW4}, // LED 19    (16)
    {0, CS12_SW2, CS11_SW2, CS10_SW2}, // LED 20    (14)
    {0,  CS9_SW1,  CS8_SW1,  CS7_SW1}, // LED 21    (9)
    {0,  CS9_SW3,  CS8_SW3,  CS7_SW3}, // LED 22    (11)
    {0, CS12_SW3, CS11_SW3, CS10_SW3}, // LED 23    (15)
    {0, CS12_SW1, CS11_SW1, CS10_SW1}, // LED 24    (13)

};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {      4,      8,     12,     16,      5,      9,     13,     17, },
  {     20,      6,     10,     14,     18,     22,      7,     15, },
  {     23,      0,      1, NO_LED,      3,     11,     19,     21, },
  { NO_LED, NO_LED, NO_LED, NO_LED,      2, NO_LED, NO_LED, NO_LED, },

}, {
  // LED Index to Physical Position
  //        LED ID'S:  NEW   (OLD)
  //                  ORDER  ORDER
  {   0,   0 }, // LED 1     (6) 
  {  73,   0 }, // LED 2     (3)
  { 150,   0 }, // LED 3     (23)
  { 223,   0 }, // LED 4     (18)
  {   0,  10 }, // LED 5     (5)
  {  73,  10 }, // LED 6     (1)
  { 150,  10 }, // LED 7     (21)
  { 223,  10 }, // LED 8     (19)
  {   0,  24 }, // LED 9     (8)
  {  73,  24 }, // LED 10    (2)
  { 150,  24 }, // LED 11    (22)
  { 223,  24 }, // LED 12    (17)
  {   0,  37 }, // LED 13    (7)
  {  73,  37 }, // LED 14    (4)
  { 150,  37 }, // LED 15    (24)
  { 223,  37 }, // LED 16    (20)
  {   0,  50 }, // LED 17    (10)
  {  73,  50 }, // LED 18    (12)
  { 150,  50 }, // LED 19    (16)
  { 223,  50 }, // LED 20    (14)
  {   0,  64 }, // LED 21    (9)
  {  73,  64 }, // LED 22    (11)
  { 150,  64 }, // LED 23    (15)
  { 223,  64 }, // LED 24    (13)

}, {
  // LED Index to Flag
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4
}
};
#endif

/*
void keyboard_post_init_user(void) {
    // Sync initial numlock state from the host
    if (host_keyboard_led_state().num_lock) {
        
    } else {
        
    }
}
*/


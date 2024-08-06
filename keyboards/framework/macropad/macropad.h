// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#define LAYOUT( \
   K1,    K2,   K3,    K4,   \
   K5,    K6,   K7,    K8,   \
   K9,    K10,  K11,   K12,  \
   K13,   K14,  K15,   K16,  \
   K17,   K18,  K19,   K20,  \
   K21,   K22,  K23,   K24   \
) \
{ \
  {   K5,    K9,    K13,   K17,   K6,    K10,   K14,   K18,   }, \
  {   K21,   K7,    K11,   K15,   K19,   K23,   K8,    K16,   }, \
  {   K24,   K1,    K2,    KC_NO, K4,    K12,   K20,   K22,   }, \
  {   KC_NO, KC_NO, KC_NO, KC_NO, K3,    KC_NO, KC_NO, KC_NO, }, \
}


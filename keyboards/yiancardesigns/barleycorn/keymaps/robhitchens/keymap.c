/* Copyright 2020 Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool is_shift_alt_tab_active = false;
uint16_t shift_alt_tab_timer = 0;

enum layers {
  _BASE,
  _GAMEMODE,
  _MOUSEPAD,
  _SPACEFN,
  _LOWER,
  _RAISE,
  _SHIFTEXTRA,
  _ADJUST,
};

enum keycodes {
  BASE = SAFE_RANGE,
  GAMEMODE,
  MOUSEPAD,
  SPACEFN,
  LOWER,
  RAISE,
//  SHIFTL,
  ADJUST,
  ALT_TAB,
  ALSFH_TAB
};

#define SPACEFN MO(_SPACEFN)
#define TAPSPACE LT(SPACEFN, KC_SPC)
#define GUISPACE LT(SPACEFN, KC_LGUI)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SHIFTEXTRA MO(_SHIFTEXTRA)
#define J_SHIFT LT(SHIFTEXTRA, KC_J)
#define F_SHIFT LT(SHIFTEXTRA, KC_F)
#define K_RAISE LT(RAISE, KC_K)
#define L_LOWER LT(LOWER, KC_L)

//This is the ANSI version of the PCB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ansi( /* Base */
    KC_ESC,   KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSLS, KC_GRV,                              KC_NLCK, KC_PSLS, KC_PAST, KC_PEQL,
    KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSPC,                                      KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_LCTL,  KC_A,     KC_S,     KC_D,  F_SHIFT,  KC_G,  KC_H, J_SHIFT,K_RAISE,L_LOWER,     KC_SCLN,  KC_QUOT,           KC_ENT,                                       KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,            KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,    KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,       KC_RSFT,                      KC_UP,              KC_P1,   KC_P2,   KC_P3,   KC_TRNS,
    KC_LGUI,  KC_LALT,  LOWER,                       TAPSPACE,                                                RAISE, KC_RALT,           KC_LEFT, KC_DOWN, KC_RGHT,          KC_P0,   KC_PDOT, KC_PENT),

[_GAMEMODE] = LAYOUT_ansi( /* Base */
    KC_ESC,   KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSLS, KC_GRV,                              KC_NLCK, KC_PSLS, KC_PAST, KC_PEQL,
    KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSPC,                                      KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_LCTL,  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,                                       KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,            KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,    KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,       KC_RSFT,                      KC_UP,              KC_P1,   KC_P2,   KC_P3,   KC_TRNS,
    GUISPACE,  KC_LALT,  LOWER,                        KC_SPC,                                                RAISE, KC_RALT,           KC_LEFT, KC_DOWN, KC_RGHT,          KC_P0,   KC_PDOT, KC_PENT),

[_MOUSEPAD] = LAYOUT_ansi( /* Base */
    KC_ESC,   KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSLS, KC_GRV,                              KC_TRNS,      KC_TRNS,   KC_TRNS,       KC_TRNS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSPC,                                      KC_MS_WH_UP,  KC_MS_U,   KC_MS_WH_DOWN, KC_TRNS,
    KC_LCTL,  KC_A,     KC_S,     KC_D,  F_SHIFT,  KC_G,  KC_H, J_SHIFT,K_RAISE,L_LOWER,     KC_SCLN,  KC_QUOT,           KC_ENT,                                       KC_MS_L,      KC_MS_D,   KC_MS_R,       KC_MS_BTN1,
    KC_LSFT,            KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,    KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,       KC_RSFT,                      KC_UP,              KC_MS_WH_LEFT,KC_MS_BTN3,KC_MS_WH_RIGHT,KC_TRNS,
    KC_LGUI,  KC_LALT,  LOWER,                       TAPSPACE,                                                RAISE, KC_RALT,           KC_LEFT, KC_DOWN, KC_RGHT,          KC_MS_BTN1,   KC_MS_BTN2, KC_MS_BTN2),

[_SPACEFN] = LAYOUT_ansi( /* Base */
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_PIPE, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_EXLM,  KC_AT,    KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR,KC_ASTR,KC_LPRN, KC_RPRN,  KC_LCBR,  KC_RCBR, KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_GRV,   KC_MINS, KC_EQL, KC_BSLS, KC_PIPE, KC_LBRC,KC_RBRC,KC_TRNS, KC_COLN,  KC_DQUO,           KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,            KC_TRNS,  KC_TILD, KC_UNDS,KC_PLUS, KC_TRNS, KC_LCBR,KC_RCBR,KC_LT,   KC_GT,    KC_QUES,       KC_TRNS,                      KC_UP,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                               KC_TRNS, KC_TRNS,         KC_LEFT, KC_DOWN, KC_RGHT,          KC_TRNS, KC_TRNS, KC_TRNS),

[_LOWER] = LAYOUT_ansi( /* Base */
    KC_TRNS,  KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_MS_WH_UP,  KC_MS_U,      KC_MS_WH_DOWN, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_MS_L,        KC_MS_D,      KC_MS_R,     KC_TRNS,       KC_TRNS, KC_TRNS, KC_MS_BTN1,KC_MS_BTN2,KC_TRNS, KC_TRNS,  KC_TRNS,         KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,                  KC_MS_WH_LEFT,KC_MS_BTN3,  KC_MS_WH_RIGHT,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS,                      KC_UP,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,        KC_TRNS,                                KC_TRNS,                                               KC_TRNS, KC_TRNS,       KC_LEFT, KC_DOWN, KC_RGHT,          KC_TRNS, KC_TRNS, KC_TRNS),

[_RAISE] = LAYOUT_ansi( /* Base */
    KC_TRNS,  KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  ALSFH_TAB,      KC_UP,        ALT_TAB,     KC_TRNS,       KC_TRNS, KC_DEL,  KC_PSCR,   KC_INS,    KC_HOME, KC_PGUP,  KC_TRNS, KC_TRNS, KC_DEL,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_LEFT,        KC_DOWN,      KC_RIGHT,    KC_TRNS,       KC_CAPS, KC_ESC,  KC_APP,    KC_TRNS,   KC_END,  KC_PGDN,  KC_TRNS,         KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,                      KC_UP,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,        KC_TRNS,                                KC_TRNS,                                               KC_TRNS, KC_TRNS,       KC_LEFT, KC_DOWN, KC_RGHT,          KC_TRNS, KC_TRNS, KC_TRNS),

[_SHIFTEXTRA] = LAYOUT_ansi( /* Base */
    KC_TRNS,  KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  S(KC_Q),        S(KC_W),      S(KC_E),     S(KC_R),       S(KC_T), S(KC_Y), S(KC_U),   S(KC_I),   S(KC_O),  S(KC_P),   S(KC_LBRC), S(KC_RBRC), KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  S(KC_A),        S(KC_S),      S(KC_D),     S(KC_F),       S(KC_G), S(KC_H), S(KC_J),   S(KC_K),   S(KC_L),  S(KC_COLN),S(KC_QUOT),         KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  S(KC_Z),        S(KC_X),      S(KC_C),     S(KC_V),       S(KC_B), S(KC_N), S(KC_M),   S(KC_COMM),S(KC_DOT),S(KC_SLSH),     KC_TRNS,                      KC_UP,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,        KC_TRNS,                                KC_TRNS,                                               KC_TRNS, KC_TRNS,       KC_LEFT, KC_DOWN, KC_RGHT,          KC_TRNS, KC_TRNS, KC_TRNS),
[_ADJUST] = LAYOUT_ansi( /* Base */
    KC_TRNS,  BASE,    GAMEMODE, MOUSEPAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  RESET,   DEBUG,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,         KC_TRNS,                                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                                            KC_UP,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,        KC_TRNS,                                KC_TRNS,                                               KC_TRNS, KC_TRNS,       KC_LEFT, KC_DOWN, KC_RGHT,          KC_TRNS, KC_TRNS, KC_TRNS),
/*
[0] = LAYOUT_ansi( 
    KC_GESC,  KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL,                            KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,                                    KC_P7,   KC_P8,   KC_P9,   KC_PEQL,
    KC_CAPS,  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,                                     KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,            KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,    KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,       KC_RSFT,                      KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_BSPC,
    KC_LCTL,  KC_LGUI,  KC_LALT,                       KC_SPC,                                              KC_RALT, MO(1),           KC_LEFT, KC_DOWN, KC_RGHT,          KC_P0,   KC_PDOT, KC_PENT),

[1] = LAYOUT_ansi( 
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RESET,    KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS,                       KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_VOLU,  KC_VOLD,  KC_MUTE,                                KC_TRNS,                                                    KC_TRNS,  KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
*/
};


layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  //state = update_tri_layer_state(state, _SPACEFN, _RAISE, _SHIFTL);
  return state;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_BASE);
      }
      return false;
      break;
    case GAMEMODE:
      if(record->event.pressed){
        print("mode just switched to gamemode");
        set_single_persistent_default_layer(_GAMEMODE);
      }
      return false;
      break;
    case MOUSEPAD:
        if(record->event.pressed){
            print("mode just switched to mousepad");
            set_single_persistent_default_layer(_MOUSEPAD);
        }
        return false;
        break;
    case ALT_TAB:
        if(record->event.pressed){
            if(!is_alt_tab_active){
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            register_code(KC_TAB);
        }else{
            unregister_code(KC_TAB);
        }
        break;
    case ALSFH_TAB:
        if(record->event.pressed){
            if(!is_shift_alt_tab_active){
                is_shift_alt_tab_active = true;
                register_code(KC_LALT);
                register_code(KC_LSHIFT);
            }
            shift_alt_tab_timer = timer_read();
            register_code(KC_TAB);
        }else{
            unregister_code(KC_TAB);
        }
        break;
  }
  return true;
}

void matrix_scan_user(void) {
    if(is_alt_tab_active){
        if(timer_elapsed(alt_tab_timer) > 500){
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    if(is_shift_alt_tab_active){
        if(timer_elapsed(shift_alt_tab_timer) > 500){
            unregister_code(KC_LALT);
            unregister_code(KC_LSHIFT);
            is_shift_alt_tab_active = false;
        }
    }
}
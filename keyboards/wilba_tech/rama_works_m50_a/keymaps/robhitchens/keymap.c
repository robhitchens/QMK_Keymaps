/* Copyright 2020 Jason Williams (Wilba)
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


enum planck_layers {
  _QWERTY,
  _GAMEMODE,
  _SPACEFN,
  _LOWER,
  _RAISE,
  _HOMENUM,
  _SHIFTL,
  _ADJUST,
  _FUNCK,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  GAMEMODE,
  BACKLIT,
  EXT_PLV,
  FUNCK,
  ALT_TAB,
  ALSFH_TAB
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNCK MO(_FUNCK)
#define SPECL MO(_SPECL)
#define SHIFTL MO(_SHIFTL)
#define SPACEFN MO(_SPACEFN)
#define TAPSPACE LT(SPACEFN, KC_SPC)
#define GUISPACE LT(SPACEFN, KC_LGUI)
#define HOMENUM MO(_HOMENUM)
#define F_SHIFT LT(SHIFTL, KC_F)
#define J_SHIFT LT(SHIFTL, KC_J)
#define K_RAISE LT(RAISE, KC_K)
#define L_LOWER LT(LOWER, KC_L)
#define ADJUST MO(_ADJUST)
//#define TAPLEFTARROW LT(LEFTARROWFN, KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
    KC_MS_BTN1,     KC_TAB,    KC_Q,    KC_W,  KC_E,  KC_R,     KC_T,     KC_Y,  KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    KC_MS_BTN2,     KC_LCTL,    KC_A,    KC_S,  KC_D, F_SHIFT, KC_G,     KC_H,  J_SHIFT, K_RAISE,L_LOWER, KC_SCLN, KC_ENT,
    KC_MS_WH_UP,    KC_LSFT,    KC_Z,    KC_X,  KC_C, KC_V,     KC_B,     KC_N,  KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
    KC_MS_WH_DOWN,  KC_ESC, KC_LALT, KC_LGUI, KC_LCTL,FUNCK, TAPSPACE, HOMENUM, KC_RCTL, KC_RALT,   KC_RGUI, ADJUST
),
[_GAMEMODE] = LAYOUT(
    KC_MS_WH_UP,   KC_TAB,     KC_Q,    KC_W,  KC_E,  KC_R,     KC_T,     KC_Y,  KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    KC_MS_WH_DOWN, KC_LCTL,     KC_A,    KC_S,  KC_D,  KC_F,     KC_G,     KC_H,  KC_J,    KC_K,    KC_L, KC_SCLN, KC_ENT,
    KC_MS_BTN1,    KC_LSFT,     KC_Z,    KC_X,  KC_C,  KC_V,     KC_B,     KC_N,  KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
    ADJUST,    KC_ESC, KC_LALT, GUISPACE, FUNCK, RAISE,   KC_SPC, HOMENUM, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
),
[_SPACEFN] = LAYOUT(
    _______, _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
    _______, _______, KC_QUOT,  KC_GRV, KC_MINS,  KC_EQL, KC_BSLS, KC_PIPE, KC_LBRC, KC_RBRC, KC_DQUO, KC_COLN,  _______,
    _______, _______, KC_DQUO, KC_TILD, KC_UNDS, KC_PLUS, KC_QUOT, KC_LCBR, KC_RCBR,   KC_LT,   KC_GT, KC_QUES, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MSTP, KC_VOLD, KC_VOLU, KC_MPLY
),
/* Lower
 * ,-------------------------------------------------------------------------------------.
 * |   ~  |MsWhLft| MsUp |MsWhRht|      |   !  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+-------+------+-------+------+------+------+------+------+------+------+------|
 * |      |MsLft  |MsDwn | MsRht |      |   &  |   $  |   _  |   +  |   {  |   }  |  |   |
 * |------+-------+------+-------+------+------+------+------+------+------+------+------|
 * |      |MsWhDwn|MsBtn3|MsWhUp |      |   #  |   @  |   %  |   <  |   >  |   ?  |      |
 * |------+-------+------+-------+------+------+------+------+------+------+------+------|
 * |      |       |      |       |      |MsBtn1|MsBtn2|      | Next | Vol- | Vol+ | Play |
 * `-------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  _______, KC_TILD, KC_MS_WH_UP,    KC_MS_U, KC_MS_WH_DOWN, _______, _______, _______,    _______,    _______, _______, _______, _______, \
  _______, _______,       KC_MS_L,    KC_MS_D,        KC_MS_R, _______, _______, _______, KC_MS_BTN1, KC_MS_BTN2, _______, _______, _______, \
  _______, _______, KC_MS_WH_LEFT, KC_MS_BTN3,    KC_MS_WH_RIGHT, _______, _______, _______,    _______,    _______, _______, _______, _______, \
  _______,       _______,    _______,        _______, _______, _______, _______,    _______,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |  Up  |      |      |      |   [  |   ]  |  Ins | Home | PgUp |PrnScn|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS | Left |  Dwn |Right |      |      |      |   -  |   =  | End  | PgDn |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
      _______, _______, ALSFH_TAB,   KC_UP, ALT_TAB, _______, _______, _______, KC_PSCR,  KC_INS, KC_HOME, KC_PGUP,  KC_DEL, \
      _______, _______,   KC_LEFT, KC_DOWN,KC_RIGHT, _______, KC_CAPS,  KC_ESC,  KC_APP, _______,  KC_END, KC_PGDN, _______, \
      _______, _______,   XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, \
      _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),
[_HOMENUM] = LAYOUT(
      _______,  KC_F12,   KC_F1,   KC_F2,  KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
      _______, _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_SHIFTL] = LAYOUT(
    _______, _______,    S(KC_Q), S(KC_W),  S(KC_E),  S(KC_R), S(KC_T),  S(KC_Y),  S(KC_U), S(KC_I),  S(KC_O), S(KC_P), _______,
    _______, _______,    S(KC_A), S(KC_S),  S(KC_D),  S(KC_F), S(KC_G),  S(KC_H),  S(KC_J), S(KC_K),  S(KC_L), S(KC_SCLN), S(KC_QUOT),
    _______, _______,    S(KC_Z), S(KC_X),  S(KC_C),  S(KC_V), S(KC_B),  S(KC_N),  S(KC_M), S(KC_COMM),  S(KC_DOT), S(KC_SLSH), _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT(//TODO add switch for qwerty game mode
    QWERTY, _______, QK_BOOT,  DB_TOGG,   EF_DEC, ES_DEC, BR_DEC, H1_DEC, S1_DEC, H2_DEC,  S2_DEC, _______, KC_DEL ,
    GAMEMODE, _______, _______, _______,  EF_INC, ES_INC, BR_INC, H1_INC, S1_INC, H2_INC,  S2_INC, _______,  _______,
    _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

/* Funck (Funck)
 * ,-----------------------------------------------------------------------------------.
 * |   +  |   1  |   2  |   3  |      |      |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   -  |   4  |   5  |   6  |      |      |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   *  |  7   |   8  |   9  |      |      |      |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   /  |  0   |   .  |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 */
[_FUNCK] = LAYOUT(
    _______, KC_PLUS,     KC_1,    KC_2,    KC_3,  _______, _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
    _______, KC_MINUS,    KC_4,    KC_5,    KC_6,  _______, _______, _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
    _______, KC_ASTR,     KC_7,    KC_8,    KC_9,  _______, _______, _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
    _______, KC_SLSH,     KC_0,  KC_DOT, _______,  _______, _______, _______, _______, _______, _______, _______
),

};

// layer_state_t layer_state_set_user(layer_state_t state) {
//   state = update_tri_layer_state(state, _FUNCK, _HOMENUM, _ADJUST);
//   return state;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
                register_code(KC_LSFT);
            }
            shift_alt_tab_timer = timer_read();
            register_code(KC_TAB);
        }else{
            unregister_code(KC_TAB);
        }
        break;
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
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
            unregister_code(KC_LSFT);
            is_shift_alt_tab_active = false;
        }
    }
}

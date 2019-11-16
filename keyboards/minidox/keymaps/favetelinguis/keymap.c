#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3 

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Defines custom keys
#define LGUIE LGUI_T(KC_E)
#define LALTS LALT_T(KC_S)
#define LCTLD LCTL_T(KC_D)
#define LLTF  LT(_LOWER, KC_F)

#define RGUII RGUI_T(KC_I)
#define RALTL RALT_T(KC_L)
#define RCTLK RCTL_T(KC_K)
#define RLTJ  LT(_RAISE, KC_J)

#define TOA  OSL(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    LGUIE,    KC_R,    KC_T,         KC_Y,    KC_U,    RGUII,    KC_O,    KC_P,    \
  KC_A,    LALTS,    LCTLD,    LLTF,    KC_G,         KC_H,    RLTJ,    RCTLK,    RALTL,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                    KC_ESC, KC_BSPC, KC_TAB,         KC_LSPO, KC_SPC, KC_ENT                 \
),

[_LOWER] = LAYOUT( \
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC,\
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_QUOT,\
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS,\
                    KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, TOA                   \
),

[_RAISE] = LAYOUT( \
  KC_EQL, KC_1, KC_2, KC_3, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
  KC_MINS, KC_4, KC_5, KC_6, KC_0,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
  KC_RBRC, KC_7, KC_8, KC_9, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
                    KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO                    \
),

[_ADJUST] =  LAYOUT( \
  KC_NO, KC_F1, KC_F2, KC_F3, KC_F12,      KC_NO, KC_NO, KC_RGUI, KC_NO, KC_NO, \
  KC_NO, KC_F4, KC_F5, KC_F6, KC_F11,      KC_NO, KC_RSFT, KC_RCTRL, KC_ALGR, KC_NO, \
  RESET, KC_F7, KC_F8, KC_F9, KC_F10,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
                    KC_NO, KC_NO, KC_NO,      KC_INS,  KC_DEL, KC_NO \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

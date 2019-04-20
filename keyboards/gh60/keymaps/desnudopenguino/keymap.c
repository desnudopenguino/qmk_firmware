#include QMK_KEYBOARD_H

/* LAYER NAME VARIABLES */
#define _DV 0
#define _QW 1
#define _GM 2
#define _MO 3

/* KEY SHORTNAMES */
#define CTL_ESC CTL_T(KC_ESC)
#define LALT_CB LALT_T(KC_LCBR)
#define RALT_CB RALT_T(KC_RCBR)
#define G_MOD   OSL(_GM)

/* custom keycodes for macros */
enum custom_keycodes {
 G_ADD = SAFE_RANGE,
 G_ADALL,
 G_COM,
 G_COMM,
 G_ADALC
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: dvorak */
  LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,
    CTL_ESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_NO,   KC_ENT,
    KC_LSPO, KC_NO,   KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_NO,   KC_RSPC,
    KC_CAPS, KC_LGUI, LALT_CB,                   KC_SPC,                             KC_NO,   MO(_MO), RALT_CB, G_MOD,   KC_RCTL
  ),

  /* 1: qwerty */
  LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO,   KC_ENT,
    KC_LSPO, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,   KC_RSPC,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_NO,   MO(_MO), KC_RALT, KC_APP,  KC_RCTL
  ),
  /* 2: git macros */
  LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, G_ADALL, _______, _______, _______,
    _______, G_ADD,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, G_ADALC, _______, _______, _______, _______, _______, G_COM,   G_COMM,  _______, _______, _______, _______,
    _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______
  ),
  /* 3: fn */
  LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______, KC_UP,
    RESET,   _______, _______,                   TG(_QW),                            _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
  ),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

void matrix_scan_user(void) {

//Layer LED indicators
    uint32_t layer = layer_state;

    if (layer & (1<<1)) {
        gh60_wasd_leds_on();
        gh60_fn_led_on();
    } else {
        gh60_wasd_leds_off();
        gh60_fn_led_off();
    }

    if (layer & (1<<2)) {
        gh60_poker_leds_on();
        gh60_esc_led_on();
    } else {
        gh60_poker_leds_off();
        gh60_esc_led_off();
    }

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case G_ADD:
        SEND_STRING("git add ");
        return false;break;
      case G_ADALL:
        SEND_STRING("git add .\n");
        return false;break;
      case G_COM:
        SEND_STRING("git commit\n");
        return false;break;
      case G_COMM:
        SEND_STRING("git commit -m \"");
        return false;break;
      case G_ADALC:
        SEND_STRING("git add .&& git commit\n");
        return false;break;
    }
  }
  return true;
};

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
#define CTLALTD LCTL(LALT(KC_DEL))
#define WIN_LF  LCTL(LGUI(KC_LEFT))
#define WIN_RT  LCTL(LGUI(KC_RGHT))

/* custom keycodes for macros */
enum custom_keycodes {
  /* git macros */
  G_ADD = SAFE_RANGE,
  G_COM,
  G_PUSH,
  G_PULL,
  G_STAT,
  G_FETCH,
  G_DIFF,
  G_MERGE,
  G_CHECK,
  /* tmux macros */
  T_NEW,
  T_ATCH,
  T_LIST,
  T_KILL,
  TP_LOAD,
  /* compile this keymap */
  KB_MAKE,
  /* GROUPS */
  GROUP_1,
  GROUP_2,
  GROUP_3,
  GROUP_4,
  GROUP_5,
  GROUP_6,
  GROUP_7,
  GROUP_8,
  GROUP_9,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: dvorak */
  LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,
    CTL_T(KC_ESC), KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_NO,   KC_ENT,
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
    _______, GROUP_1, GROUP_2, GROUP_3, GROUP_4, GROUP_5, GROUP_6, GROUP_7, GROUP_8, GROUP_9, _______, _______, _______, CTLALTD,
    _______, _______, _______, _______, G_PUSH,  _______, G_FETCH, _______, G_COM,   _______, G_PULL,  _______, _______, _______,
    _______, G_ADD,   TP_LOAD, _______, _______, T_LIST,  G_DIFF,  G_CHECK, T_ATCH,  T_NEW,   G_STAT,  _______, _______, _______,
    _______, _______, _______, _______, T_KILL,  _______, _______, G_MERGE, _______, _______, _______, _______, _______, _______,
    KB_MAKE, _______, _______,                   _______,                            _______, _______, WIN_LF,  _______, WIN_RT
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
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git add .\n");
        } else {
            SEND_STRING("git add ");
        }
        layer_off(_GM);
        return false;break;
      case G_COM:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git add . && git commit\ni");
        } else {
            SEND_STRING("git commit\n");
        }
        layer_off(_GM);
        return false;break;
      case G_PUSH:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git push origin master\n");
        } else {
            SEND_STRING("git push ");
        }
        layer_off(_GM);
        return false;break;
      case G_PULL:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git pull origin master\n");
        } else {
            SEND_STRING("git pull ");
        }
        layer_off(_GM);
        return false;break;
      case G_STAT:
        SEND_STRING("git status\n");
        layer_off(_GM);
        return false;break;
      case G_FETCH:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git fetch --all\n");
        } else {
            SEND_STRING("git fetch ");
        }
        layer_off(_GM);
        return false;break;
      case G_DIFF:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git difftool -y\n");
        } else {
            SEND_STRING("git difftool ");
        }
        layer_off(_GM);
        return false;break;
      case G_MERGE:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git merge master\n");
        } else {
            SEND_STRING("git merge ");
        }
        layer_off(_GM);
        return false;break;
      case G_CHECK:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("git checkout -b ");
        } else {
            SEND_STRING("git checkout ");
        }
        layer_off(_GM);
        return false;break;
      case T_NEW:
        SEND_STRING("tmux new -s ");
        layer_off(_GM);
        return false;break;
      case T_ATCH:
        SEND_STRING("tmux attach -t ");
        layer_off(_GM);
        return false;break;
      case T_LIST:
        SEND_STRING("tmux ls\n");
        layer_off(_GM);
        return false;break;
      case T_KILL:
        SEND_STRING("tmux kill-session -t ");
        layer_off(_GM);
        return false;break;
      case TP_LOAD:
        SEND_STRING("tmuxp load ");
        layer_off(_GM);
        return false;break;
      case KB_MAKE:
        if(get_mods() && (MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT))) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            SEND_STRING("gmake gh60:desnudopenguino:dfu\n");
        } else {
            SEND_STRING("gmake gh60:desnudopenguino\n");
        }
        layer_off(_GM);
        return false;break;
      case GROUP_1:
        register_code(KC_RCTL);
        unregister_code(KC_RCTL);
        register_code(KC_LCTL);
        SEND_STRING("1");
        unregister_code(KC_LCTL);
        layer_off(_GM);
        return false;break;
    }
  }
  return true;
};

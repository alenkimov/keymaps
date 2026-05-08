#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  RU_EXLM,
  RU_AT,
  RU_HASH,
  RU_UNDS,
  RU_COLN,
  RU_SCLN,
  RU_GRAVE,
  RU_AMPR,
  RU_QUOTE,
  RU_DQUO,
  RU_QUES,
  RU_ASTR,
  RU_PLUS,
  RU_MINUS,
  RU_EQUAL,
  RU_PIPE,
  DOT_KEY,
  COMMA_KEY,
  SLASH_KEY,
  BSLS_KEY,
  LT_KEY,
  GT_KEY,
  LBRC_KEY,
  RBRC_KEY,
  LCBR_KEY,
  RCBR_KEY,
};



enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
};

enum layers {
  _US,
  _RU,
  _NUM,
  _NAV,
  _GAME,
  _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_US] = LAYOUT_moonlander(
    KC_ESCAPE,      RU_EXLM,        RU_AT,          RU_HASH,        RU_COLN,        RU_SCLN,        RU_GRAVE,                                       KC_TRANSPARENT, RU_AMPR,        RU_ASTR,        RU_QUOTE,       RU_MINUS,       RU_EQUAL,       KC_MEDIA_PLAY_PAUSE,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_NO,                                          KC_NO,          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_NO,          
    DOT_KEY,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_NO,                                                                          KC_NO,          KC_H,           KC_J,           KC_K,           KC_L,           KC_NO,          KC_NO,          
    COMMA_KEY,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_NO,          KC_NO,          SLASH_KEY,      BSLS_KEY,       
    MO(_NAV),       KC_LEFT_GUI,    KC_LEFT_ALT,    TG(_GAME),      MO(_NUM),       KC_ENTER,                                                                                                       TD(DANCE_1),    MO(_FN),        KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_SPACE,       KC_LEFT_SHIFT,  KC_LEFT_CTRL,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_BSPC
  ),
  [_RU] = LAYOUT_moonlander(
    KC_ESCAPE,      RU_EXLM,        RU_AT,          RU_HASH,        RU_COLN,        RU_SCLN,        RU_GRAVE,                                       KC_TRANSPARENT, RU_AMPR,        RU_ASTR,        RU_QUOTE,       RU_MINUS,       RU_EQUAL,       KC_MEDIA_PLAY_PAUSE,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_NO,                                          KC_NO,          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           RU_HA,
    DOT_KEY,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_NO,                                                                          KC_NO,          KC_H,           KC_J,           KC_K,           KC_L,           RU_ZHE,         RU_E,
    COMMA_KEY,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           TD(DANCE_0),    RU_BE,          RU_YU,          SLASH_KEY,      BSLS_KEY,
    MO(_NAV),       KC_LEFT_GUI,    KC_LEFT_ALT,    TG(_GAME),      MO(_NUM),       KC_ENTER,                                                                                                       TD(DANCE_1),    MO(_FN),        KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_SPACE,       KC_LEFT_SHIFT,  KC_LEFT_CTRL,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_BSPC
  ),
  [_NUM] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_CIRC,        KC_7,           KC_8,           KC_9,           RU_RUBL,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_0,           KC_4,           KC_5,           KC_6,           KC_DLR,         KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TILD,        KC_1,           KC_2,           KC_3,           KC_PERC,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [_NAV] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT, 
    KC_TRANSPARENT, KC_HOME,        KC_UP,          KC_END,         KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, LBRC_KEY,      RBRC_KEY,      LCBR_KEY,      RCBR_KEY,      KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_NO,          KC_NO,          KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        LT_KEY,         GT_KEY,         KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_NO,          KC_DELETE,      KC_NO,          KC_NO,          KC_NO,                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [_GAME] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_LEFT_SHIFT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_LEFT_CTRL,   KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MINUS,       KC_EQUAL,       KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [_FN] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_F10,         KC_F11,         KC_F12,         KC_NO,          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_F7,          KC_F8,          KC_F9,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,                                                                          KC_TRANSPARENT, KC_NO,          KC_F4,          KC_F5,          KC_F6,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_NO,          KC_F1,          KC_F2,          KC_F3,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};





extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0} },

    [1] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {91,249,246}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,249,246}, {0,0,0}, {0,0,0}, {41,250,255}, {0,0,0}, {0,0,0}, {0,0,0}, {41,250,255}, {41,250,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {41,250,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,249,246}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,249,246}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

void set_top_row_color(HSV hsv) {
  RGB rgb = hsv_to_rgb_with_value(hsv);
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    if (g_led_config.point[i].y <= 10) {
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

void set_rgb_with_value(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  rgb_matrix_set_color(index, f * r, f * g, f * b);
}

void set_matrix_key_color(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t led = g_led_config.matrix_co[row][col];
  if (led != NO_LED) {
    set_rgb_with_value(led, r, g, b);
  }
}

void set_matrix_row_color(uint8_t row, uint8_t r, uint8_t g, uint8_t b) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    set_matrix_key_color(row, col, r, g, b);
  }
}

void set_russian_flag_color(void) {
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    if (row == 0 || row == 6) {
      set_matrix_row_color(row, 255, 255, 255);
    } else if (row == 1 || row == 2 || row == 7 || row == 8) {
      set_matrix_row_color(row, 0, 57, 166);
    } else if (row == 3 || row == 4 || row == 9 || row == 10) {
      set_matrix_row_color(row, 213, 43, 30);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (!keyboard_config.disable_layer_led) { 
    switch (get_highest_layer(layer_state | default_layer_state)) {
      case _US:
        set_layer_color(0);
        set_top_row_color((HSV){ .h = 0, .s = 255, .v = 255 });
        break;
      case _RU:
        set_layer_color(0);
        set_russian_flag_color();
        break;
      case _NUM:
        set_layer_color(1);
        break;
      case _NAV:
        set_layer_color(2);
        break;
      case _GAME:
        set_layer_color(3);
        break;
      case _FN:
        set_layer_color(4);
        break;
     default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}


typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,      
    SINGLE_HOLD,         
    DOUBLE_TAP,          
    DOUBLE_HOLD,         
    DOUBLE_SINGLE_TAP,   
    MORE_TAPS            
};

static tap dance_state[2];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_M);
        tap_code16(KC_M);
        tap_code16(KC_M);
    }
    if(state->count > 3) {
        tap_code16(KC_M);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_M); break;
        case DOUBLE_TAP: register_code16(RU_HARD); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_M); register_code16(KC_M);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_M); break;
        case DOUBLE_TAP: unregister_code16(RU_HARD); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_M); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if (default_layer_state & (1UL << _RU)) {
        tap_code16(LALT(LSFT(KC_1)));
        default_layer_set(1UL << _US);
    } else {
        tap_code16(LALT(LSFT(KC_2)));
        default_layer_set(1UL << _RU);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
};

void tap_without_shift(uint16_t keycode) {
    uint8_t mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();

    del_mods(MOD_MASK_SHIFT);
    del_oneshot_mods(MOD_MASK_SHIFT);
    send_keyboard_report();

    tap_code16(keycode);

    set_mods(mods);
    set_oneshot_mods(oneshot_mods);
    send_keyboard_report();
}

bool is_ru_base_layer(void) {
    return default_layer_state & (1UL << _RU);
}

void tap_us_symbol(uint16_t keycode) {
    uint8_t mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();
    bool ru_base_layer = is_ru_base_layer();

    del_mods(MOD_MASK_SHIFT);
    del_oneshot_mods(MOD_MASK_SHIFT);
    send_keyboard_report();

    if (ru_base_layer) {
        tap_code16(LALT(LSFT(KC_1)));
    }
    tap_code16(keycode);
    if (ru_base_layer) {
        tap_code16(LALT(LSFT(KC_2)));
    }

    set_mods(mods);
    set_oneshot_mods(oneshot_mods);
    send_keyboard_report();
}

void tap_us_key_preserve_shift(uint16_t keycode) {
    uint8_t mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();
    bool ru_base_layer = is_ru_base_layer();

    if (ru_base_layer) {
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);
        send_keyboard_report();
        tap_code16(LALT(LSFT(KC_1)));
        set_mods(mods);
        set_oneshot_mods(oneshot_mods);
        send_keyboard_report();
    }

    tap_code16(keycode);

    if (ru_base_layer) {
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);
        send_keyboard_report();
        tap_code16(LALT(LSFT(KC_2)));
        set_mods(mods);
        set_oneshot_mods(oneshot_mods);
        send_keyboard_report();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
        }
        return false;
    case RU_EXLM:
        if (record->event.pressed) {
            tap_us_symbol(KC_EXLM);
        }
        return false;
    case RU_AT:
        if (record->event.pressed) {
            tap_us_symbol(KC_AT);
        }
        return false;
    case RU_HASH:
        if (record->event.pressed) {
            tap_us_symbol(KC_HASH);
        }
        return false;
    case RU_UNDS:
        if (record->event.pressed) {
            tap_us_symbol(KC_UNDS);
        }
        return false;
    case RU_COLN:
        if (record->event.pressed) {
            tap_us_symbol(KC_COLN);
        }
        return false;
    case RU_SCLN:
        if (record->event.pressed) {
            tap_us_symbol(KC_SCLN);
        }
        return false;
    case RU_GRAVE:
        if (record->event.pressed) {
            tap_us_symbol(KC_GRAVE);
        }
        return false;
    case RU_AMPR:
        if (record->event.pressed) {
            tap_us_symbol(KC_AMPR);
        }
        return false;
    case RU_QUOTE:
        if (record->event.pressed) {
            tap_us_key_preserve_shift(KC_QUOTE);
        }
        return false;
    case RU_DQUO:
        if (record->event.pressed) {
            tap_us_symbol(KC_DQUO);
        }
        return false;
    case RU_QUES:
        if (record->event.pressed) {
            tap_us_symbol(KC_QUES);
        }
        return false;
    case RU_ASTR:
        if (record->event.pressed) {
            tap_us_symbol(KC_ASTR);
        }
        return false;
    case RU_PLUS:
        if (record->event.pressed) {
            tap_us_symbol(KC_PLUS);
        }
        return false;
    case RU_MINUS:
        if (record->event.pressed) {
            tap_us_key_preserve_shift(KC_MINUS);
        }
        return false;
    case RU_EQUAL:
        if (record->event.pressed) {
            tap_us_key_preserve_shift(KC_EQUAL);
        }
        return false;
    case RU_PIPE:
        if (record->event.pressed) {
            tap_us_symbol(KC_PIPE);
        }
        return false;
    case DOT_KEY:
        if (record->event.pressed) {
            tap_without_shift(is_ru_base_layer() ? RU_DOT : KC_DOT);
        }
        return false;
    case COMMA_KEY:
        if (record->event.pressed) {
            tap_without_shift(is_ru_base_layer() ? RU_COMMA : KC_COMMA);
        }
        return false;
    case SLASH_KEY:
        if (record->event.pressed) {
            tap_us_key_preserve_shift(KC_SLASH);
        }
        return false;
    case BSLS_KEY:
        if (record->event.pressed) {
            tap_us_key_preserve_shift(KC_BSLS);
        }
        return false;
    case LT_KEY:
        if (record->event.pressed) {
            tap_us_symbol(KC_LABK);
        }
        return false;
    case GT_KEY:
        if (record->event.pressed) {
            tap_us_symbol(KC_RABK);
        }
        return false;
    case LBRC_KEY:
        if (record->event.pressed) {
            tap_us_symbol(KC_LBRC);
        }
        return false;
    case RBRC_KEY:
        if (record->event.pressed) {
            tap_us_symbol(KC_RBRC);
        }
        return false;
    case LCBR_KEY:
        if (record->event.pressed) {
            tap_us_symbol(KC_LCBR);
        }
        return false;
    case RCBR_KEY:
        if (record->event.pressed) {
            tap_us_symbol(KC_RCBR);
        }
        return false;
  }
  return true;
}

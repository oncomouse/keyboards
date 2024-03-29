#include "oncomouse.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case TD(TD_SUPER_CTRL):
      return TAPPING_TERM;
  default:
    return TAPPING_TERM;
  }
}

/* Return an integer that corresponds to what kind of tap dance should be
 * executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that
 * another key has been hit under the tapping term. This is typically indicitive
 * that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is
 * true, that means the tapping term has ended, but the key is still being
 * pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap
 * dance is to mimic the "permissive hold" feature. In general, advanced tap
 * dances do not work well if they are used with commonly typed letters. For
 * example "A". Tap dances are best used on non-letter keys that are not hit
 * while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often
 * double tapped in a terminal, or in a web form. So 'tab' would be a poor
 * choice for a tap dance. Letters used in common words as a double. For example
 * 'p' in 'pepper'. If a tap dance function existed on the letter 'p', the word
 * 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however
 * this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t media_tap_state = {.is_press_action = true, .state = TD_NONE};

void media_finished(tap_dance_state_t *state, void *user_data) {
  media_tap_state.state = cur_dance(state);
  switch (media_tap_state.state) {
  case TD_SINGLE_TAP:
    register_code(KC_MPLY);
    break;
  case TD_SINGLE_HOLD:
    register_code(KC_MSTP);
    break;
  case TD_DOUBLE_TAP:
    register_code(KC_MNXT);
    break;
  case TD_DOUBLE_HOLD:
    register_code(KC_MPRV);
    break;
  // Last case is for fast typing. Assuming your key is `f`:
  // For emedia_ample, when typing the word `buffer`, and you want to make sure
  // that you send `ff` and not `Esc`. In order to type `ff` when typing fast,
  // the nemedia_t character will have to be hit within the `TAPPING_TERM`,
  // which by default is 200ms.
  /* case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break; */
  default:
    break;
  }
}

void media_reset(tap_dance_state_t *state, void *user_data) {
  switch (media_tap_state.state) {
  case TD_SINGLE_TAP:
    unregister_code(KC_MPLY);
    break;
  case TD_SINGLE_HOLD:
    unregister_code(KC_MSTP);
    break;
  case TD_DOUBLE_TAP:
    unregister_code(KC_MNXT);
    break;
  case TD_DOUBLE_HOLD:
    unregister_code(KC_MPRV);
    break;
  /* case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break; */
  default:
    break;
  }
  media_tap_state.state = TD_NONE;
}

bool super_ctrl_ctrl_enabled = true;
int super_ctrl_layer = SUPER_CTRL_LAYER;

static td_tap_t super_ctrl_tap_state = {.is_press_action = true,
                                        .state = TD_NONE};

void super_ctrl_finished(tap_dance_state_t *state, void *user_data) {
  super_ctrl_tap_state.state = cur_dance(state);
  switch (super_ctrl_tap_state.state) {
  case TD_SINGLE_TAP: register_code(KC_ESC); break;
  case TD_SINGLE_HOLD:
    register_code(KC_LCTL);
    break;
  case TD_DOUBLE_HOLD:
    layer_on(super_ctrl_layer);
    break;
  default: break;
  }
}
void super_ctrl_reset(tap_dance_state_t *state, void *user_data) {
  switch (super_ctrl_tap_state.state) {
  case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
  case TD_SINGLE_HOLD:
    unregister_code(KC_LCTL);
  case TD_DOUBLE_HOLD:
    layer_off(super_ctrl_layer);
    break;
  default: break;
  }
  super_ctrl_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SUPER_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, super_ctrl_finished,
                                                   super_ctrl_reset),
    /* Powerful all-in-one */
    [TD_MEDIA] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, media_finished, media_reset),
    /* Shared Mapping */
    [TD_HOME_PLY] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_MPLY),
    /* TKL */
    [TD_INS_PRV] = ACTION_TAP_DANCE_DOUBLE(KC_INS, KC_MPRV),
    [TD_PGUP_NXT] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_MNXT),
    [TD_END_STP] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_MSTP),
    /* 96% */
    [TD_END_NXT] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_MNXT),
    /* [TD_DEL_PRV] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_MPRV), */
    [TD_F12_PRV] = ACTION_TAP_DANCE_DOUBLE(KC_F12, KC_MPRV),
    [TD_NUM_STP] = ACTION_TAP_DANCE_DOUBLE(KC_NUM, KC_MSTP),
    /* 75% */
    [TD_PGUP_PRV] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_MPRV),
    [TD_PGDN_NXT] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_MNXT),
    // Also uses TD_END_STP
};

// TD(TD_Q_TAB)

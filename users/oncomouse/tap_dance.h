#pragma once

#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void media_finished(tap_dance_state_t *state, void *user_data);
void media_reset(tap_dance_state_t *state, void *user_data);

void super_ctrl_finished(tap_dance_state_t *state, void *user_data);
void super_ctrl_reset(tap_dance_state_t *state, void *user_data);

enum {
    TD_MEDIA = 0,
    TD_HOME_PLY,
    TD_INS_PRV,
    TD_PGUP_NXT,
    TD_END_STP,
    TD_END_NXT,
    TD_DEL_PRV,
    TD_NUM_STP,
    TD_PGUP_PRV,
    TD_PGDN_NXT,
    TD_F12_PRV,
    TD_SUPER_CTRL,
};

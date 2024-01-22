enum {
    /* TD_Q_TAB = 0 */
    TD_MEDIA = 0,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    /* [TD_Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB) */
    [TD_MEDIA] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
};

// TD(TD_Q_TAB)

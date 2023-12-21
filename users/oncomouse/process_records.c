#include "oncomouse.h"

bool custom_lctl_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t custom_lctl_timer;
  switch(keycode) {
  /* Stop music and send lock screen shortcut */
  case QM_STLK:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_MSTP) SS_DELAY(50) SS_LWIN(SS_LCTL("q")));
    }
    break;
  /* Send specialctrl, which acts just like ctrl except when n or p is pressed*/
  case QMK_CUSTOM_LCTL:
    if (record->event.pressed) {
      custom_lctl_active = true;
      register_code(KC_LCTL);
      custom_lctl_timer = timer_read();
    } else {
      custom_lctl_active = false;
      unregister_code(KC_LCTL);
      if (timer_elapsed(custom_lctl_timer) < TAPPING_TERM) {
        leader_start();
      }
    }
    break;
  /* Send down when specialctrl + n is pressed, like emacs bindings everywhere */
  case QMK_CUSTOM_N:
    if (record->event.pressed) {
      if (custom_lctl_active) {
        unregister_code(KC_LCTL);
        SEND_STRING(SS_TAP(X_DOWN));
        register_code(KC_LCTL);
      } else {
        SEND_STRING("n");
      }
    }
    break;
  /* Send up when specialctrl + p is pressed, like emacs bindings everywhere */
  case QMK_CUSTOM_P:
    if (record->event.pressed) {
      if (custom_lctl_active) {
        unregister_code(KC_LCTL);
        SEND_STRING(SS_TAP(X_UP));
        register_code(KC_LCTL);
      } else {
        SEND_STRING("p");
      }
    }
    break;
  }
  return true;
}

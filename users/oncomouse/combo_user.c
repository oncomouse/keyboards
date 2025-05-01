#include "oncomouse.h"

enum combo_events {
  SUPER_DUPER,
  TOGGLE_SUPER_DUPER,
};

const uint16_t PROGMEM super_duper_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM toggle_super_duper_combo[] = {KC_LCTL, KC_LWIN, KC_S, KC_D, COMBO_END};

bool combos_on = true;

combo_t key_combos[] = {
  [SUPER_DUPER] = COMBO_ACTION(super_duper_combo),
  [TOGGLE_SUPER_DUPER] = COMBO_ACTION(toggle_super_duper_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SUPER_DUPER:
      if (pressed) {
        layer_on(SUPER_CTRL_LAYER);
      } else {
        layer_off(SUPER_CTRL_LAYER);
      }
      break;
    case TOGGLE_SUPER_DUPER:
      if (pressed) {
        tap_code16(combos_on ? QK_COMBO_OFF : QK_COMBO_ON);
        combos_on = !combos_on;
      }
      break;
  }
}

#include "oncomouse.h"

void leader_end_user(void) {
  if (leader_sequence_one_key(KC_U)) {
    SEND_STRING("../");
  } else if (leader_sequence_one_key(KC_L)) {
    SEND_STRING("ls ");
  }
}

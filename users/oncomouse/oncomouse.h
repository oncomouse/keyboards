#pragma once
#include QMK_KEYBOARD_H
#include "process_records.h"
#if defined(LEADER_ENABLE)
#    include "leader_user.h"
#endif
#if defined(COMBO_ENABLE)
#    include "combo_user.h"
#endif
#if defined(TAP_DANCE_ENABLE)
#    include "tap_dance.h"
#endif
// Use constant mouse speed:
#define MK_3_SPEED

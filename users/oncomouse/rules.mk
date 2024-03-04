ENCODER_MAP_ENABLE = yes
SEND_STRING_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = no
LEADER_ENABLE = no
TAP_DANCE_ENABLE = yes

SRC += process_records.c
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap_dance.c
endif
ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
	SRC += override_user.c
endif
ifeq ($(strip $(COMBO_ENABLE)), yes)
	INTROSPECTION_KEYMAP_C += combo_user.c
endif
ifeq ($(strip $(LEADER_ENABLE)), yes)
    SRC += leader_user.c
endif

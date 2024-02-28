ENCODER_MAP_ENABLE = yes
SEND_STRING_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = no
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes

SRC += tap_dance.c
SRC += process_records.c
ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
	SRC += override_user.c
endif
ifeq ($(strip $(COMBO_ENABLE)), yes)
	INTROSPECTION_KEYMAP_C += combo_user.c
endif
ifeq ($(strip $(LEADER_ENABLE)), yes)
    SRC += leader_user.c
endif

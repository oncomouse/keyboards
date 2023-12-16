#include "oncomouse.h"

const key_override_t emacs_down = {
  .trigger_mods = MOD_BIT(KC_LCTL),
  .layers = ~0,
  .suppressed_mods = MOD_BIT(KC_LCTL),
  .options = ko_options_default,
  .negative_mod_mask = (uint8_t) ~(MOD_BIT(KC_LCTL)),
  .custom_action = NULL,
  .context = NULL,
  .trigger = KC_N,
  .replacement = KC_DOWN,
  .enabled = &custom_lctl_active,
};

const key_override_t **key_overrides = (const key_override_t *[]) {
  &emacs_down,
};

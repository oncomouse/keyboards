#!/bin/bash
# Source: https://github.com/rafaelromao/keyboards/blob/main/init_qmk.sh

KEYBOARD_HOME="$(pwd)"
export QMK_HOME="$KEYBOARD_HOME/qmk_firmware"
USER_SPACE="$QMK_HOME/users"

if [[ ! -d "$QMK_HOME" ]]
then
    echo "Add git sub-modules..."
    git submodule add -f https://github.com/Keychron/qmk_firmware
fi
echo "Update git sub-modules..."
git submodule sync --recursive
git submodule update --init --recursive --progress

qmk config user.qmk_home="$QMK_HOME"

# Link in keymaps and such:
while read -r file; do
    OUTPUT_DIR="$(echo "$(dirname "$file")" | sed -e "s@$KEYBOARD_HOME@$QMK_HOME@")"
    mkdir -p "${OUTPUT_DIR}"
    ln -sf "${file}" "${OUTPUT_DIR}"
done <<< "$(find "$KEYBOARD_HOME/keyboards" -type f)"

# Prepare users:
mkdir -p $USER_SPACE
find "$KEYBOARD_HOME/users" -type d -links 2 -exec ln -sf {} "$USER_SPACE" \;

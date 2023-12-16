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

mkdir -p $USER_SPACE
qmk config user.qmk_home="$QMK_HOME"

while read -r dir; do
    OUTPUT_DIR="$(echo "$dir" | sed -e "s@$KEYBOARD_HOME/qmk@$QMK_HOME@")"
    mkdir -p "${OUTPUT_DIR}"
    ln -sf "${dir}"/* "${OUTPUT_DIR}"
done <<< "$(find "$KEYBOARD_HOME/qmk/keyboards" -type d -links 2)"

find "$KEYBOARD_HOME/qmk/users" -type d -links 2 -exec ln -sf {} "$USER_SPACE" \;

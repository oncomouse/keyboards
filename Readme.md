# Oncomouse's Keebs

Keyboard repo based on QMK.

## To configure

Run `bash init_qmk.sh` in this directory.

Then use `qmk compile -kb <whatever> -km oncomouse` to compile my custom firmware.

### To compile Bluetooth keyboards

1. `cd qmk_firmware`
2. `git checkout bluetooth_playground`
3. `cd ..`

Then proceed as normal.

## TODO

* [x] Support for Q3 Pro
* [ ] Figure out repeatability for layers

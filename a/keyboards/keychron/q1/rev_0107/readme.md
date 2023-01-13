# The ANSI variant of the Keychron Q1 (Knob Edition with knob installed)

- This QMK firmware for the newer version of the Keychron Q1, the [Keychron Q1 QMK Custom Mechanical Keyboard Knob Version](https://www.keychron.com/products/keychron-q1-qmk-custom-mechanical-keyboard-knob-version).
- The keyboard is based on STM32L432KB, but compiled with STM32L433-based firmware.
- This keyboard uses a HC595 shift register, so pins some unassigned in the `config.h` file. Appropriate custom matrix implementaion: `matrix.c`.
- The current implementation of this firmware uses 2Kb of transient EEPROM, so keymap changes made after plugging in the board will be lost when keyboard is unplugged/power is lost (i.e. the board resets to whatever keymap was set in the firmware).

- **Enables the EC11 rotary encoder.**
- By default, turn clockwise to increase volume and turn anti-clockwise to decrease volume.
- By default, top right key (encoder) is set to mute.

- `default` keymap has no VIA/VIAL support. Knob is set to volume control/mute by default and is not programmable.
- `via` keymap enables VIA support. Encoder rotation is programmable in VIA. You need to import the VIA json layout file to detect the board using VIA. The VIA json can be found [here](https://www.keychron.com/blogs/archived/how-to-reset-your-keychron-q1-to-factory-settings) under `Download Q1 Knob Version JSON file`.
- `vial` keymap enables **both** VIA and VIAL support. Encoder rotation is programmable in VIAL (but not in VIA). You still need to import the VIA json layout file if you use VIA, however in VIAL it will *automatically detect the keyboard layout*.
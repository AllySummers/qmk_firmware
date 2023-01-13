/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

/*
    Description: List of tap dances

    * KNOB_0 = Windows
    * KNOB_1 = Mac
*/
enum tap_dance_key_event {
    KNOB_0,
    KNOB_1
};


/*
    Description: Possible states for a given tap dance

    * SINGLE_HOLD   = 1: Activates while holding the key
    * SINGLE_TAP    = 2: Activates when pressing the key once
    * DOUBLE_TAP    = 3: Activates when pressing the key 2 times in quick succession
    * TRIPLE_TAP    = 4: Activates when pressing the key 3 times in quick succession
*/
enum tap_dance_state {
    SINGLE_HOLD = 1,
    SINGLE_TAP = 2,
    DOUBLE_TAP = 3,
    TRIPLE_TAP = 4,
};

/*
    Description: Holds state for tap dance KNOB_0 (Windows)
    See: tap_dance_key_event
    See: tap_dance_state
*/
static int knob_0_tap_state   = 0;

/*
    Description: Holds state for tap dance KNOB_1 (Mac)
    See: tap_dance_key_event
    See: tap_dance_state
*/
static int knob_1_tap_state   = 0;

/*
    Description: Layers declaration

    - MAC_BASE  - Base layer for use on Mac (uses this when dip switch is on left setting)
    - MAC_FN    - Modified keys for 2nd Mac layer (currently mostly empty)
    - WIN_BASE  - Base layer for use on Windows (uses this when dip switch is on right setting)
    - WIN_FN    - Modified keys for 2nd Windows layer (currently mostly empty)
*/
enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

/*
    Description: Custom keycodes added by Keychron, mostly for Mac but includes a few for Windows
*/
enum custom_keycodes {
    KC_MISSION_CONTROL = SAFE_RANGE,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER
};

/* Common keyboard code */
typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

/* Common keyboard code */
key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER

/* Mac specific keycodes */
static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

/*
    Description: Keymaps

    See: layers
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_PSCR,            TD(KNOB_1),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_INS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,             KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCMMD, KC_LOPTN,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
      ),

    [MAC_FN] = LAYOUT_ansi_82(
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            KC_TRNS,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_PGUP,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_HOME,  KC_PGDN,  KC_END
      ),

    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_PSCR,            TD(KNOB_0),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_INS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,             KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCMD,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
      ),

    [WIN_FN] = LAYOUT_ansi_82(
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            RGB_TOG,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            KC_TRNS,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_PGUP,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_HOME,  KC_PGDN,  KC_END
      ),
};

/**
 * @brief Determines what should happen when the rotary encoder is rotated depending on the layer and dirction the encoder was turned
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case MAC_BASE:
        case WIN_BASE:
            /*
                Counter-Clockwise:  Media Previous
                Clockwise:          Meida Next
            */
            clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
            return false;
            break;
        case MAC_FN:
        case WIN_FN:
            /*
                Counter-Clockwise:  Volume Down
                Clockwise:          Volume Up
            */
            clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            return false;
            break;
    }
    return true;
}

/**
 * @brief Determines the state from tap dance state and converts to custom action
 * @returns Value of `tap_dance_state`
 */
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->pressed) {
        return SINGLE_HOLD;
    }
    if (state->count == 1) {
        return SINGLE_TAP;
    }
    if (state->count == 2) {
        return DOUBLE_TAP;
    }
    if (state->count == 3) {
        return TRIPLE_TAP;
    }

    return -1;
}

/**
 * @brief Registers/unregisters layers and keys dependent on tap dance action for KNOB_0 (Windows)
 * @see For teardown code see knob_0_reset
 */
void knob_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    knob_0_tap_state = cur_dance(state);
    switch (knob_0_tap_state) {
        case SINGLE_TAP:
            /* Register play/pause media */
            register_code16(KC_MPLY);
            break;
        case DOUBLE_TAP:
            /* Unregister play/pause media, register mute */
            unregister_code16(KC_MPLY);
            register_code16(KC_MUTE);
            break;
        // case TRIPLE_TAP:
        //     /* Unimplemented */
        //     unregister_code16(KC_MUTE);
        //     register_code16(XXX);
        //     break;
        case SINGLE_HOLD:
            /* Disable base layer, enable FN layer */
            layer_off(WIN_BASE);
            layer_on(WIN_FN);
            break;
    }
}

/**
 * @brief Resets layers and keys to their default action for KNOB_0 (Windows)
 * @see For setup code see knob_0_finished
 */
void knob_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (knob_0_tap_state) {
        case SINGLE_TAP:
            /* Unregister play/pause media */
            unregister_code16(KC_MPLY);
            break;
        case DOUBLE_TAP:
            /* Unregister mute */
            unregister_code16(KC_MUTE);
            break;
        // case TRIPLE_TAP:
        //     /* Unimplemented */
        //     unregister_code16(XXX);
        //     break;
        case SINGLE_HOLD:
            /* Enable base layer, disable FN layer */
            layer_off(WIN_FN);
            layer_on(WIN_BASE);
            break;
    }
    knob_0_tap_state = 0;
}

/**
 * @brief Registers/unregisters layers and keys dependent on tap dance action for KNOB_1 (Mac)
 * @see For teardown code see knob_1_reset
 */
void knob_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    knob_1_tap_state = cur_dance(state);
    switch (knob_1_tap_state) {
        case SINGLE_TAP:
            /* Register play/pause media */
            register_code16(KC_MPLY);
            break;
        case DOUBLE_TAP:
            /* Unregister play/pause media, register mute */
            unregister_code16(KC_MPLY);
            register_code16(KC_MUTE);
            break;
        // case TRIPLE_TAP:
        //     /* Unimplemented */
        //     unregister_code16(KC_MUTE);
        //     register_code16(XXX);
        //     break;
        case SINGLE_HOLD:
            /* Disable base layer, enable FN layer */
            layer_off(MAC_BASE);
            layer_on(MAC_FN);
            break;
    }
}

/**
 * @brief Resets layers and keys to their default action for KNOB_1 (Mac)
 * @see For setup code see knob_1_finished
 */
void knob_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (knob_1_tap_state) {
        case SINGLE_TAP:
            /* Unregister play/pause media */
            unregister_code16(KC_MPLY);
            break;
        case DOUBLE_TAP:
            /* Unregister mute */
            unregister_code16(KC_MUTE);
            break;
        // case TRIPLE_TAP:
        //     /* Unimplemented */
        //     unregister_code16(XXX);
        //     break;
        case SINGLE_HOLD:
            /* Enable base layer, disable FN layer */
            layer_off(MAC_FN);
            layer_on(MAC_BASE);
            break;
    }
    knob_1_tap_state = 0;
}


/*
    Description: Associate tap dance with defined functionality
*/
qk_tap_dance_action_t tap_dance_actions[] = {
    // Knob 0: Hold - Shift, One - (, Two - {, Three - [
    [KNOB_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, knob_0_finished, knob_0_reset),
    // Knob 1: Hold - Shift, One - (, Two - {, Three - [
    [KNOB_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, knob_1_finished, knob_1_reset),
};


/*
    Description: Keychron code to handle custom keycodes
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;  // Skip all further processing of this key
        case KC_TASK:
        case KC_FLXP:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false;  // Skip all further processing of this key
        default:
            return true;   // Process all other keycodes normally
    }
}

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
#include "keychron_common.h"

/*
    Description: Layers declaration
*/
enum layers {
    BASE,
    FN_1,
    FN_2,
    FN_3
};

/*
    Description: List of tap dances

    * KNB_0 = Windows
*/
enum tap_dance_key_event {
    KNB_0,
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
    Description: Holds state for tap dance KNB_0 (Windows)
    See: tap_dance_key_event
    See: tap_dance_state
*/
static int knob_0_tap_state   = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_PSCR,            TD(KNB_0),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_INS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,             KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCMD,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(FN_1),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
      ),

    [FN_1] = LAYOUT_ansi_82(
        KC_TRNS,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,    KC_F24,   KC_TRNS,            RGB_TOG,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            KC_TRNS,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_PGUP,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                MO(FN_2), KC_TRNS,   KC_TRNS,  KC_HOME,  KC_PGDN,  KC_END
      ),

    [FN_2] = LAYOUT_ansi_82(
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            KC_TRNS,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,   MO(FN_3),  KC_TRNS,  KC_TRNS,  KC_TRNS
      ),

    [FN_3] = LAYOUT_ansi_82(
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            QK_BOOT,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            DB_TOGG,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            EE_CLR ,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
      ),
};

/**
 * @brief Determines what should happen when the rotary encoder is rotated depending on the layer and dirction the encoder was turned
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case BASE:
            /*
                Counter-Clockwise:  Media Previous
                Clockwise:          Meida Next
            */
            clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
            return false;
            break;
        case FN_1:
            /*
                Counter-Clockwise:  Volume Down
                Clockwise:          Volume Up
            */
            clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            return false;
            break;
        default:
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
 * @brief Registers/unregisters layers and keys dependent on tap dance action for KNB_0 (Windows)
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
        // case SINGLE_HOLD:
        //     /* Disable base layer, enable FN layer */
        //     // layer_off(WIN_BASE);
        //     // layer_on(WIN_FN);
        default:
            break;
    }
}

/**
 * @brief Resets layers and keys to their default action for KNB_0 (Windows)
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
        // case SINGLE_HOLD:
        //     /* Enable base layer, disable FN layer */
        //     layer_off(WIN_FN);
        //     layer_on(WIN_BASE);
        //     break;
        default:
            break;
    }
    knob_0_tap_state = 0;
}

/*
    Description: Associate tap dance with defined functionality
*/
qk_tap_dance_action_t tap_dance_actions[] = {
    // Knob 0: Hold - Shift, One - (, Two - {, Three - [
    [KNB_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, knob_0_finished, knob_0_reset),
};

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
	  uint8_t modifiers = get_mods();

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(45, RGB_RED);
    }

    if (modifiers & MOD_BIT(KC_LEFT_SHIFT)) {
        rgb_matrix_set_color(59, RGB_RED);
    }

    if (modifiers & MOD_BIT(KC_LEFT_CTRL)) {
        rgb_matrix_set_color(72, RGB_RED);
    }

    if (modifiers & MOD_BIT(KC_LEFT_GUI)) {
        rgb_matrix_set_color(73, RGB_RED);
    }

    if (modifiers & MOD_BIT(KC_LEFT_ALT)) {
        rgb_matrix_set_color(74, RGB_RED);
    }

    if (modifiers & MOD_BIT(KC_RIGHT_ALT)) {
        rgb_matrix_set_color(76, RGB_RED);
    }

    if (modifiers & MOD_BIT(KC_RIGHT_CTRL)) {
        rgb_matrix_set_color(78, RGB_RED);
    }

    if (modifiers & MOD_BIT(KC_RIGHT_SHIFT)) {
        rgb_matrix_set_color(80, RGB_RED);
    }

    switch (layer) {
        case BASE:
            rgb_matrix_set_color(1, RGB_RED);
            break;
        case FN_1:
            rgb_matrix_set_color(2, RGB_RED);
            break;
        case FN_2:
            rgb_matrix_set_color(3, RGB_RED);
            break;
        case FN_3:
            rgb_matrix_set_color(4, RGB_RED);
            break;
        default:
            break;
    }

    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    layer_invert(FN_3);

    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [FN_1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN_2] = { ENCODER_CCW_CW( KC_NO ,  KC_NO ) },
    [FN_3] = { ENCODER_CCW_CW( KC_NO ,  KC_NO ) },
};
#endif

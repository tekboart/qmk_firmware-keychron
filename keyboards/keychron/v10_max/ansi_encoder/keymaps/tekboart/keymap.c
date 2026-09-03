/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    // TODO: BASE layers must always be the lowest numbered layers. As any layer REF in them must be to a higher numbered layer. However, to utilize Keychron's MAC/WIN Toggle, I put a layer in betwwen so that MAC toggle selects Split Base layer and WIN toggle selects Standard Base layer.
    _BASE_SPL,  // Split Layer (Base)
    _TYPING,    // Typing Layer (Base): Disable all HRMs.
    _BASE_STD,  // Standard QWERTY Layer (Base): Disable all HRMs & Split Layout.
    // NOTE: _FUNCTION must be placed after both BASE layers (i.e., Split and Standard), as In a layer's keymap, one must only reference higher-numbered layers.
    _FUNCTION,    // Function Layer (Split Layout). Hint: MoErgo calls this the "Magic" layer.
    _SYMBOL,   // Symbols Layer (Split Layout)
    _NUMBER,   // Number/Numpad Layer (Split Layout)
    _CURSOR,   // Cursor Layer (Split Layout)
    _NAVIGATION,   // Navigation + Number Layer (Split Layout). This is redundant with the _CURSOR layer and Standard Layer.
    _GAMING,   // Gaming Layer
};

// ------- Define Aliases: Thumb Keys  -------
// Split Layout
// (Base) Split Layer
#define TT_BASE TT(_BASE_SPL)
#define TG_BASE TG(_BASE_SPL)
#define DF_BASE DF(_BASE_SPL)
// Typing Layer
#define TT_TYP TT(_TYPING)
#define TG_TYP TG(_TYPING)
// Standard Layout
#define LT_STD  LT(_BASE_STD, KC_4)
#define TT_STD  TT(_BASE_STD)
#define TG_STD  TG(_BASE_STD)
#define DF_STD  DF(_BASE_STD)
// Function Layer
#define LT_FN   LT(_FUNCTION, KC_3)
#define MO_FN   MO(_FUNCTION)
#define TT_FN   TT(_FUNCTION)
#define TG_FN   TG(_FUNCTION)
// Number Layer
#define LT_NUM  LT(_NUMBER, KC_SPC)
#define TT_NUM  TT(_NUMBER)
#define TG_NUM  TG(_NUMBER)
// Navigation Layer
#define LT_NAV  LT(_NAVIGATION, KC_1)
#define TT_NAV  TT(_NAVIGATION)
#define TG_NAV  TG(_NAVIGATION)
// Symbol Layer
#define LT_SYM  LT(_SYMBOL, KC_ENT)
// Cursor Layer
#define LT_CSR   LT(_CURSOR, KC_3)
#define MO_CSR   MO(_CURSOR)
#define TT_CSR   TT(_CURSOR)
#define TG_CSR   TG(_CURSOR)


// ------- Define Aliases: Mod-Tap Keys  -------
#define MT_LSFT MT(MOD_LSFT,KC_LBRC)
#define MT_RSFT MT(MOD_RSFT,KC_RBRC)
#define MT_RALT MT(MOD_RALT,KC_TAB)

// ------- Define Aliases: Home Row Mods (HRMs) -------
#define HRW_A    MT(MOD_LGUI, KC_A)
#define HRW_S    MT(MOD_LALT, KC_S)
#define HRW_D    MT(MOD_LCTL, KC_D)
#define HRW_F    MT(MOD_LSFT, KC_F)
#define HRW_J    MT(MOD_RSFT, KC_J)
#define HRW_K    MT(MOD_RCTL, KC_K)
#define HRW_L    MT(MOD_RALT, KC_L)
#define HRW_SCLN MT(MOD_RGUI, KC_SCLN)

// ------- Define Aliases: Readable -------
#define MAC_WIN  CG_TOGG     // Toggle CTL & GUI for MacOS/Windows Mode
#define UNDO     C(KC_Z)     // Undo
#define REDO     S(C(KC_Z))  // Redo
#define PERMDEL  S(KC_DEL)   // Permanent Delete (Shift + Delete)
#define FIND     C(KC_F)     // Find
#define CUT      C(KC_X)     // Cut
#define COPY     C(KC_C)     // Copy
#define PASTE    C(KC_V)     // Paste

// ------- Define Aliases: App -------
#define AP_TERM  C(A(KC_T))  // Open Terminal
#define AP_FFOX  S(C(KC_1))  // Open Firefox Browser
#define AP_CHRM  S(C(KC_2))  // Open Google Chrome Browser
#define AP_FEXP  G(KC_E)     // Open File Explorer

// ------- Define Aliases: Selection -------
#define SEL_ALL  C(KC_A)        // Select All
#define SEL_LLN  S(KC_HOME)     // Select Line Left
#define SEL_RLN  S(KC_END)      // Select Line Right
#define SEL_LWR  S(C(KC_LEFT))  // Select Word Left
#define SEL_RWR  S(C(KC_RGHT))  // Select Word Right
// Based on Pascal Getreuer's "Select Word" QMK macro
#define SEL_LNE   KC_1  // Select Line
#define SEL_WRD   KC_2  // Select Line

// ------- Define Aliases: Symbols -------
#define SM_EXCL   S(KC_1)     // !
#define SM_ADS    S(KC_2)     // @
#define SM_HASH   S(KC_3)     // #
#define SM_DLR    S(KC_4)     // $
#define SM_PERC   S(KC_5)     // %
#define SM_CRET   S(KC_6)     // ^
#define SM_AMPS   S(KC_7)     // &
#define SM_ASTR   S(KC_8)     // *
#define SM_LPRN   S(KC_9)     // (
#define SM_RPRN   S(KC_0)     // )
#define SM_LBRC   KC_LBRC     // [
#define SM_RBRC   KC_RBRC     // ]
#define SM_LCBR   S(KC_LBRC)  // {
#define SM_RCBR   S(KC_RBRC)  // }
#define SM_TICK   KC_GRV      // `
#define SM_TILD   S(KC_GRV)   // ~
#define SM_COMM   KC_COMM     // ,
#define SM_LT     S(KC_COMM)  // <
#define SM_DOT    KC_DOT      // .
#define SM_GT     S(KC_DOT)   // >
#define SM_SLSH   KC_SLSH     // /
#define SM_QUES   S(KC_SLSH)  // ?
#define SM_BSLS   KC_BSLS     // \ Backslash
#define SM_PIPE   S(KC_BSLS)  // |
#define SM_COLN   S(KC_SCLN)  // :
#define SM_SCLN   KC_SCLN     // ;
#define SM_DQT    S(KC_QUOT)  // "
#define SM_QUOT   KC_QUOT     // '
#define SM_EQL    KC_EQL      // =
#define SM_PLUS   S(KC_EQL)   // +
#define SM_MINS   KC_MINS     // -
#define SM_UNDS   S(KC_MINS)  // _

// ------- Define Macros  -------
enum custom_keycodes {
    MC_TICK = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MC_TICK:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("```");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};

// clang-format off

// Clear keymap template:
    /** [<Layer_Name>] = LAYOUT_ansi_89( */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,  _______,            _______,  _______,  _______,            _______,            _______,                                          _______,  _______,  _______ */
    /** ), */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_SPL] = LAYOUT_ansi_89(
        KC_MUTE,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            KC_PSCR,  KC_CALC,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            KC_HOME,
        XXXXXXX,  KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,  XXXXXXX,  XXXXXXX,  KC_DEL,
        XXXXXXX,  KC_ESC,             HRW_A,    HRW_S,    HRW_D,    HRW_F,    KC_G,               KC_H,     HRW_J,    HRW_K,    HRW_L,    HRW_SCLN, KC_QUOT,  XXXXXXX,            KC_END,
        XXXXXXX,  KC_BSPC,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_DEL,             KC_UP,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            TT_CSR,   LT_NUM,   TT_CSR,             LT_SYM,             TT_FN,                                            KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_TYPING] = LAYOUT_ansi_89(
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,            KC_A,     KC_S,     KC_D,     KC_F,     _______,            _______,  KC_J,     KC_K,     KC_L,     KC_SCLN,  _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,            KC_LCTL,  KC_SPC,   _______,            KC_ENT,             _______,                                          _______,  _______,  _______
    ),

    [_FUNCTION] = LAYOUT_ansi_89(
        UG_TOGG,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  TG_STD,             BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    AP_TERM,            AP_FFOX,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F13,   XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_CAPS,            TG_NAV,   _______,  _______,  AP_FFOX,  AP_FEXP,            AP_CHRM,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   KC_F14,   XXXXXXX,            KC_END,
        XXXXXXX,  TG_TYP,             MAC_WIN,  _______,  AP_CHRM,  _______,  _______,  BAT_LVL,  AP_FEXP,  KC_F1,    KC_F2,    KC_F3,    KC_F12,   KC_F15,             KC_PGUP,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______   TG_NUM,   TG_CSR,             _______,            _______,                                          KC_HOME,  KC_PGDN,  KC_END
    ),

    [_SYMBOL] = LAYOUT_ansi_89(
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  SM_EXCL,            SM_LBRC,  SM_LCBR,  SM_RCBR,  KC_RBRC,  SM_AMPS,            SM_DOT,   KC_DEL,   S(KC_TAB),KC_INS,   KC_ESC,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  SM_HASH,            SM_CRET,  SM_EQL,   SM_UNDS,  SM_DLR,   SM_ASTR,            SM_COMM,  KC_BSPC,  KC_TAB,   KC_SPC,   KC_ENT,   MC_TICK,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  SM_TILD,            SM_LT,    SM_PLUS,  SM_MINS,  SM_GT,    SM_PIPE,  XXXXXXX,  SM_SCLN,  SM_DQT,   SM_QUOT,  SM_TICK,  SM_BSLS,  KC_RSFT,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            SM_PERC,  SM_ADS,   _______,            _______,            _______,                                          XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_NUMBER] = LAYOUT_ansi_89(
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  _______,            KC_ENT,   KC_SPC,   KC_TAB,   KC_BSPC,  KC_P0,              XXXXXXX,  KC_P7,    KC_P8,    KC_P9,    SM_COLN,  SM_PERC,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  _______,            XXXXXXX,  XXXXXXX,  SM_LPRN,  SM_RPRN,  XXXXXXX,            KC_BSPC,  KC_P4,    KC_P5,    KC_P6,    SM_MINS,  SM_PLUS,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  _______,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DOT,   KC_P1,    KC_P2,    KC_P3,    SM_SLSH,  SM_ASTR,            KC_UP,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  _______,  _______,            KC_P0,              _______,                                          KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_CURSOR] = LAYOUT_ansi_89(
        _______,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  UNDO,               C(KC_Q),  C(KC_W),  AP_FEXP,  KC_F2,    CUT,                _______,  _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  PERMDEL,            KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  COPY,               KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  REDO,               SEL_ALL,  SEL_LNE,  SEL_WRD,  FIND,     PASTE,    XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  _______,  _______,            _______,            _______,                                          XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_NAVIGATION] = LAYOUT_ansi_89(
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_UP,    _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,  _______,  XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  KC_SPC,   _______,            KC_ENT,             _______,                                          XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_GAMING] = LAYOUT_ansi_89(
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  KC_TAB,             _______,  KC_W,     _______,  _______,  _______,            _______,  _______,  KC_UP,    _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_LSFT,            KC_A,     KC_S,     KC_D,     _______,  _______,            _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  KC_LCTL,            _______,  _______,  _______,  _______,  _______,  XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  KC_SPC,   _______,            KC_ENT,             _______,                                          XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    [_BASE_STD] = LAYOUT_ansi_89(
        KC_MUTE,  KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,  KC_CALC,
        MC_1,     KC_GRV,             KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
        MC_2,     KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,
        MC_3,     KC_CAPS,            KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_END,
        MC_4,     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        MC_5,     KC_LGUI,  KC_LALT,            KC_LCTL,  KC_SPC,   KC_RALT,            KC_SPC,             _______,                                          KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

};

// Define the encoder rotation map for each layer
// The encoder map defines the behavior of the rotary encoder (aka Knob) for each layer
// Examples: KC_VOLD: Volume Down, KC_VOLU: Volume Up, UG_VALD: Underglow Brightness Down, UG_VALU: Underglow Brightness Up
// TODO: Add diff for layers, e.g., SPL_LAYER_2 + turn_right --> Screen Brightness Up, turn_left --> Screen Brightness Down
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    /** [TGL_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, */
    /** [TGL_FN]   = {ENCODER_CCW_CW(UG_VALD, UG_VALU)}, */
    [_BASE_SPL]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_TYPING]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_BASE_STD]    = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_FUNCTION]    = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [_SYMBOL]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_NUMBER]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_CURSOR]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_NAVIGATION]  = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_GAMING]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};
#endif // ENCODER_MAP_ENABLE

// ------- RGB Light Configuration -------
// Define Aliases: Colors -------
// TODO
// Change RGB Color per Layer
bool rgb_matrix_indicators_user(void) {
    /** Turn off all RGB LEDs first. */
    hsv_t hsv_off = (hsv_t){0, 0, 0};
    rgb_t rgb_off = hsv_to_rgb(hsv_off);
    rgb_matrix_set_color_all(rgb_off.r, rgb_off.g, rgb_off.b);

    /** Get the highest active layer. */
    uint8_t active_layer = get_highest_layer(layer_state | default_layer_state);

    /** Current RGB brightness. */
    uint8_t val = rgb_matrix_get_val();

    switch (active_layer) {

        // ---------------------------------------------------------------
        // BASE STANDARD
        // ---------------------------------------------------------------
        case _BASE_STD: {
            hsv_t hsv = (hsv_t){0, 0, val};
            rgb_t rgb = hsv_to_rgb(hsv);

            rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
            break;
        }

        // ---------------------------------------------------------------
        // BASE SPLIT / TYPING
        // ---------------------------------------------------------------
        case _BASE_SPL:
        case _TYPING: {
            /** Base Split Layer color. */
            hsv_t hsv_base = (hsv_t){0, 255, val};
            rgb_t rgb_base = hsv_to_rgb(hsv_base);

            /** HRM color. */
            hsv_t hsv_hrm = (hsv_t){170, 255, val};
            rgb_t rgb_hrm = hsv_to_rgb(hsv_hrm);

            /** V10 Max LED indices for Base Split Layer:
             *
             * TAB → 32, Q → 33, W → 34, E → 35, R → 36, T → 37
             * Y → 38, U → 39, I → 40, O → 41, P → 42, [ → 43
             *
             * CAPS → 48, A → 49, S → 50, D → 51, F → 52, G → 53
             * H → 54, J → 55, K → 56, L → 57, ; → 58, ' → 59
             *
             * LSFT → 63, Z → 64, X → 65, C → 66, V → 67, B → 68
             * N → 70, M → 71, , → 72, . → 73, / → 74, RShift → 75
             *
             * LGUI → 80, LSpace → 81, FN → 82
             * RSpace → 83, RGUI → 84
             */
            static const uint8_t base_spl_rgb_idx[] = {
                32, 33, 34, 35, 36, 37,
                38, 39, 40, 41, 42, 43,
                48, 49, 50, 51, 52, 53,
                54, 55, 56, 57, 58, 59,
                63, 64, 65, 66, 67, 68,
                70, 71, 72, 73, 74, 75,
                80, 81, 82,
                83, 84
            };

            for (uint8_t i = 0; i < ARRAY_SIZE(base_spl_rgb_idx); i++) {
                rgb_matrix_set_color(
                    base_spl_rgb_idx[i],
                    rgb_base.r,
                    rgb_base.g,
                    rgb_base.b
                );
            }

            /** HRMs only on _BASE_SPL. */
            if (active_layer == _BASE_SPL) {
                static const uint8_t hrm_rgb_idx[] = {
                    49, 50, 51, 52,
                    55, 56, 57, 58
                };

                for (uint8_t i = 0; i < ARRAY_SIZE(hrm_rgb_idx); i++) {
                    rgb_matrix_set_color(
                        hrm_rgb_idx[i],
                        rgb_hrm.r,
                        rgb_hrm.g,
                        rgb_hrm.b
                    );
                }
            }

            break;
        }

        // ---------------------------------------------------------------
        // NUMBER
        // ---------------------------------------------------------------
        case _NUMBER: {
            hsv_t hsv = (hsv_t){85, 255, val};
            rgb_t rgb = hsv_to_rgb(hsv);

            /** 3x3 keypad + 0:
             *
             * U/7 → 39, I/8 → 40, O/9 → 41
             * J/4 → 55, K/5 → 56, L/6 → 57
             * M/1 → 71, ,/2 → 72, ./3 → 73
             * RSPC/0 → 83
             */
            static const uint8_t rgb_idx[] = {
                39, 40, 41,
                55, 56, 57,
                71, 72, 73,
                83
            };

            for (uint8_t i = 0; i < ARRAY_SIZE(rgb_idx); i++) {
                rgb_matrix_set_color(
                    rgb_idx[i],
                    rgb.r,
                    rgb.g,
                    rgb.b
                );
            }

            break;
        }

        // ---------------------------------------------------------------
        // FUNCTION
        // ---------------------------------------------------------------
        case _FUNCTION: {
            hsv_t hsv = (hsv_t){20, 255, val};
            rgb_t rgb = hsv_to_rgb(hsv);

            /** F1-F12:
             *
             * F7 → 39, F8 → 40, F9 → 41, F10 → 42
             * F4 → 55, F5 → 56, F6 → 57, F11 → 58
             * F1 → 71, F2 → 72, F3 → 73, F12 → 74
             */
            static const uint8_t rgb_idx[] = {
                39, 40, 41, 42,
                55, 56, 57, 58,
                71, 72, 73, 74
            };

            for (uint8_t i = 0; i < ARRAY_SIZE(rgb_idx); i++) {
                rgb_matrix_set_color(
                    rgb_idx[i],
                    rgb.r,
                    rgb.g,
                    rgb.b
                );
            }

            break;
        }

        // ---------------------------------------------------------------
        // CURSOR
        // ---------------------------------------------------------------
        case _CURSOR: {
            hsv_t hsv = (hsv_t){190, 255, val};
            rgb_t rgb = hsv_to_rgb(hsv);

            /** Cursor/editing keys. */
            static const uint8_t rgb_idx[] = {
                37, 53, 68,
                38, 54, 70,
                64, 65
            };

            for (uint8_t i = 0; i < ARRAY_SIZE(rgb_idx); i++) {
                rgb_matrix_set_color(
                    rgb_idx[i],
                    rgb.r,
                    rgb.g,
                    rgb.b
                );
            }

            break;
        }

        // ---------------------------------------------------------------
        // NAVIGATION
        // ---------------------------------------------------------------
        case _NAVIGATION: {
            hsv_t hsv = (hsv_t){200, 255, val};
            rgb_t rgb = hsv_to_rgb(hsv);

            /** Left, Down, Up, Right. */
            static const uint8_t rgb_idx[] = {
                54, 55, 56, 57
            };

            for (uint8_t i = 0; i < ARRAY_SIZE(rgb_idx); i++) {
                rgb_matrix_set_color(
                    rgb_idx[i],
                    rgb.r,
                    rgb.g,
                    rgb.b
                );
            }

            break;
        }

        // ---------------------------------------------------------------
        // SYMBOL
        // ---------------------------------------------------------------
        case _SYMBOL: {
            hsv_t hsv = (hsv_t){200, 255, val};
            rgb_t rgb = hsv_to_rgb(hsv);

            /** Shifted/symbol keys. */
            static const uint8_t rgb_idx[] = {
                32, 33, 34, 35, 36, 37,
                48, 49, 50, 51, 52, 53,
                63, 64, 65, 66, 67, 68,
                80, 81, 82
            };

            for (uint8_t i = 0; i < ARRAY_SIZE(rgb_idx); i++) {
                rgb_matrix_set_color(
                    rgb_idx[i],
                    rgb.r,
                    rgb.g,
                    rgb.b
                );
            }

            break;
        }

        // ---------------------------------------------------------------
        // DEFAULT
        // ---------------------------------------------------------------
        default:
            break;
    }

    // ---------------------------------------------------------------
    // CTRL/GUI SWAP INDICATOR
    // ---------------------------------------------------------------
    /** Make M blue whenever CG_TOGG is active. */
    if (keymap_config.swap_lctl_lgui) {
        hsv_t hsv = (hsv_t){170, 255, val};
        rgb_t rgb = hsv_to_rgb(hsv);

        /** KC_M → matrix [4][9] → LED index 71 */
        rgb_matrix_set_color(71, rgb.r, rgb.g, rgb.b);
    }

    return false;
}


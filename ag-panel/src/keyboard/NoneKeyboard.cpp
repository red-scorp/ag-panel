/** @file NoneKeyboard.cpp
    @brief AG-Panel Project none keyboard implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "NoneKeyboard.h"

/** @brief Initialization of none keyboard

    @returns true
 */
bool NoneKeyboard::Init() {
    return true;
}

/** @brief Deinitialization of none keyboard class
 */
void NoneKeyboard::Exit() {
}

/** @brief Get a key of none keyboard

    @returns #KeyNone always
 */
uint8_t NoneKeyboard::GetKey() {
    return KeyNone;
}

/** @brief Get number of keys supported by none keyboard

    @returns Number of supported keys
 */
uint8_t NoneKeyboard::GetKeyCount() {
    return 0;
}

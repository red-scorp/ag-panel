/** @file I2CRGBKeypad.cpp
    @brief AG-Panel Project I2C RGB keypad keyboard implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "../../config.h"
#include "I2CRGBKeypad.h"
#include "../lcd/I2CRGBTextLCD.h"

#if !defined(ARDUINO_ARCH_GD32V) && !defined(ARDUINO_ARCH_KENDRYTE)

#include <Adafruit_RGBLCDShield.h>

/** @brief Initialization of I2C RGB keypad

    @returns true
 */
bool I2CRGBKeypad::Init() {
    /* The RGB Keypad is already initialized in I2CRGBTextLCD.cpp but we should retrieve a pointer */
    I2CRGBTextLCD *p_I2CRGBTextLCD = reinterpret_cast<I2CRGBTextLCD*>(m_LCD);
    m_Lowlevel = p_I2CRGBTextLCD->GetLowLevel();
  return true;
}

/** @brief Deinitialization of I2C RGB keypad class
 */
void I2CRGBKeypad::Exit() {
}

/** @brief Get a key of I2C RGB keypad

    Reads key state from I2C controller to find out what key has been pressed.
    @returns #KeyNone if no new actions detected, else a key code
 */
uint8_t I2CRGBKeypad::GetKey() {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    uint8_t buttons = p_I2CRGBLCD->readButtons();

    if(buttons & BUTTON_UP)
        return KeyDefaultUp;
    if(buttons & BUTTON_DOWN)
        return KeyDefaultDown;
    if(buttons & BUTTON_LEFT)
        return KeyDefaultLeft;
    if(buttons & BUTTON_RIGHT)
        return KeyDefaultRight;
    if(buttons & BUTTON_SELECT)
        return KeyDefaultSelect;

    return KeyNone;
}

/** @brief Get number of keys supported by I2C RGB keypad

    @returns Number of supported keys
 */
uint8_t I2CRGBKeypad::GetKeyCount() {
    return 5;
}

#else
#warning 'I2CRGBKeypad' is not implemented for GD32V and KENDRYTE platforms because it lacks of standard header 'Wire.h'!
#endif /* !ARDUINO_ARCH_GD32V */

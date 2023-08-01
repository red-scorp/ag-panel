/** @file AnalogKeypad.cpp
    @brief AG-Panel Project analog keypad keyboard implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "../../config.h"
#include "AnalogKeypad.h"

/** @brief Initialization of analog keypad

    @returns true
 */
bool AnalogKeypad::Init() {
    /* No initialization needed for analog pins */
    return true;
}

/** @brief Deinitialization of analog keypad class
 */
void AnalogKeypad::Exit() {
}

/** @brief Get a key of analog keypad

    Reads analog pin and deduces what key has been pressed.
    @returns #KeyNone if no new actions detected, else a key code
 */
uint8_t AnalogKeypad::GetKey() {
    uint16_t data = analogRead(m_DataPin);

    if(data >= m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexUp].min &&
        data < m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexUp].max)
        return KeyDefaultUp;
    if(data >= m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexDown].min &&
        data < m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexDown].max)
        return KeyDefaultDown;
    if(data >= m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexLeft].min &&
        data < m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexLeft].max)
        return KeyDefaultLeft;
    if(data >= m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexRight].min &&
        data < m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexRight].max)
        return KeyDefaultRight;
    if(data >= m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexSelect].min &&
        data < m_DataRangeArray[AbstractKeyboardAnalogDataRangeIndexSelect].max)
        return KeyDefaultSelect;
    return KeyNone;
}

/** @brief Get number of keys supported by analog keypad

    @returns Number of supported keys
 */
uint8_t AnalogKeypad::GetKeyCount() {
    return 5;
}

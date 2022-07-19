/*! \file DigitalMatrix.cpp
    \brief AG-Panel Project digital keypad keyboard implementation
    \copyright (C) 2019-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "../../config.h"
#include "DigitalMatrix.h"

/*! \brief Initialization of digital matrix

    Configures column and row pins of the matrix.
    \returns true
 */
bool DigitalMatrix::Init() {

    for(uint8_t c = 0; c < m_Columns; c++)
        pinMode(m_CPinsArray[c], OUTPUT);
    for(uint8_t r = 0; r < m_Rows; r++)
        pinMode(m_RPinsArray[r], INPUT_PULLUP);

    return true;
}

/*! \brief Deinitialization of digital matrix class
 */
void DigitalMatrix::Exit() {
}

/*! \brief Get a key of digital matrix

    Activates sequentially column pins and reads row pins to find out what key has been pressed.
    \returns #KeyNone if no new actions detected, else a key code
 */
uint8_t DigitalMatrix::GetKey() {
    for(uint8_t c = 0; c < m_Columns; c++) {
        delayMicroseconds(5);
        for(uint8_t i = 0; i < m_Columns; i++) {
            digitalWrite(m_CPinsArray[i], i == c? LOW: HIGH);
        }
        delayMicroseconds(5);
        for(uint8_t r = 0; r < m_Rows; r++) {
            uint16_t v = analogRead(m_RPinsArray[r]);
            if(v < 100) {
                for(uint8_t i = 0; i < m_Columns; i++) {
                    digitalWrite(m_CPinsArray[i], HIGH);
                }
                return r * m_Columns + c + 1;
            }
        }
    }
    for(uint8_t i = 0; i < m_Columns; i++) {
        digitalWrite(m_CPinsArray[i], HIGH);
    }
    return KeyNone;
}

/*! \brief Get number of keys supported by digital matrix

    \returns Number of supported keys
 */
uint8_t DigitalMatrix::GetKeyCount() {
    return m_Columns * m_Rows;
}

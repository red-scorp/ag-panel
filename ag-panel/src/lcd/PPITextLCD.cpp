/*! \file PPITextLCD.cpp
    \brief AG-Panel Project PPI (parallel) 4 and 8-bit text (hd44780) LCD implementation
    \copyright (C) 2019-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "PPITextLCD.h"
#include <LiquidCrystal.h>

//static LiquidCrystal *sp_PPILCD;    /*!< Pointer to a LiquidCrystal class instance */

/*! \brief Initialization of parallel text LCD display

    Configures parallel text LCD display to work in 8- or 4-bit mode according to specified pins and geometry.
    \note https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
    \returns true
 */
bool PPITextLCD::Init() {
    if(m_D0Pin != InvalidPin && m_D1Pin != InvalidPin && m_D2Pin != InvalidPin && m_D3Pin != InvalidPin)
        m_Lowlevel = new LiquidCrystal(m_RSPin, m_RWPin, m_EnablePin, m_D0Pin, m_D1Pin, m_D2Pin, m_D3Pin, m_D4Pin, m_D5Pin, m_D6Pin, m_D7Pin);
    else
        m_Lowlevel = new LiquidCrystal(m_RSPin, m_RWPin, m_EnablePin, m_D4Pin, m_D5Pin, m_D6Pin, m_D7Pin);
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    p_PPILCD->begin(m_Columns, m_Rows);
    return true;
}

/*! \brief Deinitialization of parallel text LCD display class
 */
void PPITextLCD::Exit() {
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    if(p_PPILCD != nullptr)
        delete p_PPILCD;
    m_Lowlevel = nullptr;
}

/*! \brief Clear LCD display

    This function calls corresponding function of LiquidCrystal class instance.
 */
void PPITextLCD::Clear() {
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    p_PPILCD->clear();
}

/*! \brief Set Cursor on LCD display

    This function calls corresponding function of LiquidCrystal class instance.
 */
void PPITextLCD::SetCursor(
    uint8_t column,       /*!< Column to put the cursor to */
    uint8_t row           /*!< Row to put the cursor to */
) {
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    p_PPILCD->setCursor(column, row);
}

/*! \brief Print a text on LCD display

    This function calls corresponding function of LiquidCrystal class instance.
 */
void PPITextLCD::Print(
    const char *str       /*!< String to print */
) {
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    p_PPILCD->print(str);
}

/*! \brief Print a character on LCD display

    This function calls corresponding function of LiquidCrystal class instance.
 */
void PPITextLCD::Print(
    char character        /*!< Character to print */
) {
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    p_PPILCD->print(character);
}

/*! \brief Write a byte (RS = 1) to LCD display

    This function calls corresponding function of LiquidCrystal class instance.
 */
void PPITextLCD::Write(
    uint8_t byte          /*!< Byte to write to LCD display */
) {
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    p_PPILCD->write(byte);
}

/*! \brief Send a command byte (RS = 0) to LCD display

    This function calls corresponding function of LiquidCrystal class instance.
 */
void PPITextLCD::Command(
    uint8_t byte          /*!< Command to send to LCD display */
) {
    LiquidCrystal *p_PPILCD = reinterpret_cast<LiquidCrystal*>(m_Lowlevel);
    p_PPILCD->command(byte);
}

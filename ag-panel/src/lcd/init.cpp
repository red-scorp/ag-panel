/*! \file init.cpp
    \brief AG-Panel Project LCD initialization
    \copyright (C) 2020-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#include "../private.h"
#include "../../config.h"

#include "all.h"

/*! \brief Initialize LCD

    This function chooses one of LCD classes to use based on configuration defined in config.h
    \returns Pointer to LCD class
 */
AbstractLCD *initLCD(
    AbstractBacklight *Backlight,   /*!< Pointer to configured backlight class */
    AbstractFont *Font              /*!< Pointer to configured font class */
) {
    AbstractLCD *p_LCD = nullptr;

    #if defined(LCD_TEXT_4BIT) || defined(LCD_TEXT_8BIT)
        #if defined(LCD_TEXT_4BIT)
            p_LCD = new PPITextLCD(Backlight, LCD_COLS, LCD_ROWS,
                LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
                LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
        #elif defined(LCD_TEXT_8BIT)
            p_LCD = new PPITextLCD(Backlight, LCD_COLS, LCD_ROWS,
                LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
                LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3,
                LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
        #endif
    #elif defined(LCD_TEXT_I2C_PCF8574)
        p_LCD = new I2CPCF8574TextLCD(LCD_COLS, LCD_ROWS, LCD_I2C_ADDR);
    #elif defined(LCD_TEXT_I2C_RGB)
        p_LCD = new I2CRGBTextLCD(LCD_COLS, LCD_ROWS, 123, LCD_BACKLIGHT_COLOR);
    #elif defined(LCD_TEXT_I2C_AIP31068)
        p_LCD = new I2CAIP31068TextLCD(Backlight, LCD_COLS, LCD_ROWS, LCD_I2C_ADDR);
    #elif defined(LCD_TEXT_SPI_AIP31068)
        p_LCD = new SPIAIP31068TextLCD(Backlight, LCD_COLS, LCD_ROWS, LCD_PIN_SS, LCD_PIN_SCLK, LCD_PIN_MOSI, LCD_PIN_MISO);
    #elif defined(LCD_TEXT_UT)
        /*p_LCD = new UTTextLCD(Backlight);*/
    #else
        #error LCD is not defined!
    #endif

    return p_LCD;
}

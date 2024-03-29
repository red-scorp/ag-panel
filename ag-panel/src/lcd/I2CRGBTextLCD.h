/** @file I2CRGBTextLCD.h
    @brief AG-Panel Project I2C RGB keypad's text (hd44780) LCD interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

const uint32_t DefaultI2CRGBTextLCDDefaultColor = DefaultBacklightRGBColor;

/** @brief I2C RGB Text LCD class

    This class implements a 4-bit text LCD display based on HD44780 and connected
    with a help of MCP23017 I2C 16-bit digital I/O expander chip.
    This class implements it's own backlight control.
 */
class I2CRGBTextLCD: public AbstractTextLCD {

public:
    explicit I2CRGBTextLCD(
        uint8_t Columns,            /**< Number of columns of the text LCD */
        uint8_t Rows,               /**< Number of rows of the text LCD */
        uint8_t I2CAddress,         /**< I2C address of digital I/O expander chip */
        uint32_t DefaultColor = DefaultI2CRGBTextLCDDefaultColor    /**< Default color if not specified */
    ): AbstractTextLCD(nullptr, Columns, Rows),
        m_I2CAddress(I2CAddress),
        m_DefaultColor(DefaultColor),
        m_Lowlevel(nullptr) { Init(); }
    virtual ~I2CRGBTextLCD() override { Exit(); }

    virtual void SetBacklight(bool on) override;
    virtual void SetBacklight(uint8_t brightness) override;
    virtual void SetBacklight(uint8_t red, uint8_t green, uint8_t blue) override;
    virtual void SetBacklight(uint32_t rgb) override;

    virtual void Clear() override;
    virtual void SetCursor(uint8_t column, uint8_t row) override;
    virtual void Print(const char *str) override;
    virtual void Print(char character) override;

    virtual void Write(uint8_t byte) override;
    virtual void Command(uint8_t byte) override;

    void *GetLowLevel() const { return m_Lowlevel; }

protected:
    uint8_t m_I2CAddress;         /**< I2C address of digital I/O expander chip */
    uint32_t m_DefaultColor;      /**< Default color if not specified */

private:
    void *m_Lowlevel;       /**< Pointer to Low-Level LCD class */
    bool Init();
    void Exit();
};

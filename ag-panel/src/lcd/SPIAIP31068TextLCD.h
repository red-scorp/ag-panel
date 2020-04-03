/*!
  \file SPIAIP31068TextLCD.h
  \brief AG-Panel Project SPI 8-bit text (AIP31068) LCD interface
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

/*!
  \brief SPI Text LCD class

  This class implements a 8-bit text LCD display based on AIP31068 chip, similar to
  HD44780 but with I2C and SPI interface.
  This class implements it's own backlight control.
 */
class SPIAIP31068TextLCD: public AbstractTextLCD {

public:
  SPIAIP31068TextLCD(
    AbstractBacklight *Backlight,     /*!< External backlight class pointer */
    uint8_t Columns,            /*!< Number of columns of the text LCD */
    uint8_t Rows,               /*!< Number of rows of the text LCD */
    uint8_t SSPin               /*!< Slave Select pin */
  ): AbstractTextLCD(Backlight, Columns, Rows),
    m_SSPin(SSPin),
    m_SCLKPin(SCK),
    m_MOSIPin(MOSI),
    m_MISOPin(MISO),
    m_Lowlevel(nullptr) { Init(); }
  SPIAIP31068TextLCD(
    AbstractBacklight *Backlight,     /*!< External backlight class pointer */
    uint8_t Columns,            /*!< Number of columns of the text LCD */
    uint8_t Rows,               /*!< Number of rows of the text LCD */
    uint8_t SSPin,              /*!< Slave Select pin */
    uint8_t SCLKPin,            /*!< Serial Clock pin */
    uint8_t MOSIPin,            /*!< Master Output Slave Input pin */
    uint8_t MISOPin             /*!< Master Input Slave Output pin */
  ): AbstractTextLCD(Backlight, Columns, Rows),
    m_SSPin(SSPin),
    m_SCLKPin(SCLKPin),
    m_MOSIPin(MOSIPin),
    m_MISOPin(MISOPin),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~SPIAIP31068TextLCD() override { Exit(); }

  virtual void Clear() override;
  virtual void SetCursor(uint8_t column, uint8_t row) override;
  virtual void Print(const char *str) override;

  virtual void Write(uint8_t byte) override;
  virtual void Command(uint8_t byte) override;

protected:
  uint8_t m_SSPin;        /*!< Slave Select pin */
  uint8_t m_SCLKPin;      /*!< Serial Clock pin */
  uint8_t m_MOSIPin;      /*!< Master Output Slave Input pin */
  uint8_t m_MISOPin;      /*!< Master Input Slave Output pin */

private:
  void *m_Lowlevel;       /*!< Pointer to Low-Level LCD class */
  bool Init();
  void Exit();
};

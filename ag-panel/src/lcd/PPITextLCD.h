/*!
  \file PPITextLCD.h
  \brief AG-Panel Project PPI (parallel) 4 and 8-bit text (hd44780) LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

/*!
  \brief PPI (Parallel) Text LCD class

  This class implements a parallel 8- and 4-bit text LCD display based on HD44780
  and connected with several digital pins.
  This class uses a backlight implementation given by a pointer.
 */
class PPITextLCD: public AbstractTextLCD {

public:
  explicit PPITextLCD(
    AbstractBacklight *Backlight,     /*!< External backlight class pointer */
    uint8_t Columns,            /*!< Number of columns of the text LCD */
    uint8_t Rows,               /*!< Number of rows of the text LCD */
    uint8_t RSPin,              /*!< Register Select (RS) digital pin */
    uint8_t RWPin,              /*!< Read/Write (R/W) digital pin */
    uint8_t EnablePin,          /*!< Clock (Enable) digital pin */
    uint8_t D0Pin,              /*!< Data bit 0 digital pin */
    uint8_t D1Pin,              /*!< Data bit 1 digital pin */
    uint8_t D2Pin,              /*!< Data bit 2 digital pin */
    uint8_t D3Pin,              /*!< Data bit 3 digital pin */
    uint8_t D4Pin,              /*!< Data bit 4 digital pin */
    uint8_t D5Pin,              /*!< Data bit 5 digital pin */
    uint8_t D6Pin,              /*!< Data bit 6 digital pin */
    uint8_t D7Pin               /*!< Data bit 7 digital pin */
  ): AbstractTextLCD(Backlight, Columns, Rows),
    m_RSPin(RSPin),
    m_RWPin(RWPin),
    m_EnablePin(EnablePin),
    m_D0Pin(D0Pin),
    m_D1Pin(D1Pin),
    m_D2Pin(D2Pin),
    m_D3Pin(D3Pin),
    m_D4Pin(D4Pin),
    m_D5Pin(D5Pin),
    m_D6Pin(D6Pin),
    m_D7Pin(D7Pin),
    m_Lowlevel(nullptr) { Init(); }
  explicit PPITextLCD(
    AbstractBacklight *Backlight,     /*!< External backlight class pointer */
    uint8_t Columns,            /*!< Number of columns of the text LCD */
    uint8_t Rows,               /*!< Number of rows of the text LCD */
    uint8_t RSPin,              /*!< Register Select (RS) digital pin */
    uint8_t RWPin,              /*!< Read/Write (R/W) digital pin */
    uint8_t EnablePin,          /*!< Clock (Enable) digital pin */
    uint8_t D4Pin,              /*!< Data bit 4 digital pin */
    uint8_t D5Pin,              /*!< Data bit 5 digital pin */
    uint8_t D6Pin,              /*!< Data bit 6 digital pin */
    uint8_t D7Pin               /*!< Data bit 7 digital pin */
  ): AbstractTextLCD(Backlight, Columns, Rows),
    m_RSPin(RSPin),
    m_RWPin(RWPin),
    m_EnablePin(EnablePin),
    m_D0Pin(InvalidPin),
    m_D1Pin(InvalidPin),
    m_D2Pin(InvalidPin),
    m_D3Pin(InvalidPin),
    m_D4Pin(D4Pin),
    m_D5Pin(D5Pin),
    m_D6Pin(D6Pin),
    m_D7Pin(D7Pin),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~PPITextLCD() override { Exit(); }

  using AbstractTextLCD::SetBacklight;
  virtual void Clear() override;
  virtual void SetCursor(uint8_t column, uint8_t row) override;
  virtual void Print(const char *str) override;
  virtual void Print(char character) override;

  virtual void Write(uint8_t byte) override;
  virtual void Command(uint8_t byte) override;

protected:
  uint8_t m_RSPin;              /*!< Register Select (RS) digital pin */
  uint8_t m_RWPin;              /*!< Read/Write (R/W) digital pin */
  uint8_t m_EnablePin;          /*!< Clock (Enable) digital pin */
  uint8_t m_D0Pin;              /*!< Data bit 0 digital pin (only 8-bit mode) */
  uint8_t m_D1Pin;              /*!< Data bit 1 digital pin (only 8-bit mode) */
  uint8_t m_D2Pin;              /*!< Data bit 2 digital pin (only 8-bit mode) */
  uint8_t m_D3Pin;              /*!< Data bit 3 digital pin (only 8-bit mode) */
  uint8_t m_D4Pin;              /*!< Data bit 4 digital pin */
  uint8_t m_D5Pin;              /*!< Data bit 5 digital pin */
  uint8_t m_D6Pin;              /*!< Data bit 6 digital pin */
  uint8_t m_D7Pin;              /*!< Data bit 7 digital pin */

private:
  void *m_Lowlevel;       /*!< Pointer to Low-Level LCD class */
  bool Init();
  void Exit();
};

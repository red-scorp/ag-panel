/*!
  \file RotaryEncoder.h
  \brief AG-Panel Project rotary encoder keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultRotaryEncoderD1Pin = 2;      /*!< Default first digital pin of rotary encoder */
const uint8_t DefaultRotaryEncoderD2Pin = 3;      /*!< Default second digital pin of rotary encoder */
const uint8_t DefaultRotaryEncoderButtonPin = 11; /*!< Default digital pin of select button */

/*!
  \brief Digital Matrix class
  This class implements rotary encoder based on two digital pins for encoder an simgle digital pin for select key.
 */
class RotaryEncoder: public AbstractKeyboard {

public:
  RotaryEncoder(
    uint8_t D1Pin = DefaultRotaryEncoderD1Pin,        /*!< First digital pin of rotary encoder */
    uint8_t D2Pin = DefaultRotaryEncoderD1Pin,        /*!< Second digital pin of rotary encoder */
    uint8_t ButtonPin = DefaultRotaryEncoderButtonPin /*!< Digital pin of select button */
  ): AbstractKeyboard(),
    m_D1Pin(D1Pin),
    m_D2Pin(D2Pin),
    m_ButtonPin(ButtonPin) { Init(); }
  virtual ~RotaryEncoder() override { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_D1Pin;        /*!< First digital pin of rotary encoder */
  uint8_t m_D2Pin;        /*!< Second digital pin of rotary encoder */
  uint8_t m_ButtonPin;    /*!< Digital pin of select button */

private:
  bool Init();
  void Exit();
};

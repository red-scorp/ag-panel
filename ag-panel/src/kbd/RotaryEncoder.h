/*!
  \file RotaryEncoder.h
  \brief AG-Panel Project rotary encoder keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultRotaryEncoderD1Pin = 2;
const uint8_t DefaultRotaryEncoderD2Pin = 3;
const uint8_t DefaultRotaryEncoderButtonPin = 11;

class RotaryEncoder: public AbstractKeyboard {

public:
  RotaryEncoder(uint8_t D1Pin = DefaultRotaryEncoderD1Pin, uint8_t D2Pin = DefaultRotaryEncoderD1Pin, uint8_t ButtonPin = DefaultRotaryEncoderButtonPin): AbstractKeyboard(), m_D1Pin(D1Pin), m_D2Pin(D2Pin), m_ButtonPin(ButtonPin) { Init(); }
  virtual ~RotaryEncoder() override { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_D1Pin;
  uint8_t m_D2Pin;
  uint8_t m_ButtonPin;

private:
  bool Init();
  void Exit();
};

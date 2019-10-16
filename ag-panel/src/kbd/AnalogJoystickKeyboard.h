/*!
  \file AnalogJoystickKeyboard.h
  \brief AG-Panel Project analog joystick keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultAnalogJoystickXPin = A0;
const uint8_t DefaultAnalogJoystickYPin = A1;
const uint8_t DefaultAnalogJoystickButtonPin = 12;

class AnalogJoystickKeyboard: public AbstractKeyboard {

public:
  AnalogJoystickKeyboard(uint8_t XPin = DefaultAnalogJoystickXPin, uint8_t YPin = DefaultAnalogJoystickYPin, uint8_t ButtonPin = DefaultAnalogJoystickButtonPin): AbstractKeyboard(), m_XPin(XPin), m_YPin(YPin), m_ButtonPin(ButtonPin) { Init(); }
  virtual ~AnalogJoystickKeyboard() { Exit(); }

  virtual uint8_t GetKey();

protected:
  uint8_t m_XPin;
  uint8_t m_YPin;
  uint8_t m_ButtonPin;

private:
  bool Init();
  void Exit();
};

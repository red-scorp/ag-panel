/*!
  \file AnalogJoystick.cpp
  \brief AG-Panel Project analog joystick keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"
#include "AnalogJoystick.h"

/* TODO: Change KBD_*_CENTER and KBD_THRESHOLD macros to constants */
#define KBD_X_CENTER        512
#define KBD_Y_CENTER        512
#define KBD_THRESHOLD       50

bool AnalogJoystick::Init() {
  pinMode(m_ButtonPin, INPUT_PULLUP);
  return true;
}

void AnalogJoystick::Exit() {
}

uint8_t AnalogJoystick::GetKey() {

  uint16_t x = analogRead(m_XPin);
  uint16_t y = analogRead(m_YPin);
  uint8_t button = digitalRead(m_ButtonPin);

  if(button == LOW)
    return KeyDefaultSelect;
  if(x < (KBD_X_CENTER - KBD_THRESHOLD))
    return KeyDefaultLeft;
  if(x > (KBD_X_CENTER + KBD_THRESHOLD))
    return KeyDefaultRight;
  if(y < (KBD_Y_CENTER - KBD_THRESHOLD))
    return KeyDefaultDown;
  if(y > (KBD_Y_CENTER + KBD_THRESHOLD))
    return KeyDefaultUp;
  return KeyNone;
}
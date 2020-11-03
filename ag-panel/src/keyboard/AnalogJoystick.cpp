/*!
  \file AnalogJoystick.cpp
  \brief AG-Panel Project analog joystick keyboard implementation
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "../../config.h"
#include "AnalogJoystick.h"

static const int s_AnalogJoystickXCenter = MaxAnalogValue / 2;      /*!< Center position of analog input scale for X axis */
static const int s_AnalogJoystickYCenter = MaxAnalogValue / 2;      /*!< Center position of analog input scale for X axis */
static const int s_AnalogJoystickThreshold = MaxAnalogValue / 20;   /*!< Insensitive area (resting position) around center of X and Y axis */

static const uint8_t s_AnalogJoystickKeysMax = 5;   /*!< Maximum of detectable keys for the class */

/*!
  \brief Initialization of analog joystick

  Configures select button pin.
  \returns true
 */
bool AnalogJoystick::Init() {
  pinMode(m_ButtonPin, INPUT_PULLUP);
  return true;
}

/*!
  \brief Deinitialisation of analog joystick class
 */
void AnalogJoystick::Exit() {
}

/*!
  \brief Get a key of analog joystick

  Reads X- and Y-direction analog pins and a select button digital pin.
  \returns #KeyNone if no new actions detected, else a key code
 */
uint8_t AnalogJoystick::GetKey() {
  uint16_t x = analogRead(m_XPin);
  uint16_t y = analogRead(m_YPin);
  uint8_t button = digitalRead(m_ButtonPin);

  if(button == LOW)
    return KeyDefaultSelect;
  if(x < (s_AnalogJoystickXCenter - s_AnalogJoystickThreshold))
    return KeyDefaultLeft;
  if(x > (s_AnalogJoystickXCenter + s_AnalogJoystickThreshold))
    return KeyDefaultRight;
  if(y < (s_AnalogJoystickYCenter - s_AnalogJoystickThreshold))
    return KeyDefaultDown;
  if(y > (s_AnalogJoystickYCenter + s_AnalogJoystickThreshold))
    return KeyDefaultUp;
  return KeyNone;
}

/*!
  \brief Get number of keys supported by analog joystick

  \returns Number of supported keys
 */
uint8_t AnalogJoystick::GetKeyCount() {
  return s_AnalogJoystickKeysMax;
}

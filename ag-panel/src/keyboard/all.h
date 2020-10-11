/*!
  \file all.h
  \brief AG-Panel Project all Keyboard includes
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "AbstractKeyboard.h"

#include "NoneKeyboard.h"
#include "AnalogKeypad.h"
#include "AnalogJoystick.h"
#include "AnalogMatrix.h"
#include "RotaryEncoder.h"
#include "I2CMPR121CapacitiveKeypad.h"
#include "I2CTTP229CapacitiveKeypad.h"
#include "DigitalMatrix.h"
#include "I2CRGBKeypad.h"
#include "SimpleButton.h"
#include "JoinedKeyboard.h"

AbstractKeyboard *initKeyboard(AbstractLCD *p_LCD);

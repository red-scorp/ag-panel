/*! \file all.h
    \brief AG-Panel Project all Keyboard includes
    \copyright (C) 2019-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "AbstractKeyboard.h"

#ifndef UNIT_TEST

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

#endif/*UNIT_TEST*/

AbstractKeyboard *initKeyboard(AbstractLCD *p_LCD);

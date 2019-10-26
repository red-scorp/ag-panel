/*!
  \file kbd.cpp
  \brief AG-Panel Project Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#include "AbstractKeyboard.h"
#include "NoneKeyboard.h"
#include "AnalogKeypad.h"
#include "AnalogJoystick.h"
#include "AnalogMatrix.h"

/* Keyboard Configuration sanity check */
#if (!defined(KBD_NONE) && !defined(KBD_D_MATRIX) && !defined(KBD_A_JOYSTICK) \
  && !defined(KBD_A_KEYPAD) && !defined(KBD_ROTARY_ENCODER) && !defined(KBD_A_MATRIX) \
  && !defined(KBD_I2C_RGB) && !defined(KBD_I2C_C_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_D_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_NONE) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_NONE) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_NONE) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_NONE) && defined(KBD_I2C_C_MATRIX)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_I2C_C_MATRIX)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_I2C_C_MATRIX)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_I2C_C_MATRIX)) \
  || (defined(KBD_ROTARY_ENCODER) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_ROTARY_ENCODER) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_ROTARY_ENCODER) && defined(KBD_I2C_C_MATRIX)) \
  || (defined(KBD_A_MATRIX) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_A_MATRIX) && defined(KBD_I2C_C_MATRIX)) \
  || (defined(KBD_I2C_RGB) && defined(KBD_I2C_C_MATRIX))
#error You should define KBD_NONE, KBD_D_MATRIX, KBD_A_JOYSTICK, KBD_A_KEYPAD, KBD_ROTARY_ENCODER, KBD_A_MATRIX, KBD_I2C_RGB or KBD_I2C_C_MATRIX and only one of them!
#endif

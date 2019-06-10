/*!
  \file kbd.cpp
  \brief ALoS-Panel Project Keyboard code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

/* Keyboard Configuration sanity check */
#if (!defined(KBD_NONE) && !defined(KBD_D_MATRIX) && !defined(KBD_A_JOYSTICK) \
  && !defined(KBD_A_KEYPAD) && !defined(KBD_ROTARY_ENCODER) && !defined(KBD_A_MATRIX) \
  && !defined(KBD_I2C_RGB)) \
  || (defined(KBD_NONE) && defined(KBD_D_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_NONE) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_NONE) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_NONE) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_ROTARY_ENCODER) && defined(KBD_A_MATRIX)) \
  || (defined(KBD_ROTARY_ENCODER) && defined(KBD_I2C_RGB)) \
  || (defined(KBD_A_MATRIX) && defined(KBD_I2C_RGB))
#error You should define KBD_NONE, KBD_D_MATRIX, KBD_A_JOYSTICK, KBD_A_KEYPAD, KBD_ROTARY_ENCODER, KBD_A_MATRIX or KBD_I2C_RGB and only one of them!
#endif

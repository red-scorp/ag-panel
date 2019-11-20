/*!
  \file kbd.cpp
  \brief AG-Panel Project Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if 0

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

#include "AbstractKeyboard.h"
#include "NoneKeyboard.h"
#include "AnalogKeypad.h"
#include "AnalogJoystick.h"
#include "AnalogMatrix.h"
#include "RotaryEncoder.h"
#include "I2CCapacitiveMatrix.h"
#include "DigitalMatrix.h"
#include "I2CRGBKeypad.h"

static AbstractKeyboard *Keyboard = nullptr;

/*! \brief Initialization of keyboard
 */
void kbd_init() {
#if defined(KBD_NONE)
  Keyboard = new NoneKeyboard();
#elif defined(KBD_D_MATRIX)
  static const uint8_t cols[] = {
  #if KBD_COLS >= 1
    KBD_PIN_C1,
    #if KBD_COLS >= 2
      KBD_PIN_C2,
      #if KBD_COLS >= 3
        KBD_PIN_C3,
        #if KBD_COLS >= 4
          KBD_PIN_C4,
          #if KBD_COLS >= 5
            #error Only 4 Columns are supported for now
          #endif
        #endif
      #endif
    #endif
  #endif
  };
  static const uint8_t rows[] = {
  #if KBD_ROWS >= 1
    KBD_PIN_R1,
    #if KBD_ROWS >= 2
      KBD_PIN_R2,
      #if KBD_ROWS >= 3
        KBD_PIN_R3,
        #if KBD_ROWS >= 4
          KBD_PIN_R4,
          #if KBD_ROWS >= 5
            #error Only 4 Rows are supported for now
          #endif
        #endif
      #endif
    #endif
  #endif
  };
  Keyboard = new DigitalMatrix(KBD_COLS, KBD_ROWS, cols, rows);
#elif defined(KBD_A_JOYSTICK)
  Keyboard = new AnalogJoystick(KBD_PIN_X, KBD_PIN_Y, KBD_PIN_BTN);
#elif defined(KBD_A_KEYPAD)
  Keyboard = new AnalogKeypad(KBD_PIN_DATA);
#elif defined(KBD_ROTARY_ENCODER)
  Keyboard = new RotaryEncoder(KBD_PIN_D1, KBD_PIN_D2, KBD_PIN_BTN);
#elif defined(KBD_A_MATRIX)
  static const uint16_t data_array[KBD_ROWS * KBD_COLS] = KBD_DATA_ARRAY;
  Keyboard = new AnalogMatrix(KBD_COLS, KBD_ROWS, data_array, KBD_PIN_DATA);
#elif defined(KBD_I2C_RGB)
  Keyboard = new I2CRGBKeypad();
#elif defined(KBD_I2C_C_MATRIX)
  Keyboard = new I2CCapacitiveMatrix(KBD_COLS, KBD_ROWS, KBD_I2C_ADDR);
#endif
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  uint8_t key = Keyboard->GetKey();
  if(key == KeyNone) {
    return KBD_KEY_NONE;
  } else {
    return KBD_KEY(key >> 2, key & 0x3);
  }
}

#endif

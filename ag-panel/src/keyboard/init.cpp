/*!
  \file init.cpp
  \brief AG-Panel Project Keyboard initialization
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"

#include "all.h"

/*!
  \brief Initialize keyboard

  This function chooses one or more keyboard classes to use based on configuration defined in config.h
  \returns Pointer to keyboard class
 */
AbstractKeyboard *initKeyboard() {
  AbstractKeyboard *Keyboard = nullptr;

  /* Initializae joined keyboard subsystem */
  #if defined(KBD_JOINED)
    JoinedKeyboard *JoinedKeyboard = new JoinedKeyboard();
  #endif

  /* Initialize rael keyboard classes and join if it is wished to be done */
  #if defined(KBD_NONE)
    Keyboard = new NoneKeyboard();
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_D_MATRIX)
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
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_JOYSTICK)
    Keyboard = new AnalogJoystick(KBD_PIN_X, KBD_PIN_Y, KBD_PIN_BTN);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_KEYPAD)
    Keyboard = new AnalogKeypad(KBD_PIN_DATA);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_ROTARY_ENCODER)
    Keyboard = new RotaryEncoder(KBD_PIN_D1, KBD_PIN_D2, KBD_PIN_BTN);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_MATRIX)
    static const uint16_t data_array[KBD_ROWS * KBD_COLS] = KBD_DATA_ARRAY;
    Keyboard = new AnalogMatrix(KBD_COLS, KBD_ROWS, data_array, KBD_PIN_DATA);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_RGB)
    #if !defined(LCD_TEXT_I2C_RGB)
      #error 'KBD_I2C_RGB' must be defined together with 'LCD_TEXT_I2C_RGB'!
    #endif
    Keyboard = new I2CRGBKeypad(s_LCD);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_C_MPR121_KEYPAD)
    Keyboard = new I2CMPR121CapacitiveKeypad(KBD_KEYS, KBD_I2C_ADDR);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_C_TTP229_KEYPAD)
    Keyboard = new I2CTTP229CapacitiveKeypad(KBD_KEYS, KBD_I2C_ADDR);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_BUTTON)
    static const uint8_t pins[] = KBD_PIN_ARRAY;
    Keyboard = new SimpleButton(KBD_NUM, pins);
    #if defined(KBD_JOINED)
      JoinedKeyboard->AddKeyboard(Keyboard);
      Keyboard = nullptr;
    #endif
  #endif

  /* Substitute last keyboard class with joined keyboard if enabled */
  #if defined(KBD_JOINED)
    Keyboard = JoinedKeyboard;
  #endif

  return Keyboard;
}

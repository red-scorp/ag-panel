/*!
  \file init.cpp
  \brief AG-Panel Project Keyboard initialization
  \copyright (C) 2020-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#include "../private.h"
#include "../../config.h"

#include "all.h"

/*!
  \brief Initialize keyboard

  This function chooses one or more keyboard classes to use based on configuration defined in config.h
  \returns Pointer to keyboard class
 */
AbstractKeyboard *initKeyboard(AbstractLCD *p_LCD) {
  AbstractKeyboard *p_Keyboard = nullptr;

  /* Initialize joined keyboard subsystem */
  #if defined(KBD_JOINED)
    JoinedKeyboard *p_JoinedKeyboard = new JoinedKeyboard();
  #endif

  /* Initialize real keyboard classes and join if it is wished to be done */
  #if defined(KBD_NONE)
    p_Keyboard = new NoneKeyboard();
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
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
    p_Keyboard = new DigitalMatrix(KBD_COLS, KBD_ROWS, cols, rows);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_JOYSTICK)
    p_Keyboard = new AnalogJoystick(KBD_PIN_X, KBD_PIN_Y, KBD_PIN_BTN);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_KEYPAD)
    static const AnalogDataRange ranges[AbstractKeyboardAnalogDataRangeIndexMax] = {
      {KBD_DATA_UP_MIN, KBD_DATA_UP_MAX},
      {KBD_DATA_DOWN_MIN, KBD_DATA_DOWN_MAX},
      {KBD_DATA_LEFT_MIN, KBD_DATA_LEFT_MAX},
      {KBD_DATA_RIGHT_MIN, KBD_DATA_RIGHT_MAX},
      {KBD_DATA_SELECT_MIN, KBD_DATA_SELECT_MAX},
    };
    p_Keyboard = new AnalogKeypad(KBD_PIN_DATA, ranges);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_ROTARY_ENCODER)
    p_Keyboard = new RotaryEncoder(KBD_PIN_D1, KBD_PIN_D2, KBD_PIN_BTN);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_MATRIX)
    static const uint16_t data_array[KBD_ROWS * KBD_COLS] = KBD_DATA_ARRAY;
    p_Keyboard = new AnalogMatrix(KBD_COLS, KBD_ROWS, data_array, KBD_PIN_DATA);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_RGB)
    #if !defined(LCD_TEXT_I2C_RGB)
      #error 'KBD_I2C_RGB' must be defined together with 'LCD_TEXT_I2C_RGB'!
    #endif
    p_Keyboard = new I2CRGBKeypad(p_LCD);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_C_MPR121_KEYPAD)
    p_Keyboard = new I2CMPR121CapacitiveKeypad(KBD_KEYS, KBD_I2C_ADDR);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_C_TTP229_KEYPAD)
    p_Keyboard = new I2CTTP229CapacitiveKeypad(KBD_KEYS, KBD_I2C_ADDR);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_BUTTON)
    static const uint8_t pins[] = KBD_PIN_ARRAY;
    p_Keyboard = new SimpleButton(KBD_NUM, pins);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_UT)
    /*p_Keyboard = new UTKeyboard();*/
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(p_Keyboard);
      p_Keyboard = nullptr;
    #endif
  #endif

  /* Substitute last keyboard class with joined keyboard if enabled */
  #if defined(KBD_JOINED)
    p_Keyboard = p_JoinedKeyboard;
  #endif

  return p_Keyboard;
}

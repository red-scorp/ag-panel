/*!
  \file init.cpp
  \brief AG-Panel Project LCD backlight initialization
  \copyright (C) 2020-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#include "../../private.h"
#include "../../../config.h"

#include "all.h"

/*!
  \brief Initialize LCD backlight

  This function chooses one of backlight classes to use based on configuration defined in config.h
  \returns Pointer to LCD backlight class
 */
AbstractBacklight *initBacklight() {
  AbstractBacklight *p_Backlight = nullptr;

  #if defined(LCD_BACKLIGHT_NONE)
    p_Backlight = new NoneBacklight();
  #elif defined(LCD_BACKLIGHT_ONOFF)
    p_Backlight = new BinaryBacklight(LCD_PIN_BACKLIGHT);
  #elif defined(LCD_BACKLIGHT_PWM)
    #if defined(LCD_BL_PWM_MAX)
      p_Backlight = new PWMBacklight(LCD_PIN_BACKLIGHT, LCD_BL_PWM_MAX);
    #else
      p_Backlight = new PWMBacklight(LCD_PIN_BACKLIGHT);
    #endif
  #elif defined(LCD_BACKLIGHT_RGB_ONOFF)
    p_Backlight = new RGBBinaryBacklight(LCD_PIN_BACKLIGHT_R, LCD_PIN_BACKLIGHT_G, LCD_PIN_BACKLIGHT_B);
  #elif defined(LCD_BACKLIGHT_RGB_PWM)
    #if defined(LCD_BL_PWM_MAX)
      p_Backlight = new RGBPWMBacklight(LCD_PIN_BACKLIGHT_R, LCD_PIN_BACKLIGHT_G, LCD_PIN_BACKLIGHT_B, LCD_BACKLIGHT_COLOR, LCD_BL_PWM_MAX);
    #else
      p_Backlight = new RGBPWMBacklight(LCD_PIN_BACKLIGHT_R, LCD_PIN_BACKLIGHT_G, LCD_PIN_BACKLIGHT_B, LCD_BACKLIGHT_COLOR);
    #endif
  #elif defined(LCD_BACKLIGHT_I2C_RGB_PWM)
    #if defined(LCD_BL_PWM_MAX)
      p_Backlight = new I2CRGBPWMBacklight(LCD_BACKLIGHT_CHAN_R, LCD_BACKLIGHT_CHAN_G, LCD_BACKLIGHT_CHAN_B, LCD_BACKLIGHT_I2C_ADDR, LCD_BACKLIGHT_COLOR, LCD_BL_PWM_MAX);
    #else
      p_Backlight = new I2CRGBPWMBacklight(LCD_BACKLIGHT_CHAN_R, LCD_BACKLIGHT_CHAN_G, LCD_BACKLIGHT_CHAN_B, LCD_BACKLIGHT_I2C_ADDR, LCD_BACKLIGHT_COLOR);
    #endif
  #elif defined(LCD_BACKLIGHT_UT)
    /*p_Backlight = new UTBacklight();*/
  #endif

  return p_Backlight;
}
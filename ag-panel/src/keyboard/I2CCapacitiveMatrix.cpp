/*!
  \file I2CCapacitiveMatrix.cpp
  \brief AG-Panel Project I2C capacitive matrix keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "../../config.h"
#include "I2CCapacitiveMatrix.h"

#include <Adafruit_MPR121.h>

/*!
  \brief Initialization of capacitive matrix

  Begin communication with controller of capacitive matrix.
  \returns true
 */
bool I2CCapacitiveMatrix::Init() {
  m_Lowlevel = new Adafruit_MPR121;   /* TODO: Use m_I2CAddress somewhere? */
  Adafruit_MPR121 *p_I2CKbd = (Adafruit_MPR121*)m_Lowlevel;
  p_I2CKbd->begin();
  return true;
}

/*!
  \brief Deinitialisation of capacitive matrix class
 */
void I2CCapacitiveMatrix::Exit() {
  Adafruit_MPR121 *p_I2CKbd = (Adafruit_MPR121*)m_Lowlevel;
  if(p_I2CKbd != nullptr)
    delete p_I2CKbd;
  m_Lowlevel = nullptr;
}

/*!
  \brief Get a key of capacitive matrix

  Reads touch status from I2C touch controller to find out what key has been pressed.
  \returns #KeyNone if no new actions detected, else a key code
 */
uint8_t I2CCapacitiveMatrix::GetKey() {

  Adafruit_MPR121 *p_I2CKbd = (Adafruit_MPR121*)m_Lowlevel;

  const uint16_t watch_mask = (uint16_t)(1l << (m_Columns * m_Rows + 1)) - 1; /* watch only lower CxR bits, ignore rest */
  static uint16_t last_touched = 0;

  uint16_t touched = p_I2CKbd->touched() & watch_mask;
  uint16_t pressed = (touched ^ last_touched) & touched;
  uint16_t released = (touched ^ last_touched) & last_touched;

  last_touched ^= released; /* remove all released keys */
  if(pressed != 0) {
    for(uint8_t i = 0; i < (m_Columns * m_Rows); i++) {
      if(pressed & (1 << i)) {
        last_touched ^= (1 << i); /* remember only one pressed key we are going to send to a host */
        uint8_t c = i % m_Columns;
        uint8_t r = i / m_Columns;
        return r * m_Columns + c + 1;
      }
    }
  }

  return KeyNone;
}

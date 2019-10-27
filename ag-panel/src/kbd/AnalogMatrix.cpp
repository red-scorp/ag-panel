/*!
  \file AnalogMatrix.cpp
  \brief AG-Panel Project analog keypad keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"
#include "AnalogMatrix.h"

/* TODO: Change all KBD_DATA_* macros to constants */
#define KBD_DATA_TOLERANCE  25
/*#define KBD_DATA_ARRAY      {1023, 930, 850, 790, \
                             680, 640, 600, 570, \
                             512, 487, 465, 445, \
                             410, 330, 277, 238}*/
/*#define KBD_DATA_ARRAY      {1023, 930, 850, \
                             790, 730, 680, \
                             640, 600, 570, \
                             540, 510, 490}*/

bool AnalogMatrix::Init() {
  /* no initialization needed for analog pins */
  return true;
}

void AnalogMatrix::Exit() {
}

uint8_t AnalogMatrix::GetKey() {

  uint16_t data = analogRead(m_DataPin);

  for(uint8_t c = 0; c < m_Columns; c++)
    for(uint8_t r = 0; r < m_Rows; r++) {
      if(data >= m_DataArray[r * m_Columns + c] - KBD_DATA_TOLERANCE &&
        data <= m_DataArray[r * m_Columns + c] + KBD_DATA_TOLERANCE) {
        return r * m_Columns + c + 1;
      }
    }
  return KeyNone;
}

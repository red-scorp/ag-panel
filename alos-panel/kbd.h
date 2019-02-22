/*!
  \file kbd.h
  \brief ALoS-Panel Project Keyboard interface
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef KBD_H
#define KBD_H

#include "config.h"

#define KBD_KEY_NONE        0x00

#define KBD_KEY_UP          0x01  /* KeyMatrix_1_1=Up */
#define KBD_KEY_DOWN        0x02  /* KeyMatrix_1_2=Down */
#define KBD_KEY_LEFT        0x04  /* KeyMatrix_1_3=Left */
#define KBD_KEY_RIGHT       0x08  /* KeyMatrix_1_4=Right */
#define KBD_KEY_SELECT      0x11  /* KeyMatrix_2_1=Enter */

void kbd_init();
uint8_t kbd_getkey();

#endif//KBD_H

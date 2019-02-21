/*!
  \file kbd.h
  \brief ALoS-Panel Project Keyboard interface
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef KBD_H
#define KBD_H

#include "config.h"

#define KBD_KEY_NONE        0xFF

#define KBD_KEY_UP          0x01
#define KBD_KEY_DOWN        0x02
#define KBD_KEY_LEFT        0x03
#define KBD_KEY_RIGHT       0x04
#define KBD_KEY_SELECT      0x05

void kbd_init();
uint8_t kbd_getkey();

#endif//KBD_H

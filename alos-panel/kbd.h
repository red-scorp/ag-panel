/*!
  \file kbd.h
  \brief ALoS-Panel Project Keyboard interface
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef KBD_H
#define KBD_H

#include "config.h"

#define KBD_KEY_NONE        0xFF

void kbd_init();
uint8_t kbd_getkey();

#endif//KBD_H

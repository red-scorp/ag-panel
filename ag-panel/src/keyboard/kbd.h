/*!
  \file kbd.h
  \brief AG-Panel Project Keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef KBD_H
#define KBD_H

#if 0

#include "../../config.h"

#define KBD_KEY_NONE        0x00  /* No key is pressed */

/* Key conversion for LoS-Panel keypad values:
 * Rows are bits:
 *  - 0x?1 => KeyMatrix_?_1
 *  - 0x?2 => KeyMatrix_?_2
 *  - 0x?4 => KeyMatrix_?_3
 *  - 0x?8 => KeyMatrix_?_4
 * Columns are numbers+1:
 *  - 0x0? => KeyMatrix_1_?
 *  - 0x1? => KeyMatrix_2_?
 *  - 0x2? => KeyMatrix_3_?
 *  - 0x3? => KeyMatrix_4_?
 *  - 0x4? => KeyMatrix_5_?
 */
#define KBD_KEY(r, c)       (((c) << 4) | (1 << (r)))

#define KBD_KEY_UP          KBD_KEY(0, 0)  /* KeyMatrix_1_1=Up */
#define KBD_KEY_DOWN        KBD_KEY(0, 1)  /* KeyMatrix_1_2=Down */
#define KBD_KEY_LEFT        KBD_KEY(0, 2)  /* KeyMatrix_1_3=Left */
#define KBD_KEY_RIGHT       KBD_KEY(0, 3)  /* KeyMatrix_1_4=Right */
#define KBD_KEY_SELECT      KBD_KEY(1, 0)  /* KeyMatrix_2_1=Enter */

void kbd_init();
uint8_t kbd_getkey();

#endif

#endif//KBD_H

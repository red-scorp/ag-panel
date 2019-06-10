/*!
  \file kbd.h
  \brief ALoS-Panel Project Keyboard interface
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef KBD_H
#define KBD_H

#include "../../config.h"

#define KBD_KEY_NONE        0x00  /* No key is pressed */

#define KBD_KEY_UP          0x01  /* KeyMatrix_1_1=Up */
#define KBD_KEY_DOWN        0x02  /* KeyMatrix_1_2=Down */
#define KBD_KEY_LEFT        0x04  /* KeyMatrix_1_3=Left */
#define KBD_KEY_RIGHT       0x08  /* KeyMatrix_1_4=Right */
#define KBD_KEY_SELECT      0x11  /* KeyMatrix_2_1=Enter */

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

void kbd_init();
uint8_t kbd_getkey();

#endif//KBD_H

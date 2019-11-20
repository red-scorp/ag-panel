/*!
  \file version.h
  \brief AG-Panel Project version header
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef VERSION_H
#define VERSION_H

/* Version Configuration */
#define VER_MAJOR           "0"
#define VER_MINOR           "2"
#define VER_STATUS          "\xE0" // alpha
//#define VER_STATUS          "\xE2" // beta

/* FirmWare Configuration */
#define FW_NAME             "AG-Panel" /* Arduino Graphic Panel for lcdproc */
#if defined(VER_STATUS)
#define FW_VERSION          VER_MAJOR "." VER_MINOR VER_STATUS
#else
#define FW_VERSION          VER_MAJOR "." VER_MINOR
#endif

#endif//VERSION_H

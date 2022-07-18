/*! \file version.h
    \brief AG-Panel Project version header
    \copyright (C) 2019-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

/* Version Configuration */
#define VER_MAJOR           "0"
#define VER_MINOR           "2"
#define VER_STATUS          "a" // alpha
//#define VER_STATUS          "b" // beta

/* FirmWare Configuration */
#define FW_NAME             "AG-Panel" /* Arduino Graphic Panel for lcdproc */

#if defined(VER_STATUS)
    #define FW_VERSION          VER_MAJOR "." VER_MINOR VER_STATUS
#else
    #define FW_VERSION          VER_MAJOR "." VER_MINOR
#endif

/*!
  \file version.h
  \brief ALoS-Panel Project version header
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef VERSION_H
#define VERSION_H

/* Version Configuration */
#define VER_MAJOR           "0"
#define VER_MINOR           "1"
#define VER_STATUS          "alpha"

/* FirmWare Configuration */
#define FW_NAME             "ALoS" /* Arduino LCD over Serial Panel */
#if defined(VER_STATUS)
#define FW_VERSION          VER_MAJOR "." VER_MINOR "-" VER_STATUS
#else
#define FW_VERSION          VER_MAJOR "." VER_MINOR
#endif

#endif//VERSION_H

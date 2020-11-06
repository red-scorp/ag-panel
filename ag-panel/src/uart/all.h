/*!
  \file all.h
  \brief AG-Panel Project all UART includes
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "AbstractUART.h"

#include "HardwareUART.h"
#include "SoftwareUART.h"
#include "NoneUART.h"
#include "BufferedUART.h"
#include "TextLoggingUART.h"
#include "USBVirtualUART.h"

extern AbstractUART *initUART();

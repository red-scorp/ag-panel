/*!
  \file all.h
  \brief AG-Panel Project all UART includes
  \copyright (C) 2019-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "AbstractUART.h"

#include "NoneUART.h"

#ifndef UNIT_TEST

#include "HardwareUART.h"
#include "SoftwareUART.h"
#include "BufferedUART.h"
#include "TextLoggingUART.h"
#include "USBVirtualUART.h"

#endif/*UNIT_TEST*/

extern AbstractUART *initUART();

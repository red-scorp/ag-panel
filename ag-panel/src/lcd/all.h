/*!
  \file all.h
  \brief AG-Panel Project all LCD includes
  \copyright (C) 2019-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "backlight/all.h"
#include "font/all.h"

#include "AbstractLCD.h"
#include "AbstractTextLCD.h"

#ifndef UNIT_TEST

#include "PPITextLCD.h"
#include "I2CPCF8574TextLCD.h"
#include "I2CRGBTextLCD.h"
#include "I2CAIP31068TextLCD.h"
#include "SPIAIP31068TextLCD.h"

#include "AbstractGraphicLCD.h"
#include "AbstractU8GraphicLCD.h"

#endif/*UNIT_TEST*/

extern AbstractLCD *initLCD(AbstractBacklight *Backlight, AbstractFont *Font);

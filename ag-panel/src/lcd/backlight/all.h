/** @file all.h
    @brief AG-Panel Project all LCD backlight includes
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "AbstractBacklight.h"

#ifndef UNIT_TEST

#include "NoneBacklight.h"
#include "BinaryBacklight.h"
#include "PWMBacklight.h"
#include "RGBPWMBacklight.h"
#include "RGBBinaryBacklight.h"
#include "I2CRGBPWMBacklight.h"

#endif/*UNIT_TEST*/

extern AbstractBacklight *initBacklight();

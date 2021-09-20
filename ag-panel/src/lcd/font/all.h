/*!
  \file all.h
  \brief AG-Panel Project all fonts includes
  \copyright (C) 2020-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "AbstractFont.h"
#include "AbstractFixedFont.h"

#ifndef UNIT_TEST

#include "Fixed8x8TestFont.h"

#endif/*UNIT_TEST*/

extern AbstractFont *initFont();

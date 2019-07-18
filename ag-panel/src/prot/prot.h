/*!
  \file prot.h
  \brief AG-Panel Project protocol interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef PROT_H
#define PROT_H

#include "../../config.h"

/* Protocol functions */
void prot_init();
void prot_loop();
void prot_yield();

#endif//PROT_H

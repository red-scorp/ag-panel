/*!
  \file prot.cpp
  \brief AG-Panel Project protocol code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "prot.h"

#include "AbstractProtocol.h"

/* Protocol Configuration sanity check */
#if (!defined(PROT_LOSPANEL) && !defined(PROT_RAWSERIAL)) \
  || (defined(PROT_LOSPANEL) && defined(PROT_RAWSERIAL))
#error You should define PROT_LOSPANEL or PROT_RAWSERIAL and only one of them!
#endif

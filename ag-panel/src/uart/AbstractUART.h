/*!
  \file AbstractUART.h
  \brief AG-Panel Project abstract UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"

const auto DefaultBaudRate = 9600;

class AbstractUART {

public:
	AbstractUART(uint32_t BaudRate = DefaultBaudRate): m_BaudRate(BaudRate) { Init(); }
	virtual ~AbstractUART() { Exit(); }

	virtual uint8_t PutCh(uint8_t txbyte) = 0;
	virtual uint8_t GetCh() = 0;
	virtual void Prefill() {}

protected:
	uint32_t m_BaudRate;

	virtual bool Init() { return true; }
	virtual void Exit() {}
};

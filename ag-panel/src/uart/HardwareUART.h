/*!
  \file HardwareUART.h
  \brief AG-Panel Project direct hardware UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractUART.h"

//const auto DefaultBaudRate = 9600;

class HardwareUART: public AbstractUART {

public:
	HardwareUART(uint32_t BaudRate = DefaultBaudRate): AbstractUART(BaudRate) {}
//	virtual ~HardwareUART() {}

	virtual uint8_t PutCh(uint8_t txbyte) override;
	virtual uint8_t GetCh() override;

private:
	virtual bool Init() override;
	virtual void Exit() override;
};

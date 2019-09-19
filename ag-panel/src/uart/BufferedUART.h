/*!
  \file BufferedUART.h
  \brief AG-Panel Project direct hardware UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractUART.h"

const auto DefaultBufferSize = 512;

class BufferedUART: public AbstractUART {

public:
	BufferedUART(AbstractUART *UART, uint32_t BufferSize = DefaultBufferSize): AbstractUART(), m_BufferSize(BufferSize), m_UART(UART), m_Buffer(nullptr), m_BufferFilled(0) {}
//	virtual ~BufferedUART() {}

	virtual uint8_t PutCh(uint8_t txbyte) override;
	virtual uint8_t GetCh() override;
	virtual void Prefill() override;
	virtual uint32_t Available() override;

private:
	uint32_t m_BufferSize;
	AbstractUART *m_UART;
	uint8_t *m_Buffer;
	uint32_t m_BufferFilled;

	virtual bool Init() override;
	virtual void Exit() override;
	uint8_t PushBuffer();
	uint8_t FillBuffer();
};

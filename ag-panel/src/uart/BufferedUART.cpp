/*!
  \file BufferedUART.cpp
  \brief AG-Panel Project direct hardware UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "BufferedUART.h"

bool BufferedUART::Init() {
	m_Buffer = new uint8_t[m_BufferSize];
	return (m_Buffer == nullptr)? false: true;
}

void BufferedUART::Exit() {
	if(m_UART != nullptr)
		delete m_UART;
}

uint8_t BufferedUART::PutCh(uint8_t txbyte) {
	return m_UART->PutCh(txbyte);
}

uint8_t BufferedUART::GetCh() {
	while(FillBuffer() == 0) {
		yield();
	}

	return PushBuffer();
}

void BufferedUART::Prefill() {
	FillBuffer();
}

uint8_t BufferedUART::PushBuffer() {
	uint8_t top_byte = m_Buffer[0];

	for(uint32_t i = 1; i < m_BufferFilled; i++) {
		m_Buffer[i - 1] = m_Buffer[i];
	}

	m_BufferFilled--;
	return top_byte;
}

uint8_t BufferedUART::FillBuffer() {
	while(m_BufferFilled < m_BufferSize && m_UART->Available()) {
		uint8_t rxbyte = m_UART->GetCh();
		m_Buffer[m_BufferFilled++] = rxbyte;
	}

	return m_BufferFilled;
}

uint32_t BufferedUART::Available() {
	return m_BufferFilled;
}

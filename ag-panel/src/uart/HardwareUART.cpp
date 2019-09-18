/*!
  \file HardwareUART.cpp
  \brief AG-Panel Project direct hardware UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "HardwareUART.h"
#include <HardwareSerial.h>

bool HardwareUART::Init() {
	Serial.begin(m_BaudRate);
	return true;
}

void HardwareUART::Exit() {
}

uint8_t HardwareUART::PutCh(uint8_t txbyte) {
	return Serial.write(txbyte);
}

uint8_t HardwareUART::GetCh() {
	while(Serial.available() == 0) {
		yield();
	}

	return Serial.read();
}

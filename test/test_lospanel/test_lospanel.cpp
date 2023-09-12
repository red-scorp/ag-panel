/** @file test_lospanel.cpp
    @brief AG-Panel Project unit test los-panel protocol code
    @copyright (C) 2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Trick to include unit test headers during build and have syntax highlighting in editor */
#if defined(UNIT_TEST)
#include "unity.h"
#else
#include "../unity/unity.h"
#endif /* UNIT_TEST */

#include "../ag-panel/src/debug.h"
#include "../ag-panel/src/uart/all.h"
#include "../ag-panel/src/lcd/backlight/all.h"
#include "../ag-panel/src/lcd/font/all.h"
#include "../ag-panel/src/lcd/all.h"
#include "../ag-panel/src/keyboard/all.h"
#include "../ag-panel/src/protocol/all.h"

#define MOCK_FUNCTION   
#define MOCK_VARIABLE   static

using namespace std;


MOCK_VARIABLE int i_MockBacklight_SetOn_called = 0;
MOCK_VARIABLE int i_MockBacklight_SetBrightness_called = 0;
MOCK_VARIABLE int i_MockBacklight_SetRGB_called = 0;
class MockBacklight: public AbstractBacklight {
public:
    MockBacklight(): AbstractBacklight() { }
    virtual ~MockBacklight() { }
    virtual void SetOn(bool on) override { i_MockBacklight_SetOn_called++; }
    virtual void SetBrightness(uint8_t brightness) override { i_MockBacklight_SetBrightness_called++; }
    virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override { i_MockBacklight_SetRGB_called++; }
};
MOCK_VARIABLE int i_MockTextLCD_Clear_called = 0;
MOCK_VARIABLE int i_MockTextLCD_SetCursor_called = 0;
MOCK_VARIABLE int i_MockTextLCD_Print_str_called = 0;
MOCK_VARIABLE int i_MockTextLCD_Print_ch_called = 0;
MOCK_VARIABLE int i_MockTextLCD_Write_called = 0;
MOCK_VARIABLE int i_MockTextLCD_Command_called = 0;
class MockTextLCD: public AbstractTextLCD {
public:
    MockTextLCD(AbstractBacklight *Backlight): AbstractTextLCD(Backlight, 20, 2) { }
    virtual ~MockTextLCD() { }
    virtual void Clear() override { i_MockTextLCD_Clear_called++; }
    virtual void SetCursor(uint8_t x, uint8_t y) override { i_MockTextLCD_SetCursor_called++; }
    virtual void Print(const char *str) override { i_MockTextLCD_Print_str_called++; }
    virtual void Print(char ch) override { i_MockTextLCD_Print_ch_called++; }
    virtual void Write(uint8_t byte) override { i_MockTextLCD_Write_called++; }
    virtual void Command(uint8_t byte) override { i_MockTextLCD_Command_called++; }
};
MOCK_VARIABLE int i_MockUART_GetBaudRate_called = 0;
class MockUART: public AbstractUART {
public:
    MockUART(): AbstractUART() { }
    virtual ~MockUART() { }
    virtual uint8_t PutCh(uint8_t txbyte) override { return 0; }
    virtual uint8_t GetCh() override { return 0; }
    virtual uint32_t GetBaudRate() const override { i_MockUART_GetBaudRate_called++; return AbstractUART::GetBaudRate(); }
};
MOCK_VARIABLE int i_MockKeyboard_GetKey_called = 0;
MOCK_VARIABLE int i_MockKeyboard_GetKeyCount_called = 0;
class MockKeyboard: public AbstractKeyboard {
public:
    MockKeyboard(): AbstractKeyboard() { }
    virtual ~MockKeyboard() { }
    virtual uint8_t GetKey() override { i_MockKeyboard_GetKey_called++; return 0; }
    virtual uint8_t GetKeyCount() override { i_MockKeyboard_GetKeyCount_called++; return 0; }
};
MOCK_VARIABLE int i_micros_called = 0;
MOCK_FUNCTION unsigned long micros() { i_micros_called++; return 0; }

#undef DEBUG_STR
#define DEBUG_STR(str) printf("%s", str)

#include "../ag-panel/src/protocol/LoSPanelProtocol.cpp"

/* Call before each unit test case */
void setUp(void) {

    i_MockBacklight_SetOn_called = 0;
    i_MockBacklight_SetBrightness_called = 0;
    i_MockBacklight_SetRGB_called = 0;
    i_MockTextLCD_Clear_called = 0;
    i_MockTextLCD_SetCursor_called = 0;
    i_MockTextLCD_Print_str_called = 0;
    i_MockTextLCD_Print_ch_called = 0;
    i_MockTextLCD_Write_called = 0;
    i_MockTextLCD_Command_called = 0;
    i_MockUART_GetBaudRate_called = 0;
    i_MockKeyboard_GetKey_called = 0;
    i_MockKeyboard_GetKeyCount_called = 0;
    i_micros_called = 0;
}

/* Call after each unit test case */
void tearDown(void) {
}

void test_lospanel_protocol_does_right_initialization(void) {

    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    // TODO: test initialization of LoSPanelProtocol class

    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}


/* Unit testing main function */
int main(int argc, char *argv[]) {

    UNITY_BEGIN();

    /* Calling unit test functions */
    RUN_TEST(test_lospanel_protocol_does_right_initialization);

    UNITY_END();
}

/** @file test_lospanel.cpp
    @brief AG-Panel Project unit test los-panel protocol code
    @copyright (C) 2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

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

#define MOCK_UART_TXBUF_SIZE        512
#define MOCK_UART_RXBUF_SIZE        512
#define MOCK_LCD_WIDTH              20
#define MOCK_LCD_HEIGHT             2
#define MOCK_LCD_WRITE_BUF_SIZE     128
#define MOCK_LCD_COMMAND_BUF_SIZE   128

using namespace std;

/* Mocks for testing LoSPanelProtocol class */
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
MOCK_VARIABLE uint8_t c_MockTextLCD_WriteBuffer[MOCK_LCD_WRITE_BUF_SIZE] = { 0 };
MOCK_VARIABLE int i_MockTextLCD_WriteBufferPos = 0;
MOCK_VARIABLE uint8_t c_MockTextLCD_CommandBuffer[MOCK_LCD_COMMAND_BUF_SIZE] = { 0 };
MOCK_VARIABLE int i_MockTextLCD_CommandBufferPos = 0;
class MockTextLCD: public AbstractTextLCD {
public:
    MockTextLCD(AbstractBacklight *Backlight): AbstractTextLCD(Backlight, MOCK_LCD_WIDTH, MOCK_LCD_HEIGHT) { }
    virtual ~MockTextLCD() { }
    virtual void Clear() override { i_MockTextLCD_Clear_called++; }
    virtual void SetCursor(uint8_t x, uint8_t y) override { i_MockTextLCD_SetCursor_called++; }
    virtual void Print(const char *str) override { i_MockTextLCD_Print_str_called++; }
    virtual void Print(char ch) override { i_MockTextLCD_Print_ch_called++; }
    virtual void Write(uint8_t byte) override {
        i_MockTextLCD_Write_called++;
        if(i_MockTextLCD_WriteBufferPos < MOCK_LCD_WRITE_BUF_SIZE)
            c_MockTextLCD_WriteBuffer[i_MockTextLCD_WriteBufferPos++] = byte;
     }
    virtual void Command(uint8_t byte) override {
        i_MockTextLCD_Command_called++;
        if(i_MockTextLCD_CommandBufferPos < MOCK_LCD_COMMAND_BUF_SIZE)
            c_MockTextLCD_CommandBuffer[i_MockTextLCD_CommandBufferPos++] = byte;
    }
};
MOCK_VARIABLE int i_MockUART_GetBaudRate_called = 0;
MOCK_VARIABLE int i_MockUART_PutCh_called = 0;
MOCK_VARIABLE int i_MockUART_GetCh_called = 0;
MOCK_VARIABLE int i_MockUART_Available_called = 0;
MOCK_VARIABLE uint8_t c_MockUART_TxBuffer[MOCK_UART_TXBUF_SIZE] = { 0 };
MOCK_VARIABLE int i_MockUART_TxBufferPos = 0;
MOCK_VARIABLE uint8_t c_MockUART_RxBuffer[MOCK_UART_RXBUF_SIZE] = { 0 };
MOCK_VARIABLE int i_MockUART_RxBufferPos = 0;
MOCK_VARIABLE int i_MockUART_RxBufferMax = 0;
class MockUART: public AbstractUART {
public:
    MockUART(): AbstractUART() { }
    virtual ~MockUART() { }
    virtual uint8_t PutCh(uint8_t TxByte) override {
        i_MockUART_PutCh_called++;
        if(i_MockUART_TxBufferPos < MOCK_UART_TXBUF_SIZE)
            c_MockUART_TxBuffer[i_MockUART_TxBufferPos++] = TxByte;
        return 0;
    }
    virtual uint8_t GetCh() override {
        i_MockUART_GetCh_called++;
        if(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax && i_MockUART_RxBufferPos < MOCK_UART_RXBUF_SIZE)
            return c_MockUART_RxBuffer[i_MockUART_RxBufferPos++];
        return 0;
    }
    virtual uint32_t GetBaudRate() const override { i_MockUART_GetBaudRate_called++; return AbstractUART::GetBaudRate(); }
    virtual uint32_t Available() override {
        i_MockUART_Available_called++;
        return i_MockUART_RxBufferMax - i_MockUART_RxBufferPos;
    }
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
MOCK_FUNCTION unsigned long micros() {
    i_micros_called++;
    struct timeval ts;
    gettimeofday(&ts, NULL);
    return ts.tv_sec * 1000000 + ts.tv_usec;
}

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
    memset(c_MockTextLCD_WriteBuffer, 0, sizeof(c_MockTextLCD_WriteBuffer));
    i_MockTextLCD_WriteBufferPos = 0;
    memset(c_MockTextLCD_CommandBuffer, 0, sizeof(c_MockTextLCD_CommandBuffer));
    i_MockTextLCD_CommandBufferPos = 0;
    i_MockUART_GetBaudRate_called = 0;
    i_MockUART_PutCh_called = 0;
    i_MockUART_GetCh_called = 0;
    i_MockUART_Available_called = 0;
    memset(c_MockUART_TxBuffer, 0, sizeof(c_MockUART_TxBuffer));
    i_MockUART_TxBufferPos = 0;
    memset(c_MockUART_RxBuffer, 0, sizeof(c_MockUART_RxBuffer));
    i_MockUART_RxBufferPos = 0;
    i_MockUART_RxBufferMax = 0;
    i_MockKeyboard_GetKey_called = 0;
    i_MockKeyboard_GetKeyCount_called = 0;
    i_micros_called = 0;
}

/* Call after each unit test case */
void tearDown(void) {
}

/* Unit test function to check if initialization of mocks for LoSPanelProtocol class works correctly */
void test_lospanel_protocol_does_right_initialization(void) {

    AbstractUART *p_UART = new MockUART();
    TEST_ASSERT_NOT_NULL(p_UART);

    AbstractBacklight *p_Backlight = new MockBacklight();
    TEST_ASSERT_NOT_NULL(p_Backlight);

    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    TEST_ASSERT_NOT_NULL(p_TextLCD);

    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    TEST_ASSERT_NOT_NULL(p_Keyboard);

    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);
    TEST_ASSERT_NOT_NULL(p_Protocol);

    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit test function to check if LoSPanelProtocol class read data from UART and sends it to LCD */
void test_lospanel_protocol_reads_uart_and_prints_on_lcd(void) {

    uint8_t c_UARTInputData[] = { 'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5' };
    uint8_t c_LCDOutputData[] = { 'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5' };

    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    memcpy(c_MockUART_RxBuffer, c_UARTInputData, sizeof(c_UARTInputData));
    i_MockUART_RxBufferPos = 0;
    i_MockUART_RxBufferMax = sizeof(c_UARTInputData);

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Checking if the function under test called right functions */
    TEST_ASSERT_EQUAL_INT(sizeof(c_UARTInputData), i_MockUART_GetCh_called);
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockTextLCD_Write_called);
    TEST_ASSERT_EQUAL_INT(0, i_MockTextLCD_Command_called);

    /* Checking if the function under test does right output */
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockTextLCD_WriteBufferPos);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_LCDOutputData, c_MockTextLCD_WriteBuffer, sizeof(c_LCDOutputData)));

    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit test function to check if LoSPanelProtocol class read data from UART and sends it to LCD with commands */
void test_lospanel_protocol_reads_uart_and_prints_on_lcd_with_commands(void) {

    uint8_t c_UARTInputData[] = { 'A', 'B', 0xFE, 0x01, 'C', 'D', 0xFE, 0x02, 'E', 'F', 0xFE, 0x03 };
    uint8_t c_LCDOutputData[] = { 'A', 'B', 'C', 'D', 'E', 'F'};
    uint8_t c_LCDCommandData[] = { 0x01, 0x02, 0x03 };

    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    memcpy(c_MockUART_RxBuffer, c_UARTInputData, sizeof(c_UARTInputData));
    i_MockUART_RxBufferPos = 0;
    i_MockUART_RxBufferMax = sizeof(c_UARTInputData);

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Checking if the function under test called right functions */
    TEST_ASSERT_EQUAL_INT(sizeof(c_UARTInputData), i_MockUART_GetCh_called);
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockTextLCD_Write_called);
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDCommandData), i_MockTextLCD_Command_called);

    /* Checking if the function under test does right output */
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockTextLCD_WriteBufferPos);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_LCDOutputData, c_MockTextLCD_WriteBuffer, sizeof(c_LCDOutputData)));
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDCommandData), i_MockTextLCD_CommandBufferPos);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_LCDCommandData, c_MockTextLCD_CommandBuffer, sizeof(c_LCDCommandData)));

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
    RUN_TEST(test_lospanel_protocol_reads_uart_and_prints_on_lcd);
    RUN_TEST(test_lospanel_protocol_reads_uart_and_prints_on_lcd_with_commands);

    UNITY_END();
}

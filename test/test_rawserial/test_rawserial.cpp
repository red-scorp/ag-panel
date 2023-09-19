/** @file test_rawserial.cpp
    @brief AG-Panel Project unit test rawserial protocol code
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

using namespace std;

#pragma region Mocks for unit tests

#define MOCK_FUNCTION   
#define MOCK_VARIABLE   static

#define MOCK_UART_TXBUF_SIZE        512
#define MOCK_UART_RXBUF_SIZE        512
#define MOCK_LCD_WIDTH              20
#define MOCK_LCD_HEIGHT             2
#define MOCK_LCD_PRINT_BUF_SIZE     (MOCK_LCD_HEIGHT * MOCK_LCD_WIDTH * 2)

/* Mocks for testing RawSerialProtocol class */
MOCK_VARIABLE int i_MockBacklight_SetOn_called = 0;
MOCK_VARIABLE int i_MockBacklight_SetBrightness_called = 0;
MOCK_VARIABLE int i_MockBacklight_SetRGB_called = 0;
MOCK_VARIABLE uint8_t c_MockBacklight_Brightness = 0;
class MockBacklight: public AbstractBacklight {
public:
    MockBacklight(): AbstractBacklight() { }
    virtual ~MockBacklight() { }
    virtual void SetOn(bool on) override { i_MockBacklight_SetOn_called++; }
    virtual void SetBrightness(uint8_t brightness) override { i_MockBacklight_SetBrightness_called++; c_MockBacklight_Brightness = brightness; }
    virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override { i_MockBacklight_SetRGB_called++; }
};
MOCK_VARIABLE int i_MockLCD_Clear_called = 0;
MOCK_VARIABLE int i_MockLCD_SetCursor_called = 0;
MOCK_VARIABLE uint8_t c_MockLCD_SetCursor_called_with_x = 0;
MOCK_VARIABLE uint8_t c_MockLCD_SetCursor_called_with_y = 0;
MOCK_VARIABLE int i_MockLCD_Print_str_called = 0;
MOCK_VARIABLE int i_MockLCD_Print_ch_called = 0;
MOCK_VARIABLE uint8_t c_MockLCD_PrintBuffer[MOCK_LCD_PRINT_BUF_SIZE] = { 0 };
MOCK_VARIABLE int i_MockLCD_PrintBufferPos = 0;
class MockLCD: public AbstractLCD {
public:
    MockLCD(AbstractBacklight *Backlight): AbstractLCD(Backlight, MOCK_LCD_WIDTH, MOCK_LCD_HEIGHT) { }
    virtual ~MockLCD() { }
    virtual void Clear() override { i_MockLCD_Clear_called++; }
    virtual void SetCursor(uint8_t x, uint8_t y) override {
        i_MockLCD_SetCursor_called++;
        c_MockLCD_SetCursor_called_with_x = x;
        c_MockLCD_SetCursor_called_with_y = y;
    }
    virtual void Print(const char *str) override {
        i_MockLCD_Print_str_called++;
        while(*str != '\0' && i_MockLCD_PrintBufferPos < MOCK_LCD_PRINT_BUF_SIZE)
            c_MockLCD_PrintBuffer[i_MockLCD_PrintBufferPos++] = *str++;
    }
    virtual void Print(char ch) override {
        i_MockLCD_Print_ch_called++;
        if(i_MockLCD_PrintBufferPos < MOCK_LCD_PRINT_BUF_SIZE)
            c_MockLCD_PrintBuffer[i_MockLCD_PrintBufferPos++] = ch;
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
#define MOCKUART_FILL_RXBUFFER_SIZED(data, size) \
    memcpy(c_MockUART_RxBuffer, data, size); \
    i_MockUART_RxBufferPos = 0; \
    i_MockUART_RxBufferMax = size;
#define MOCKUART_FILL_RXBUFFER(data) \
    MOCKUART_FILL_RXBUFFER_SIZED(data, sizeof(data))
MOCK_VARIABLE int i_MockKeyboard_GetKey_called = 0;
MOCK_VARIABLE int i_MockKeyboard_GetKeyCount_called = 0;
MOCK_VARIABLE uint8_t c_MockKeyboard_GetKey_return = 0;
class MockKeyboard: public AbstractKeyboard {
public:
    MockKeyboard(): AbstractKeyboard() { }
    virtual ~MockKeyboard() { }
    virtual uint8_t GetKey() override { i_MockKeyboard_GetKey_called++; return c_MockKeyboard_GetKey_return; }
    virtual uint8_t GetKeyCount() override { i_MockKeyboard_GetKeyCount_called++; return 5; }
};
MOCK_VARIABLE int i_micros_called = 0;
unsigned long real_micros() {
    struct timeval ts;
    gettimeofday(&ts, NULL);
    uint32_t result = (uint32_t)(ts.tv_sec * 1000000 + ts.tv_usec);
    // printf("real_micros: %u:%u -> %u\n", ts.tv_sec, ts.tv_usec, result);
    return result;
}
MOCK_FUNCTION unsigned long micros() { i_micros_called++; return real_micros(); }

#undef DEBUG_STR
#define DEBUG_STR(str) printf("%s", str)

#pragma endregion

#include "../ag-panel/src/protocol/RawSerialProtocol.cpp"

/* Call before each unit test case */
void setUp(void) {

    i_MockBacklight_SetOn_called = 0;
    i_MockBacklight_SetBrightness_called = 0;
    i_MockBacklight_SetRGB_called = 0;
    c_MockBacklight_Brightness = 0;
    i_MockLCD_Clear_called = 0;
    i_MockLCD_SetCursor_called = 0;
    c_MockLCD_SetCursor_called_with_x = 0;
    c_MockLCD_SetCursor_called_with_y = 0;
    i_MockLCD_Print_str_called = 0;
    i_MockLCD_Print_ch_called = 0;
    memset(c_MockLCD_PrintBuffer, 0, sizeof(c_MockLCD_PrintBuffer));
    i_MockLCD_PrintBufferPos = 0;
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
    c_MockKeyboard_GetKey_return = 0;
    i_micros_called = 0;
}

/* Call after each unit test case */
void tearDown(void) {
}

/* Unit test function to check if initialization of mocks for RawSerialProtocol class works correctly */
void test_rawserial_protocol_does_right_initialization(void) {

    /* Creating objects to initialize RawSerialProtocol class */
    AbstractUART *p_UART = new MockUART();
    TEST_ASSERT_NOT_NULL(p_UART);

    AbstractBacklight *p_Backlight = new MockBacklight();
    TEST_ASSERT_NOT_NULL(p_Backlight);

    AbstractLCD *p_LCD = new MockLCD(p_Backlight);
    TEST_ASSERT_NOT_NULL(p_LCD);

    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    TEST_ASSERT_NOT_NULL(p_Keyboard);

    AbstractProtocol *p_Protocol = new RawSerialProtocol(p_UART, p_LCD, p_Keyboard);
    TEST_ASSERT_NOT_NULL(p_Protocol);

    /* Removing objects after use */
    delete p_Protocol;
    delete p_Keyboard;
    delete p_LCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit test function to check if RawSerialProtocol class reads UART and prints on LCD */
void test_rawserial_protocol_reads_uart_and_prints_on_lcd(void) {

    /* Definition of input and expected output data */
    uint8_t c_UARTInputData[] = "Hello World!";
    uint8_t c_LCDOutputData[] = "Hello World!";

    /* Creating objects to initialize RawSerialProtocol class */
    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractLCD *p_LCD = new MockLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new RawSerialProtocol(p_UART, p_LCD, p_Keyboard);

    /* Checking if during initialization to ->Clear() and ->SetCursor() for LCD was performed */
    TEST_ASSERT_EQUAL_INT(0, i_MockLCD_Clear_called);
    TEST_ASSERT_EQUAL_INT(0, i_MockLCD_SetCursor_called);

    /* Setting up text input data */
    MOCKUART_FILL_RXBUFFER(c_UARTInputData);

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Checking if the function under test called right functions */
    TEST_ASSERT_EQUAL_INT(sizeof(c_UARTInputData), i_MockUART_GetCh_called);
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockLCD_Print_ch_called);
    TEST_ASSERT_EQUAL_INT(1, i_MockLCD_Clear_called);
    TEST_ASSERT_EQUAL_INT(1, i_MockLCD_SetCursor_called);
    TEST_ASSERT_EQUAL(0, c_MockLCD_SetCursor_called_with_x);
    TEST_ASSERT_EQUAL(0, c_MockLCD_SetCursor_called_with_y);

    /* Checking if the function under test does right output */
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockLCD_PrintBufferPos);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_LCDOutputData, c_MockLCD_PrintBuffer, sizeof(c_LCDOutputData)));

    /* Removing objects after use */
    delete p_Protocol;
    delete p_Keyboard;
    delete p_LCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit testing main function */
int main(int argc, char *argv[]) {

    UNITY_BEGIN();

    /* Calling unit test functions */
    RUN_TEST(test_rawserial_protocol_does_right_initialization);
    RUN_TEST(test_rawserial_protocol_reads_uart_and_prints_on_lcd);

    UNITY_END();
}

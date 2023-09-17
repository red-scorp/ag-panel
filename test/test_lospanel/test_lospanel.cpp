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

using namespace std;

#pragma region Mocks for unit tests

#define MOCK_FUNCTION   
#define MOCK_VARIABLE   static

#define MOCK_UART_TXBUF_SIZE        512
#define MOCK_UART_RXBUF_SIZE        512
#define MOCK_LCD_WIDTH              20
#define MOCK_LCD_HEIGHT             2
#define MOCK_LCD_WRITE_BUF_SIZE     128
#define MOCK_LCD_COMMAND_BUF_SIZE   128

/* Mocks for testing LoSPanelProtocol class */
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
    // result = result % 10000;
    // printf("real_micros: %u:%u -> %u\n", ts.tv_sec, ts.tv_usec, result);
    return result;
}
MOCK_FUNCTION unsigned long micros() { i_micros_called++; return real_micros(); }

#undef DEBUG_STR
#define DEBUG_STR(str) printf("%s", str)

#pragma endregion

#include "../ag-panel/src/protocol/LoSPanelProtocol.cpp"

/* Call before each unit test case */
void setUp(void) {

    i_MockBacklight_SetOn_called = 0;
    i_MockBacklight_SetBrightness_called = 0;
    i_MockBacklight_SetRGB_called = 0;
    c_MockBacklight_Brightness = 0;
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
    c_MockKeyboard_GetKey_return = 0;
    i_micros_called = 0;
}

/* Call after each unit test case */
void tearDown(void) {
}

/* Unit test function to check if initialization of mocks for LoSPanelProtocol class works correctly */
void test_lospanel_protocol_does_right_initialization(void) {

    /* Creating objects to initialize LosPanelProtocol class */
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

    /* Removing objects after use */
    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit test function to check if LoSPanelProtocol class read data from UART and sends it to LCD */
void test_lospanel_protocol_reads_uart_and_prints_on_lcd(void) {

    /* Definition of input and expected output data */
    uint8_t c_UARTInputData[] = { 'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5' };
    uint8_t c_LCDOutputData[] = { 'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5' };

    /* Creating objects to initialize LosPanelProtocol class */
    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    /* Setting up text input data */
    MOCKUART_FILL_RXBUFFER(c_UARTInputData);

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

    /* Removing objects after use */
    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit test function to check if LoSPanelProtocol class read data from UART and sends it to LCD with commands */
void test_lospanel_protocol_reads_uart_and_prints_on_lcd_with_commands(void) {

    /* Definition of input and expected output data */
    uint8_t c_UARTInputData[] = { 'A', 'B', 0xFE, 0x01, 'C', 'D', 0xFE, 0x02, 'E', 'F', 0xFE, 0x03 };
    uint8_t c_LCDOutputData[] = { 'A', 'B', 'C', 'D', 'E', 'F'};
    uint8_t c_LCDCommandData[] = { 0x01, 0x02, 0x03 };

    /* Creating objects to initialize LosPanelProtocol class */
    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    /* Setting up text and command input data */
    MOCKUART_FILL_RXBUFFER(c_UARTInputData);

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

    /* Removing objects after use */
    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit test function to check if LoSPanelProtocol class read data from UART and controls backlight */
void test_lospanel_protocol_reads_uart_and_controls_backlight(void) {

    /* Definition of input and expected output data */
    uint8_t c_UARTInputDataMax[] = { 'A', 0xFD, 0xFF, 0xFE, 0x01, 'B' };
    uint8_t c_UARTInputDataOff[] = { 'C', 0xFD, 0x00, 0xFE, 0x02, 'D' };
    uint8_t c_UARTInputDataHalf[] = { 'E', 0xFD, 0x7F, 0xFE, 0x03, 'F' };
    uint8_t c_LCDOutputData[] = { 'A', 'B', 'C', 'D', 'E', 'F'};
    uint8_t c_LCDCommandData[] = { 0x01, 0x02, 0x03 };

    /* Creating objects to initialize LosPanelProtocol class */
    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    /* Setting up max backlight input data */
    MOCKUART_FILL_RXBUFFER(c_UARTInputDataMax);

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Check if backlight was set to max brightness */
    TEST_ASSERT_EQUAL_INT(1, i_MockBacklight_SetBrightness_called);
    TEST_ASSERT_EQUAL_INT(255, c_MockBacklight_Brightness);

    /* Setting up off backlight input data */
    MOCKUART_FILL_RXBUFFER(c_UARTInputDataOff);

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Check if backlight was set to off brightness */
    TEST_ASSERT_EQUAL_INT(2, i_MockBacklight_SetBrightness_called);
    TEST_ASSERT_EQUAL_INT(0, c_MockBacklight_Brightness);

    /* Setting up half backlight input data */
    MOCKUART_FILL_RXBUFFER(c_UARTInputDataHalf);

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Check if backlight was set to off brightness */
    TEST_ASSERT_EQUAL_INT(3, i_MockBacklight_SetBrightness_called);
    TEST_ASSERT_EQUAL_INT(127, c_MockBacklight_Brightness);

    /* Checking if the function under test called right functions */
    TEST_ASSERT_EQUAL_INT(sizeof(c_UARTInputDataMax) + sizeof(c_UARTInputDataOff) + sizeof(c_UARTInputDataHalf), i_MockUART_GetCh_called);
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockTextLCD_Write_called);
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDCommandData), i_MockTextLCD_Command_called);

    /* Checking if the function under test still able to process commands and text data */
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDOutputData), i_MockTextLCD_WriteBufferPos);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_LCDOutputData, c_MockTextLCD_WriteBuffer, sizeof(c_LCDOutputData)));
    TEST_ASSERT_EQUAL_INT(sizeof(c_LCDCommandData), i_MockTextLCD_CommandBufferPos);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_LCDCommandData, c_MockTextLCD_CommandBuffer, sizeof(c_LCDCommandData)));

    /* Removing objects after use */
    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}

/* Run single timing test for LoSPanelProtocol's LCD commands */
void run_timing_test_with_input_data(AbstractProtocol *p_Protocol, uint8_t *c_UARTInputData, uint32_t i_UARTInputDataSize, uint32_t i_expected_wait_time) {

    uint8_t c_UARTInputDataRefWait[] = { 0xFE, 0x04 };

    /* Setting up time measured input data */
    MOCKUART_FILL_RXBUFFER_SIZED(c_UARTInputData, i_UARTInputDataSize);

    uint32_t i_micros_start = real_micros();

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Setting up short input data */
    MOCKUART_FILL_RXBUFFER(c_UARTInputDataRefWait);

    /* Calling the function under test till it runs out of input data */
    while(i_MockUART_RxBufferPos < i_MockUART_RxBufferMax)
        p_Protocol->Loop();

    /* Check if the function under test waited 2 ms */
    uint32_t i_micros_end = real_micros();
    TEST_ASSERT_GREATER_OR_EQUAL_INT(1, i_micros_called);
    i_micros_called = 0;
    // printf("test start %u us, end %u us\n", i_micros_start, i_micros_end);
    // printf("waited %u us, expecting %u us\n", i_micros_end - i_micros_start, i_expected_wait_time);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(i_expected_wait_time, i_micros_end - i_micros_start);
}

/* Unit test function to check if LoSPanelProtocol class holds proper time between LCD transfers */
void test_lospanel_protocol_holds_proper_timing(void) {

    /* Definition of input and expected output data */
    /* Based on the timing spec https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller ,
       we need to wait 37 us after each byte transfer, except for commands 1 - 3, where we need to wait 1.52 ms.
       We also need to wait nothing after backlight command. */
    uint8_t c_UARTInputData2ms1[] = { 0xFE, 0x00 };     /* long command 0x00 */
    uint8_t c_UARTInputData2ms2[] = { 0xFE, 0x01 };     /* long command 0x01 */
    uint8_t c_UARTInputData2ms3[] = { 0xFE, 0x02 };     /* long command 0x02 */
    uint8_t c_UARTInputData2ms4[] = { 0xFE, 0x03 };     /* long command 0x03 */
    uint8_t c_UARTInputData40us1[] = { 0xFE, 0x04 };    /* short command 0x04 */
    uint8_t c_UARTInputData40us2[] = { 0xFE, 0x7F };    /* short command 0x7F */
    uint8_t c_UARTInputData40us3[] = { 0xFE, 0xFF };    /* short command 0xFF */
    uint8_t c_UARTInputData40us4[] = { 'A' };           /* short text data */
    uint8_t c_UARTInputData0us1[] = { 0xFD, 0x00 };     /* set backlight request is not timed and has no waiting delay */

    /* Creating objects to initialize LosPanelProtocol class */
    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    /* Calling the function under test with different input data */
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData2ms1, sizeof(c_UARTInputData2ms1), 1520);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData2ms2, sizeof(c_UARTInputData2ms2), 1520);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData2ms3, sizeof(c_UARTInputData2ms3), 1520);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData2ms4, sizeof(c_UARTInputData2ms4), 1520);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData40us1, sizeof(c_UARTInputData40us1), 37);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData40us2, sizeof(c_UARTInputData40us2), 37);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData40us3, sizeof(c_UARTInputData40us3), 37);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData40us4, sizeof(c_UARTInputData40us4), 37);
    run_timing_test_with_input_data(p_Protocol, c_UARTInputData0us1, sizeof(c_UARTInputData0us1), 0);

    /* Removing objects after use */
    delete p_Protocol;
    delete p_Keyboard;
    delete p_TextLCD;
    delete p_Backlight;
    delete p_UART;
}

/* Unit test function to check if LoSPanelProtocol class reads keys and sends them to UART */
void test_lospanel_protocol_reads_keys_and_sends_over_uart(void) {

    /* Definition of input and expected output data */
    uint8_t c_KeyboardIntputData1 = 0x01;
    uint8_t c_KeyboardIntputData2 = 0x04;
    uint8_t c_KeyboardIntputData3 = 0x17;
    uint8_t c_UARTOutputData1[] = { 0xFE, 0x02 };
    uint8_t c_UARTOutputData2[] = { 0xFE, 0x11 };
    uint8_t c_UARTOutputData3[] = { 0xFE, 0x58 };

    /* Creating objects to initialize LosPanelProtocol class */
    AbstractUART *p_UART = new MockUART();
    AbstractBacklight *p_Backlight = new MockBacklight();
    AbstractTextLCD *p_TextLCD = new MockTextLCD(p_Backlight);
    AbstractKeyboard *p_Keyboard = new MockKeyboard();
    AbstractProtocol *p_Protocol = new LoSPanelProtocol(p_UART, p_TextLCD, p_Keyboard);

    /* Setting up keyboard input data */
    c_MockKeyboard_GetKey_return = c_KeyboardIntputData1;
    memset(c_MockUART_TxBuffer, 0, sizeof(c_MockUART_TxBuffer));
    i_MockUART_TxBufferPos = 0;

    /* Calling the function under test till it runs out of input data */
    while(i_MockKeyboard_GetKey_called < 1) {
        p_Protocol->Loop();
        p_Protocol->Yield();
    }

    /* Checking if the function under test called right functions */
    TEST_ASSERT_EQUAL_INT(1, i_MockKeyboard_GetKey_called);
    TEST_ASSERT_EQUAL_INT(2, i_MockUART_PutCh_called);

    /* Checking if the function under test does right output */
    TEST_ASSERT_EQUAL_INT(sizeof(c_UARTOutputData1), i_MockUART_TxBufferPos);
    // printf("c_MockUART_TxBuffer: %02X %02X\n", c_MockUART_TxBuffer[0], c_MockUART_TxBuffer[1]);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_UARTOutputData1, c_MockUART_TxBuffer, sizeof(c_UARTOutputData1)));

    /* Setting up keyboard input data */
    c_MockKeyboard_GetKey_return = c_KeyboardIntputData2;
    memset(c_MockUART_TxBuffer, 0, sizeof(c_MockUART_TxBuffer));
    i_MockUART_TxBufferPos = 0;

    /* Calling the function under test till it runs out of input data */
    while(i_MockKeyboard_GetKey_called < 2) {
        p_Protocol->Loop();
        p_Protocol->Yield();
    }

    /* Checking if the function under test called right functions */
    TEST_ASSERT_EQUAL_INT(2, i_MockKeyboard_GetKey_called);
    TEST_ASSERT_EQUAL_INT(4, i_MockUART_PutCh_called);

    /* Checking if the function under test does right output */
    TEST_ASSERT_EQUAL_INT(sizeof(c_UARTOutputData2), i_MockUART_TxBufferPos);
    // printf("c_MockUART_TxBuffer: %02X %02X\n", c_MockUART_TxBuffer[0], c_MockUART_TxBuffer[1]);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_UARTOutputData2, c_MockUART_TxBuffer, sizeof(c_UARTOutputData2)));

    /* Setting up keyboard input data */
    c_MockKeyboard_GetKey_return = c_KeyboardIntputData3;
    memset(c_MockUART_TxBuffer, 0, sizeof(c_MockUART_TxBuffer));
    i_MockUART_TxBufferPos = 0;

    /* Calling the function under test till it runs out of input data */
    while(i_MockKeyboard_GetKey_called < 3) {
        p_Protocol->Loop();
        p_Protocol->Yield();
    }

    /* Checking if the function under test called right functions */
    TEST_ASSERT_EQUAL_INT(3, i_MockKeyboard_GetKey_called);
    TEST_ASSERT_EQUAL_INT(6, i_MockUART_PutCh_called);

    /* Checking if the function under test does right output */
    TEST_ASSERT_EQUAL_INT(sizeof(c_UARTOutputData3), i_MockUART_TxBufferPos);
    // printf("c_MockUART_TxBuffer: %02X %02X\n", c_MockUART_TxBuffer[0], c_MockUART_TxBuffer[1]);
    TEST_ASSERT_EQUAL_INT(0, memcmp(c_UARTOutputData3, c_MockUART_TxBuffer, sizeof(c_UARTOutputData3)));

    /* Removing objects after use */
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
    RUN_TEST(test_lospanel_protocol_reads_uart_and_controls_backlight);
    RUN_TEST(test_lospanel_protocol_holds_proper_timing);
    RUN_TEST(test_lospanel_protocol_reads_keys_and_sends_over_uart);

    UNITY_END();
}

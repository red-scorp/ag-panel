/** @file test_main.cpp
    @brief AG-Panel Project unit test main code
    @copyright (C) 2021-2023 Andriy Golovnya
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

using namespace std;

#pragma region Mocks for unit tests

#define MOCK_FUNCTION   
#define MOCK_VARIABLE   static

/* Mocks for initDebug() function */
MOCK_VARIABLE int i_initDebug_called = 0;
MOCK_VARIABLE AbstractUART *p_initDebug_return = (AbstractUART*)(void*)&i_initDebug_called;
MOCK_FUNCTION AbstractUART *initDebug() {
    i_initDebug_called++;
    return p_initDebug_return;
}

/* Mocks for initUART() function */
MOCK_VARIABLE int i_initUART_called = 0;
MOCK_VARIABLE AbstractUART *p_initUART_return = (AbstractUART*)(void*)&i_initUART_called;
MOCK_FUNCTION AbstractUART *initUART() {
    i_initUART_called++;
    return p_initUART_return;
}

/* Mocks for initBacklight() function */
MOCK_VARIABLE int i_initBacklight_called = 0;
MOCK_VARIABLE AbstractBacklight *p_initBacklight_return = (AbstractBacklight*)(void*)&i_initBacklight_called;
MOCK_FUNCTION AbstractBacklight *initBacklight() {
    i_initBacklight_called++;
    return p_initBacklight_return;
}

/* Mocks for initFont() function */
MOCK_VARIABLE int i_initFont_called = 0;
MOCK_VARIABLE AbstractFont *p_initFont_return = (AbstractFont*)(void*)&i_initFont_called;
MOCK_FUNCTION AbstractFont *initFont() {
    i_initFont_called++;
    return p_initFont_return;
}

/* Mocks for initLCD() function */
MOCK_VARIABLE int i_initLCD_called = 0;
MOCK_VARIABLE AbstractLCD *p_initLCD_return = (AbstractLCD*)(void*)&i_initLCD_called;
MOCK_VARIABLE AbstractBacklight *p_initLCD_called_with_Backlight = nullptr;
MOCK_VARIABLE AbstractFont *p_initLCD_called_with_Font = nullptr;
MOCK_FUNCTION AbstractLCD *initLCD(AbstractBacklight *Backlight, AbstractFont *Font) {
    i_initLCD_called++;
    p_initLCD_called_with_Backlight = Backlight;
    p_initLCD_called_with_Font = Font;
    return p_initLCD_return;
}

/* Mocks for initKeyboard() function */
MOCK_VARIABLE int i_initKeyboard_called = 0;
MOCK_VARIABLE AbstractKeyboard *p_initKeyboard_return = (AbstractKeyboard*)(void*)&i_initKeyboard_called;
MOCK_VARIABLE AbstractLCD *p_initKeyboard_called_with_LCD = nullptr;
MOCK_FUNCTION AbstractKeyboard *initKeyboard(AbstractLCD *p_LCD) {
    i_initKeyboard_called++;
    p_initKeyboard_called_with_LCD = p_LCD;
    return p_initKeyboard_return;
}

/* Mocks for initProtocol() function */
MOCK_VARIABLE int i_initProtocol_called = 0;
MOCK_VARIABLE AbstractProtocol *p_initProtocol_return = (AbstractProtocol*)(void*)&i_initProtocol_called;
MOCK_VARIABLE AbstractUART *p_initProtocol_called_with_UART = nullptr;
MOCK_VARIABLE AbstractLCD *p_initProtocol_called_with_LCD = nullptr;
MOCK_VARIABLE AbstractKeyboard *p_initProtocol_called_with_Keyboard = nullptr;
MOCK_FUNCTION AbstractProtocol *initProtocol(AbstractUART *UART, AbstractLCD *LCD, AbstractKeyboard *Keyboard) {
    i_initProtocol_called++;
    p_initProtocol_called_with_UART = UART;
    p_initProtocol_called_with_LCD = LCD;
    p_initProtocol_called_with_Keyboard = Keyboard;
    return p_initProtocol_return;
}

/* Mocks for print_welcome() function */
MOCK_VARIABLE int i_print_welcome_called = 0;
MOCK_FUNCTION void print_welcome() {
    i_print_welcome_called++;
}

/* Mocks for loop() and yield() functions */
MOCK_VARIABLE int i_MockProtocol_Loop_called = 0;
MOCK_VARIABLE int i_MockProtocol_Yield_called = 0;
class MockProtocol: public AbstractProtocol {
public:
    MockProtocol(): AbstractProtocol(nullptr, nullptr, nullptr) { }
    virtual ~MockProtocol() { }
    virtual void Loop() override { i_MockProtocol_Loop_called++; }
    virtual void Yield() override { i_MockProtocol_Yield_called++; }
};

/* Mocks for real_print_welcome() function */
void real_print_welcome();
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
MOCK_VARIABLE int i_MockLCD_Clear_called = 0;
MOCK_VARIABLE int i_MockLCD_SetCursor_called = 0;
MOCK_VARIABLE int i_MockLCD_Print_str_called = 0;
MOCK_VARIABLE int i_MockLCD_Print_ch_called = 0;
class MockLCD: public AbstractLCD {
public:
    MockLCD(AbstractBacklight *Backlight): AbstractLCD(Backlight, 20, 2) { }
    virtual ~MockLCD() { }
    virtual void Clear() override { i_MockLCD_Clear_called++; }
    virtual void SetCursor(uint8_t x, uint8_t y) override { i_MockLCD_SetCursor_called++; }
    virtual void Print(const char *str) override { i_MockLCD_Print_str_called++; }
    virtual void Print(char ch) override { i_MockLCD_Print_ch_called++; }
};
MOCK_VARIABLE int i_MockUART_GetBaudRate_called = 0;
class MockUART: public AbstractUART {
public:
    MockUART(): AbstractUART() { }
    virtual ~MockUART() { }
    virtual uint8_t PutCh(uint8_t TxByte) override { return 0; }
    virtual uint8_t GetCh() override { return 0; }
    virtual uint32_t GetBaudRate() const override { i_MockUART_GetBaudRate_called++; return AbstractUART::GetBaudRate(); }
};

#undef DEBUG_STR
#define DEBUG_STR(str) printf("%s", str)

#pragma endregion

#include "../ag-panel/src/main.cpp"

/* Call before each unit test case */
void setUp(void) {

    /* Reset variables in main.cpp */
    s_UART = nullptr;
    s_LCD = nullptr;
    s_Keyboard = nullptr;
    s_Protocol = nullptr;
    g_DebugUART = nullptr;

    /* Reset local mocks */
    i_initDebug_called = 0;
    i_initUART_called = 0;
    i_initBacklight_called = 0;
    i_initFont_called = 0;
    i_initLCD_called = 0;
    i_initKeyboard_called = 0;
    i_initProtocol_called = 0;

    i_MockProtocol_Loop_called = 0;
    i_MockProtocol_Yield_called = 0;

    i_MockBacklight_SetOn_called = 0;
    i_MockBacklight_SetBrightness_called = 0;
    i_MockBacklight_SetRGB_called = 0;
    i_MockLCD_Clear_called = 0;
    i_MockLCD_SetCursor_called = 0;
    i_MockLCD_Print_str_called = 0;
    i_MockLCD_Print_ch_called = 0;
    i_MockUART_GetBaudRate_called = 0;
}

/* Call after each unit test case */
void tearDown(void) {
}

/* Unit test function to test proper initialization of all classes */
void test_setup_calls_all_init_functions_with_right_arguments(void) {

    /* Calling the function under test */
    setup();

    /* Check if all init functions are called */
    TEST_ASSERT_TRUE(i_initDebug_called == 1);
    TEST_ASSERT_TRUE(i_initUART_called == 1);
    TEST_ASSERT_TRUE(i_initBacklight_called == 1);
    TEST_ASSERT_TRUE(i_initFont_called == 1);
    TEST_ASSERT_TRUE(i_initLCD_called == 1);
    TEST_ASSERT_TRUE(i_initKeyboard_called == 1);
    TEST_ASSERT_TRUE(i_initProtocol_called == 1);
    TEST_ASSERT_TRUE(i_print_welcome_called == 1);

    /* Check if all instance pointer are stored in proper variables */
    TEST_ASSERT_EQUAL_PTR(g_DebugUART, p_initDebug_return);
    TEST_ASSERT_EQUAL_PTR(s_UART, p_initUART_return);
    TEST_ASSERT_EQUAL_PTR(s_LCD, p_initLCD_return);
    TEST_ASSERT_EQUAL_PTR(s_Keyboard, p_initKeyboard_return);
    TEST_ASSERT_EQUAL_PTR(s_Protocol, p_initProtocol_return);

    /* Check if all init functions are called with proper arguments */
    TEST_ASSERT_EQUAL_PTR(p_initProtocol_called_with_UART, p_initUART_return);
    TEST_ASSERT_EQUAL_PTR(p_initProtocol_called_with_LCD, p_initLCD_return);
    TEST_ASSERT_EQUAL_PTR(p_initProtocol_called_with_Keyboard, p_initKeyboard_return);
    TEST_ASSERT_EQUAL_PTR(p_initKeyboard_called_with_LCD, p_initLCD_return);
    TEST_ASSERT_EQUAL_PTR(p_initLCD_called_with_Backlight, p_initBacklight_return);
    TEST_ASSERT_EQUAL_PTR(p_initLCD_called_with_Font, p_initFont_return);
}

/* Unit test function to test basic function of Arduino's loop() function */
void test_loop_calls_protocol_loop_and_yield(void) {

    /* Setup test */
    s_Protocol = new MockProtocol();

    /* Calling the function under test */
    loop();

    /* Check if all init functions are called */
    TEST_ASSERT_TRUE(i_MockProtocol_Loop_called == 1);
    TEST_ASSERT_TRUE(i_MockProtocol_Yield_called == 1);

    /* Cleanup test */
    delete s_Protocol;
}

/* Unit test function to test basic function of Arduino's yield() function */
void test_yield_calls_protocol_yield(void) {

    /* Setup test */
    s_Protocol = new MockProtocol();

    /* Calling the function under test */
    yield();

    /* Check if all init functions are called */
    TEST_ASSERT_TRUE(i_MockProtocol_Loop_called == 0);
    TEST_ASSERT_TRUE(i_MockProtocol_Yield_called == 1);

    /* Cleanup test */
    delete s_Protocol;
}

/* Unit test function to test basic function of print_welcome() function */
void test_print_welcome_calls_lcd_functions(void) {

    /* Setup test */
    AbstractBacklight *p_Backlight = new MockBacklight();

    s_LCD = new MockLCD(p_Backlight);
    printf("LCD size = %dx%d\n", s_LCD->GetColumns(), s_LCD->GetRows());

    s_UART = new MockUART();
    printf("baud rate = %d\n", s_UART->GetBaudRate());

    /* Calling the function under test */
    real_print_welcome();

    /* Check if all init functions are called */
    TEST_ASSERT_TRUE(i_MockBacklight_SetOn_called >= 1 || i_MockBacklight_SetBrightness_called >= 1 || i_MockBacklight_SetRGB_called >= 1);
    TEST_ASSERT_TRUE(i_MockLCD_Clear_called >= 1);
    TEST_ASSERT_TRUE(i_MockLCD_SetCursor_called >= 1);
    TEST_ASSERT_TRUE(i_MockLCD_Print_str_called >= 1 || i_MockLCD_Print_ch_called >= 1);
    TEST_ASSERT_TRUE(i_MockUART_GetBaudRate_called >= 1);

    /* Cleanup test */
    delete s_UART;
    delete s_LCD;
}

/* Unit testing main function */
int main(int argc, char *argv[]) {

    UNITY_BEGIN();

    /* Calling unit test functions */
    RUN_TEST(test_setup_calls_all_init_functions_with_right_arguments);
    RUN_TEST(test_loop_calls_protocol_loop_and_yield);
    RUN_TEST(test_yield_calls_protocol_yield);
    RUN_TEST(test_print_welcome_calls_lcd_functions);

    UNITY_END();
}

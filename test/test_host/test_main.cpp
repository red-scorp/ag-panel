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

#define MOCK_FUNCTION   
#define MOCK_VARIABLE   static

using namespace std;

/* Mocks for initDebug() function */
MOCK_VARIABLE bool b_initDebug_called = false;
MOCK_VARIABLE AbstractUART* p_initDebug_return = (AbstractUART*)(void*)b_initDebug_called;
MOCK_FUNCTION AbstractUART *initDebug() {
    b_initDebug_called = true;
    return p_initDebug_return;
}

/* Mocks for initUART() function */
MOCK_VARIABLE bool b_initUART_called = false;
MOCK_VARIABLE AbstractUART* p_initUART_return = (AbstractUART*)(void*)b_initUART_called;
MOCK_FUNCTION AbstractUART *initUART() {
    b_initUART_called = true;
    return p_initUART_return;
}

/* Mocks for initBacklight() function */
MOCK_VARIABLE bool b_initBacklight_called = false;
MOCK_VARIABLE AbstractBacklight* p_initBacklight_return = (AbstractBacklight*)(void*)b_initBacklight_called;
MOCK_FUNCTION AbstractBacklight *initBacklight() {
    b_initBacklight_called = true;
    return p_initBacklight_return;
}

/* Mocks for initFont() function */
MOCK_VARIABLE bool b_initFont_called = false;
MOCK_VARIABLE AbstractFont* p_initFont_return = (AbstractFont*)(void*)b_initFont_called;
MOCK_FUNCTION AbstractFont *initFont() {
    b_initFont_called = true;
    return p_initFont_return;
}

/* Mocks for initLCD() function */
MOCK_VARIABLE bool b_initLCD_called = false;
MOCK_VARIABLE AbstractLCD* p_initLCD_return = (AbstractLCD*)(void*)b_initLCD_called;
MOCK_VARIABLE AbstractBacklight *p_initLCD_called_with_Backlight = nullptr;
MOCK_VARIABLE AbstractFont *p_initLCD_called_with_Font = nullptr;
MOCK_FUNCTION AbstractLCD *initLCD(AbstractBacklight *Backlight, AbstractFont *Font) {
    b_initLCD_called = true;
    p_initLCD_called_with_Backlight = Backlight;
    p_initFont_return = Font;
    return p_initLCD_return;
}

/* Mocks for initKeyboard() function */
MOCK_VARIABLE bool b_initKeyboard_called = false;
MOCK_VARIABLE AbstractKeyboard* p_initKeyboard_return = (AbstractKeyboard*)(void*)b_initKeyboard_called;
MOCK_VARIABLE AbstractLCD *p_initKeyboard_called_with_LCD = nullptr;
MOCK_FUNCTION AbstractKeyboard *initKeyboard(AbstractLCD *p_LCD) {
    b_initKeyboard_called = true;
    p_initKeyboard_called_with_LCD = p_LCD;
    return p_initKeyboard_return;
}

/* Mocks for initProtocol() function */
MOCK_VARIABLE bool b_initProtocol_called = false;
MOCK_VARIABLE AbstractProtocol* p_initProtocol_return = (AbstractProtocol*)(void*)b_initProtocol_called;
MOCK_VARIABLE AbstractUART *p_initProtocol_called_with_UART = nullptr;
MOCK_VARIABLE AbstractLCD *p_initProtocol_called_with_LCD = nullptr;
MOCK_VARIABLE AbstractKeyboard *p_initProtocol_called_with_Keyboard = nullptr;
MOCK_FUNCTION AbstractProtocol *initProtocol(AbstractUART *UART, AbstractLCD *LCD, AbstractKeyboard *Keyboard) {
    b_initProtocol_called = true;
    p_initProtocol_called_with_UART = UART;
    p_initProtocol_called_with_LCD = LCD;
    p_initProtocol_called_with_Keyboard = Keyboard;
    return p_initProtocol_return;
}

/* Mocks for print_welcome() function */
MOCK_VARIABLE bool b_print_welcome_called = false;
MOCK_FUNCTION void print_welcome() {
    b_print_welcome_called = true;
}

/* Mocks for loop() and yield() functions */
MOCK_VARIABLE bool b_MockProtocol_Loop_called = false;
MOCK_VARIABLE bool b_MockProtocol_Yield_called = false;
class MockProtocol: public AbstractProtocol {
public:
    MockProtocol(): AbstractProtocol(nullptr, nullptr, nullptr) { }
    virtual ~MockProtocol() { }
    virtual void Loop() override { b_MockProtocol_Loop_called = true; }
    virtual void Yield() override { b_MockProtocol_Yield_called = true; }
};

/* Mocks for real_print_welcome() function */
void real_print_welcome();
MOCK_VARIABLE bool b_MockLCD_Clear_called = false;
MOCK_VARIABLE bool b_MockLCD_SetCursor_called = false;
MOCK_VARIABLE bool b_MockLCD_Print_str_called = false;
MOCK_VARIABLE bool b_MockLCD_Print_ch_called = false;
class MockLCD: public AbstractLCD {
public:
    MockLCD(): AbstractLCD(nullptr, 20, 2) { }
    virtual ~MockLCD() { }
    virtual void Clear() override { b_MockLCD_Clear_called = true; }
    virtual void SetCursor(uint8_t x, uint8_t y) override { b_MockLCD_SetCursor_called = true; }
    virtual void Print(const char *str) override { b_MockLCD_Print_str_called = true; }
    virtual void Print(char ch) override { b_MockLCD_Print_ch_called = true; }
};
MOCK_VARIABLE bool b_MockUART_GetBaudRate_called = false;
class MockUART: public AbstractUART {
public:
    MockUART(): AbstractUART(9600) { }
    virtual ~MockUART() { }
    virtual uint8_t PutCh(uint8_t txbyte) override { return 0; }
    virtual uint8_t GetCh() override { return 0; }
    virtual uint32_t GetBaudRate() const override { b_MockUART_GetBaudRate_called = true; return 0; }
};

#define DEBUG_STR(str) printf("%s", str)

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
    b_initDebug_called = false;
    b_initUART_called = false;
    b_initBacklight_called = false;
    b_initFont_called = false;
    b_initLCD_called = false;
    b_initKeyboard_called = false;
    b_initProtocol_called = false;

    b_MockProtocol_Loop_called = false;
    b_MockProtocol_Yield_called = false;

    b_MockLCD_Clear_called = false;
    b_MockLCD_SetCursor_called = false;
    b_MockLCD_Print_str_called = false;
    b_MockLCD_Print_ch_called = false;
    b_MockUART_GetBaudRate_called = false;
}

/* Call after each unit test case */
void tearDown(void) {
}

/* Unit test function to test proper initialization of all classes */
void test_setup_calls_all_init_functions_with_right_arguments(void) {

    /* Calling the function under test */
    setup();

    /* Check if all init functions are called */
    TEST_ASSERT_TRUE(b_initDebug_called);
    TEST_ASSERT_TRUE(b_initUART_called);
    TEST_ASSERT_TRUE(b_initBacklight_called);
    TEST_ASSERT_TRUE(b_initFont_called);
    TEST_ASSERT_TRUE(b_initLCD_called);
    TEST_ASSERT_TRUE(b_initKeyboard_called);
    TEST_ASSERT_TRUE(b_initProtocol_called);
    TEST_ASSERT_TRUE(b_print_welcome_called);

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
    TEST_ASSERT_TRUE(b_MockProtocol_Loop_called);
    TEST_ASSERT_TRUE(b_MockProtocol_Yield_called);

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
    TEST_ASSERT_FALSE(b_MockProtocol_Loop_called);
    TEST_ASSERT_TRUE(b_MockProtocol_Yield_called);

    /* Cleanup test */
    delete s_Protocol;
}

/* Unit test function to test basic function of print_welcome() function */
void test_print_welcome_calls_lcd_functions(void) {

    /* Setup test */
    s_LCD = new MockLCD();
    printf("LCD size = %dx%d\n", s_LCD->GetColumns(), s_LCD->GetRows());

    s_UART = new MockUART();
    printf("baud rate = %d\n", s_UART->GetBaudRate());

    /* Calling the function under test */
    real_print_welcome();

    /* Check if all init functions are called */
    TEST_ASSERT_TRUE(b_MockLCD_Clear_called);
    TEST_ASSERT_TRUE(b_MockLCD_SetCursor_called);
    TEST_ASSERT_TRUE(b_MockLCD_Print_str_called || b_MockLCD_Print_ch_called);
    TEST_ASSERT_TRUE(b_MockUART_GetBaudRate_called);

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
    // RUN_TEST(test_print_welcome_calls_lcd_functions);

    UNITY_END();
}

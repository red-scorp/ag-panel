/*! \file test_main.cpp
    \brief AG-Panel Project test main code
    \copyright (C) 2021-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

using namespace std;

#include "../ag-panel/src/main.cpp"

#include "../ag-panel/src/debug.cpp"

#include "../ag-panel/src/uart/init.cpp"
#include "../ag-panel/src/uart/NoneUART.cpp"
#include "../ag-panel/src/lcd/init.cpp"
#include "../ag-panel/src/lcd/backlight/init.cpp"
#include "../ag-panel/src/lcd/font/init.cpp"
#include "../ag-panel/src/keyboard/init.cpp"
#include "../ag-panel/src/protocol/init.cpp"
#include "../ag-panel/src/protocol/RawSerialProtocol.cpp"

int main(int argc, char *argv[]) {

    UNITY_BEGIN();

    setup();

    while(true)
        loop();
}

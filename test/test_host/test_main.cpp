/*! \file test_main.cpp
    \brief AG-Panel Project unit test main code
    \copyright (C) 2021-2023 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../unity/unity.h"

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

/* Unit testing main function */
int main(int argc, char *argv[]) {

    UNITY_BEGIN();

    // TODO: call unit test functions



    UNITY_END();
}

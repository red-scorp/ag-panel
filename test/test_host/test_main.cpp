/*!
  \file test_main.cpp
  \brief AG-Panel Project test main code
  \copyright (C) 2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#include "../ag-panel/src/main.cpp"

int main(int argc, char *argv[]) {

  setup();

  while(true)
    loop();
}


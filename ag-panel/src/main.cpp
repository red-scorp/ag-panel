/*!
  \file main.cpp
  \brief AG-Panel Project main code
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "private.h"
#include "../config.h"
#include "version.h"

#include "debug.h"

#include "uart/all.h"
#include "lcd/all.h"
#include "keyboard/all.h"
#include "protocol/all.h"

/*!
  \brief Globally available debugging UART class pointer
  \todo Move it to a separete file ('debug.cpp') to free some space if debug output is disabled.
 */
AbstractUART *g_DebugUART = nullptr;

/*!
  \brief Main communication UART class pointer
 */
static AbstractUART *s_UART = nullptr;

/*!
  \brief Main display class pointer
 */
static AbstractLCD *s_LCD = nullptr;

/*!
  \brief Main input class pointer
 */
static AbstractKeyboard *s_Keyboard = nullptr;

/*!
  \brief Main data exchange protocol class pointer
 */
static AbstractProtocol *s_Protocol = nullptr;

/*!
  \brief Print welcome message to the LCD

  This function prints project name, project version and UART baud rate to the attached LCD.
 */
void print_welcome() {
  char str[s_LCD->GetColumns() + 1];
  uint8_t center_x = (s_LCD->GetColumns() - 16) / 2;
  uint8_t center_y = (s_LCD->GetRows() - 2) / 2;
  memset(str, 0, sizeof(str));
  s_LCD->Clear();
  s_LCD->SetBacklight(bool(true));
  DEBUG_STR("Backlight> "); DEBUG_STR("true"); DEBUG_STR("\n");
  s_LCD->SetCursor(center_x, center_y);
  snprintf(str, sizeof(str) - 1, FW_NAME " v" FW_VERSION);
  s_LCD->Print(str);
  DEBUG_STR("LCD> "); DEBUG_STR(str); DEBUG_STR("\n");
  s_LCD->SetCursor(center_x, center_y + 1);
  snprintf(str, sizeof(str) - 1, "@%luBd Ready", (unsigned long)s_UART->GetBaudRate());
  s_LCD->Print(str);
  DEBUG_STR("LCD> "); DEBUG_STR(str); DEBUG_STR("\n");
}

/*!
  \brief Main initialization function

  - setup debugging
  - setup UART
  - setup LCD
  - setup keyboard
  - setup protocol
 */
void setup() {

  /* 1. First we will initialize debug UART to enable debug output as early as possible */
  /*! \todo Disable with macro if debug output is disabled */
  g_DebugUART = initDebug();

  DEBUG_STR("Starting Up...\n");

  /* 2. As second step we should initialize communication UART */
  DEBUG_STR("Initializing UART...\n");
  s_UART = initUART();

  /* 3. Third step is to initialize display output */
  /* 3.1. Initializing LCD backlight class */
  DEBUG_STR("Initializing Backlight...\n");
  AbstractBacklight *Backlight = initBacklight();

  /* 3.2. Initialize LCD itself */
  DEBUG_STR("Initializing LCD...\n");
  s_LCD = initLCD(Backlight);

  /* 4. Now we should initialize keyboard for input to be ready */
  DEBUG_STR("Initializing Keyboard...\n");
  s_Keyboard = initKeyboard(s_LCD);

  /*! \todo Add AbstractSpeaker and other classes for notice, warning and error sounds??? */

  /* 5. Now it's time for protocol itself. Remember the protocol class defines how all other elements communicate with each other */
  DEBUG_STR("Initializing Protocol...\n");
  s_Protocol = initProtocol(s_UART, s_LCD, s_Keyboard);

  /*! 6. Print a splash screen/welcome message. */
  print_welcome();
}

/*!
  \brief Main loop function

  - run protocol main task
  - start protocol background task
 */
void loop() {

  if(s_Protocol != nullptr) {
    s_Protocol->Loop();
    s_Protocol->Yield();
  }
}

#if !defined(ARDUINO_ARCH_ESP32)
/*!
  \brief Background task function

  - start protocol background task
 */
void yield() {

  if(s_Protocol != nullptr)
    s_Protocol->Yield();
}
#endif

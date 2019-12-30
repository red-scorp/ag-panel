# Arduino Graphic Panel for lcdproc (ag-panel)

A Next generation of [lcdproc](http://lcdproc.sourceforge.net/) display panel based on Arduino and similar HW.
This project is based on my earlier code [Arduino LCD over Serial Panel (alos-panel)](https://github.com/red-scorp/alos-panel).
The original code was fully rewritten for C++ for better maintainability and expansion.
Documentation is pending!

This project **will** support different connections and different types of displays, including HD44780 based.
Main platform for this project is Arduino Uno and Nano boards but it should certainly work on another Arduino boards as well.

## Current status
Work in progress but already usable.

## Supported configurations
- Protocols
  - [x] los-panel (lcdproc) for direct HD44780 (will support **only** HD44780 displays)
  - [ ] rawserial (lcdproc) (to be implemented)
  - [ ] own protocol TBD (lcdproc) (to be implemented)
- UART Serial
  - [x] Hardware UART
  - [x] Software UART
  - [x] No (null) UART
  - [x] Buffered UART (addition to a regular UART)
- LCD Display
  - [x] HD44780 in 4-bit and 8-bit modes
  - [x] HD44780 w/ binary (on/off) backlight over I2C bus
  - [x] HD44780 w/ RGB binary (7 colors) backlight over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
- LCD Backlight
  - [x] Not controlled
  - [x] ON/OFF binary backlight
  - [x] RGB binary (7 colors) backlight
  - [x] PWM-controlled (monochrome brightness) backlight
  - [x] RGB PWM-controlled backlight (hue brightness) backlight
- Keyboard
  - [x] No keyboard
  - [x] Digital Matrix up to 4x4 (on analog pins)
  - [x] Analog Arduino joystick as key strokes
  - [x] Analog Keypad of 'LCD Keypad Shield'
  - [x] Rotary Encoder
  - [x] Analog Matrix 4x4 and 3x4 from RobotDyn
  - [x] Digital Keypad or Digital Joystick over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
  - [x] Capacitive Keypad attached over I2C based on MPR121
  - [x] Capacitive Keypad attached over I2C based on TTP229
  - [x] Single pin button
  - [x] Joined keyboard for combining several supported keyboards/keypads together in a single unit
- Development
  - [x] Hardware UART port for debugging output
  - [x] Software UART port for debugging output
  - [x] Hex String dump of UART output
  - [x] Hex String dump of UART input

Please check 'config.h' and 'config_adv.h' for up-to-date information.

## How to help
Your contributions are welcome!
Please contact me directly over e-mail andriy.golovnya@googlemail.com or over [GitHub](https://github.com/red-scorp).
Thanks in advance!

# Arduino Graphic Panel for lcdproc (ag-panel)

A Next generation of [lcdproc](http://lcdproc.sourceforge.net/) display panel based on Arduino and similar HW.
This project is based on my earlier code [Arduino LCD over Serial Panel (alos-panel)](https://github.com/red-scorp/alos-panel).
Documentation pending!

This project **will** support different connections and different types of displays, including HD44780 based.
Main platform for this project is Arduino Uno and Nano boards but it should certainly work on another Arduino boards as well.

## Current status
Work in progress but already usable.

## Supported configurations
- Protocols
  - [x] los-panel (lcdproc) for direct HD44780 (will be removed soon)
  - [ ] rawserial (lcdproc) (to be implemented)
- UART Serial
  - [x] Hardware UART
  - [x] Software UART
  - [x] No (null) UART
  - [x] Buffered UART (addition to a regualr UART)
- LCD Display
  - [x] HD44780 in 4-bit and 8-bit modes
  - [x] HD44780 over I2C bus
  - [x] HD44780 w/ RGB binary backlight over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
- LCD Backlight
  - [x] Not controlled
  - [x] ON/OFF binary backlight
  - [x] RGB binary (7 colors) backlight
  - [x] PWM-controlled (monotone brightness) backlight
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
    [ ] Single pin button (to be implemented)
- Development
  - [ ] Hardware UART port for debugging output (to be implemented)
  - [ ] Software UART port for debugging output (to be implemented)
  - [ ] Hex String dump of UART output (to be implemented)
  - [ ] Hex String dump of UART input (to be implemented)

Please check config.h for more information.

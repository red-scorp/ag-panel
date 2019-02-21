# Arduino LCD over Serial Panel (alos-panel)

Here I'm creating an Arduino based replacement for [LCD over Serial Panel (LoS-Panel)](https://mlf.home.xs4all.nl/los/) for HD44780 Driver of [lcdproc](http://www.lcdproc.org/).
More information on setup of LoS-Panel for lcdproc [can be found here](http://lcdproc.sourceforge.net/docs/current-user.html#hd44780-los-panel).

This project **will** support different connections and different types of HD44780 based displays.
Main platform for this project is Arduino Uno and Nano boards but it should certainly work on another Arduino boards as well.

## Current status 
Work in progress but already usable.

## Supported configurations
- UART Serial
  - [x] HW UART of Arduino
  - [x] HW UART of Arduino with extra buffer
  - [ ] SW UART of Arduino (to be defined)
- LCD Display
  - [x] HD44780 in 4-bit and 8-bit modes
  - [x] HD44780 over I2C bus
- LCD Backlight
  - [x] Not controlled
  - [x] ON/OFF binary backlight
  - [x] PWM-controlled backlight
- Keyboard
  - [x] No keyboard
  - [ ] Digital Matrix up to 4x4 (work in progress)
  - [ ] Analog Arduino joystick as key strokes (work in progress)
  - [ ] Analog Keypad (work in progress)
  - [ ] Analog Matrix (to do defined)

Please check config.h for more information.

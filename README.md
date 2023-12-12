```
 █████╗   ██████╗         ██████╗   █████╗  ███╗   ██╗ ███████╗ ██╗     
██╔══██╗ ██╔════╝         ██╔══██╗ ██╔══██╗ ████╗  ██║ ██╔════╝ ██║     
███████║ ██║  ███╗ █████╗ ██████╔╝ ███████║ ██╔██╗ ██║ █████╗   ██║     
██╔══██║ ██║   ██║ ╚════╝ ██╔═══╝  ██╔══██║ ██║╚██╗██║ ██╔══╝   ██║     
██║  ██║ ╚██████╔╝        ██║      ██║  ██║ ██║ ╚████║ ███████╗ ███████╗
╚═╝  ╚═╝  ╚═════╝         ╚═╝      ╚═╝  ╚═╝ ╚═╝  ╚═══╝ ╚══════╝ ╚══════╝
```

# Arduino Graphic Panel for lcdproc (ag-panel)

Welcome to the Arduino Graphic Panel for lcdproc (ag-panel) project! This is the next generation of [lcdproc](http://lcdproc.sourceforge.net/) display panel, built on the versatile Arduino platform and similar hardware. If you're looking to create dynamic and customizable displays, this project is for you.

## Project Evolution

This project is based on the earlier code of [Arduino LCD over Serial Panel (alos-panel)](https://github.com/red-scorp/alos-panel). However, we've taken it to the next level by fully rewriting the original C code in C++ for improved maintainability and expandability. While the documentation is still a work in progress, we're excited to share the project's potential with you.

## Versatile Compatibility

The ag-panel project is designed to offer maximum compatibility and flexibility. Here's what it currently supports:

- **Protocols**
  - ✓ los-panel (lcdproc) for direct HD44780 (supports **only** HD44780 displays)
  - ◻️ rawserial (lcdproc) (in progress)
  - ◻️ own protocol TBD (lcdproc) (to be implemented)

- **UART Serial**
  - ✓ Hardware UART (up to 10 if supported)
  - ✓ USB Virtual UART (for SAMD, SAM, and STM32 platforms)
  - ✓ Software UART (for AVR, STM32, ESP8266, and ESP32 platforms)
  - ◻️ Bluetooth UART (to be implemented)
  - ◻️ LAN/WLAN TCP/IP socket (to be implemented)
  - ✓ No (null) UART
  - ✓ Buffered UART (addition to a regular UART)

- **LCD Display**
  - ✓ HD44780 and clones in 4-bit and 8-bit modes
  - ✓ HD44780 with binary (on/off) backlight over I2C bus, based on 'I2C LCD backpack'
  - ✓ HD44780 with RGB binary (7 colors) backlight over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
  - ✓ AIP31068, HD44780-like with I2C and SPI interface
  - ◻️ U8g2 compatible displays (to be implemented)

- **LCD Backlight**
  - ✓ Not controlled or controlled by the display itself
  - ✓ ON/OFF binary backlight
  - ✓ RGB binary (7 colors) backlight
  - ✓ PWM-controlled (monochrome brightness) backlight
  - ✓ RGB PWM-controlled (hue brightness) backlight
  - ✓ RGB PWM-controlled backlight attached over I2C bus with the help of PCA9633 LED controller

- **Keyboard / Input**
  - ✓ No keyboard
  - ✓ Digital Matrix up to 4x4 (on analog pins)
  - ✓ Analog Arduino joystick as key strokes
  - ✓ Analog Keypad of 'LCD Keypad Shield'
  - ✓ Rotary Encoder
  - ✓ Analog Matrix 4x4 and 3x4 from RobotDyn
  - ✓ Digital Keypad or Digital Joystick over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
  - ✓ Capacitive Keypad attached over I2C based on MPR121 controller
  - ✓ Capacitive Keypad attached over I2C based on TTP229 controller
  - ✓ Single pin button
  - ✓ Joined keyboard for combining several supported keyboards/keypads together in a single unit

- **Development / Debugging**
  - ✓ Hardware UART port for debugging output
  - ✓ Software UART port for debugging output
  - ✓ Hex String dump of UART output
  - ✓ Hex String dump of UART input
  - ✓ Unit Tests for main components

Please refer to *'config.h'* and *'config_adv.h'* for the most up-to-date information on supported configurations.

## Current Status

While ag-panel is still a work in progress, it's already usable and offers a wide range of features for your display projects.

## Project Structure

### Platforms

The ag-panel code is written in C++ and utilizes the Arduino Framework. It's designed to compile and run on various embedded CPU platforms, including but not limited to:

- ✓ Atmel (Microchip) AVR
- ✓ Atmel (Microchip) SAMD and SAM
- ◻️ Renesas RA (to be tested)
- ◻️ Espressif ESP32 and ESP8266 (to be tested)
- ✓ ST STM32
- ◻️ Raspberry RP2040 (to be tested)
- ◻️ RISC-V (planned)
- ◻️ Logic Green AVR (planned)

### Code Structure

The code is organized by subsystems, with classes for different functionalities residing in their respective folders:

```
ag-panel
├── src (main source code)
│   ├── keyboard (keyboard/input classes)
│   ├── lcd (LCD related classes)
│   │   ├── backlight (LCD backlight classes)
│   │   └── font (font classes)
│   ├── protocol (protocol logic)
│   └── uart (UART implementations)
├── ag-panel.ino (empty)
├── config_adv.h (advanced configuration)
└── config.h (basic configuration)
```

Unit test code is located in the *'test'* folder:

```
test
├── test_lospanel (unit tests for los-panel protocol)
├── test_main (unit tests for main components)
├── test_rawserial (unit tests for rawserial protocol)
└── unity (Unity unit test framework)
```

## Getting Started

To begin working with the ag-panel project, you'll need to fulfill certain dependencies:

### Download Code

You can obtain the ag-panel project code using one of the following methods:

- If you prefer using the Git version control system, run the following command: `git clone https://github.com/red-scorp/ag-panel.git`
- Alternatively, you can download the entire master branch code as a [single zip file](https://github.com/red-scorp/ag-panel/archive/refs/heads/master.zip).

### Supported IDEs

You can compile the ag-panel project with any IDE that supports development for the Arduino SDK. We've tested it with the following IDEs:

- To open the project in the [Arduino IDE](https://www.arduino.cc/en/software), simply open the INO file located at *ag-panel/ag-panel.ino* from the File menu.
- To use [Visual Studio Code](https://code.visualstudio.com/) with the [PlatformIO](https://platformio.org/) Extension, open the project folder containing the *platformio.ini* file from the File menu.

### Required Libraries

To successfully compile the project, you may need to install the following libraries:

- LiquidCrystal
- LiquidCrystal_I2C
- Adafruit MPR121
- Adafruit RGB LCD Shield Library
- TTP229
- LiquidCrystal_AIP31068
- SoftSPIB
- pca9633
- EspSoftwareSerial
- ESP32 AnalogWrite
- U8g2

While PlatformIO can automatically resolve library dependencies, Arduino IDE users will need to install the required libraries manually.

## How You Can Contribute

We welcome your contributions to the ag-panel project! Whether it's code, resources, or financial support, your help is invaluable. Feel free to reach out directly via email at andriy.golovnya@gmail.com or through my [GitHub profile](https://github.com/red-scorp).

If you'd like to make a financial contribution to support the project's development, you can donate via [PayPal](http://paypal.me/redscorp) or [Ko-Fi](http://ko-fi.com/redscorp). Your generosity is greatly appreciated.

Thank you in advance for your support, and let's make the ag-panel project even better together!

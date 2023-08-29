```
 █████╗   ██████╗         ██████╗   █████╗  ███╗   ██╗ ███████╗ ██╗     
██╔══██╗ ██╔════╝         ██╔══██╗ ██╔══██╗ ████╗  ██║ ██╔════╝ ██║     
███████║ ██║  ███╗ █████╗ ██████╔╝ ███████║ ██╔██╗ ██║ █████╗   ██║     
██╔══██║ ██║   ██║ ╚════╝ ██╔═══╝  ██╔══██║ ██║╚██╗██║ ██╔══╝   ██║     
██║  ██║ ╚██████╔╝        ██║      ██║  ██║ ██║ ╚████║ ███████╗ ███████╗
╚═╝  ╚═╝  ╚═════╝         ╚═╝      ╚═╝  ╚═╝ ╚═╝  ╚═══╝ ╚══════╝ ╚══════╝
```

# Arduino Graphic Panel for lcdproc (ag-panel)

A Next generation of [lcdproc](http://lcdproc.sourceforge.net/) display panel based on Arduino and similar HW.
This project is based on my earlier code of [Arduino LCD over Serial Panel (alos-panel)](https://github.com/red-scorp/alos-panel).
The original _alos-panel_ C code was fully rewritten in C++ for better maintainability and expansion.
Documentation is pending!

This project **will** support multiple different connections and different types of displays, including HD44780-based displays.
The main platform for this project is Arduino Uno and Nano boards, but it should certainly work on other Arduino boards as well.
One of the goals of this project is portability between different CPUs. You can expect it to work with AVR, SAM, SAMD, STM32, ESP32, RISC-V, and other hobby platforms.

## Current Status

Work in progress, but already usable.

## Supported Configurations

- Protocols
  - [x] los-panel (lcdproc) for direct HD44780 (supports **only** HD44780 displays)
  - [ ] rawserial (lcdproc) (in progress)
  - [ ] own protocol TBD (lcdproc) (to be implemented)
- UART Serial
  - [x] Hardware UART (up to 10 if supported)
  - [x] USB Virtual UART (for SAMD, SAM, and STM32 platforms)
  - [x] Software UART (for AVR, STM32, ESP8266, and ESP32 platforms)
  - [ ] Bluetooth UART (to be implemented)
  - [ ] LAN/WLAN TCP/IP socket (to be implemented)
  - [x] No (null) UART
  - [x] Buffered UART (addition to a regular UART)
- LCD Display
  - [x] HD44780 and clones in 4-bit and 8-bit modes
  - [x] HD44780 with binary (on/off) backlight over I2C bus, based on 'I2C LCD backpack'
  - [x] HD44780 with RGB binary (7 colors) backlight over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
  - [x] AIP31068, HD44780-like with I2C and SPI interface
- LCD Backlight
  - [x] Not controlled or controlled by the display itself
  - [x] ON/OFF binary backlight
  - [x] RGB binary (7 colors) backlight
  - [x] PWM-controlled (monochrome brightness) backlight
  - [x] RGB PWM-controlled (hue brightness) backlight
  - [x] RGB PWM-controlled backlight attached over I2C bus with the help of PCA9633 LED controller
- Keyboard / Input
  - [x] No keyboard
  - [x] Digital Matrix up to 4x4 (on analog pins)
  - [x] Analog Arduino joystick as key strokes
  - [x] Analog Keypad of 'LCD Keypad Shield'
  - [x] Rotary Encoder
  - [x] Analog Matrix 4x4 and 3x4 from RobotDyn
  - [x] Digital Keypad or Digital Joystick over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
  - [x] Capacitive Keypad attached over I2C based on MPR121 controller
  - [x] Capacitive Keypad attached over I2C based on TTP229 controller
  - [x] Single pin button
  - [x] Joined keyboard for combining several supported keyboards/keypads together in a single unit
- Development / Debugging
  - [x] Hardware UART port for debugging output
  - [x] Software UART port for debugging output
  - [x] Hex String dump of UART output
  - [x] Hex String dump of UART input

Please check *'config.h'* and *'config_adv.h'* for up-to-date information.

## Design

### Platforms

The code of _ag-panel_ is written in C++ with the Arduino Framework.
The code compiles and runs on several embedded CPU platforms:

- [x] Atmel (Microchip) AVR
- [x] Atmel (Microchip) SAMD and SAM
- [ ] Renesas RA (to be tested)
- [ ] Espressif ESP32 and ESP8266 (to be tested)
- [x] ST STM32
- [ ] Raspberry RP2040 (to be tested)
- [ ] RISC-V (planned)
- [ ] Logic Green AVR (planned)

### Class Diagram

The UML class diagram is shown below:

![UML diagram](/img/class_diagram.png)

### Code Tree

The code is structured by subsystem.
Classes of different subsystems are located in their respective folders.

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

### Dependencies

This project has several dependencies you should fullfil to be able to build it.

#### Download code

To download _ag-panel_ code you can use one of following ways:

- To use Git version control system you can use following command: ```git clone https://github.com/red-scorp/ag-panel.git```
- Alternatively, you can download full master branch code in a [single zip file](https://github.com/red-scorp/ag-panel/archive/refs/heads/master.zip).

#### IDEs

The code of _ag-panel_ can be compiled with any IDE which supports development for Arduino SDK.
The following IDEs are tested with _ag-panel_ project:

- To open the project in [Arduino IDE](https://www.arduino.cc/en/software) you should open INO file _ag-panel/ag-panel.ino_ from File menu.
- To open the project in [Visual Studio Code](https://code.visualstudio.com/) with PlatformIO Extension you should open project folder with _platformio.ini_ from File menu.

#### Libraries

To compile the project following libraries might be required:

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

While PlatformIO is able to resolve library dependencies itself, in Arduino IDE you have to install required libraries manually.

## How to Help

Your contributions in the form of code, resources, or finances are welcome! Please contact me directly via email at andriy.golovnya@gmail.com or through my [GitHub profile](https://github.com/red-scorp).

If you'd like to make a financial contribution, you can donate via [PayPal](http://paypal.me/redscorp) or [Ko-Fi](http://ko-fi.com/redscorp). Your support is greatly appreciated.

Thanks in advance!

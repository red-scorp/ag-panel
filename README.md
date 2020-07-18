# Arduino Graphic Panel for lcdproc (ag-panel)

A Next generation of [lcdproc](http://lcdproc.sourceforge.net/) display panel based on Arduino and similar HW.
This project is based on my earlier code of [Arduino LCD over Serial Panel (alos-panel)](https://github.com/red-scorp/alos-panel).
The original alos-panel C code was fully rewritten on C++ for better maintainability and expansion.
Documentation is pending!

This project **will** support different connections and different types of displays, including HD44780 based.
Main platform for this project is Arduino Uno and Nano boards but it should certainly work on another Arduino boards as well.
One of the topics of this project is portability between different CPUs, though you can expect it working with AVR, SAM, SAMD, STM32, ESP32, RISC-V and other hoddy platforms as well.

## Current status
Work in progress but already usable.

## Supported configurations
- Protocols
  - [x] los-panel (lcdproc) for direct HD44780 (will support **only** HD44780 displays)
  - [ ] rawserial (lcdproc) (in progress)
  - [ ] own protocol TBD (lcdproc) (to be implemented)
- UART Serial
  - [x] Hardware UART
  - [x] USB Virtual UART (for SAMD and SAM platforms)
  - [x] Software UART (for AVR, STM32, ESP8266 and ESP32 platforms)
  - [ ] Bluetooth UART (to be implemented)
  - [ ] LAN/WLAN TCP/IP socket (to be implemented)
  - [x] No (null) UART
  - [x] Buffered UART (addition to a regular UART)
- LCD Display
  - [x] HD44780 and clones in 4-bit and 8-bit modes
  - [x] HD44780 w/ binary (on/off) backlight over I2C bus, based on 'I2C LCD backpack'
  - [x] HD44780 w/ RGB binary (7 colors) backlight over I2C bus, like 'Adafruit RGB 16x2 LCD Shield'
  - [x] AIP31068, HD44780-like w/ I2C and SPI interface
- LCD Backlight
  - [x] Not controlled
  - [x] ON/OFF binary backlight
  - [x] RGB binary (7 colors) backlight
  - [x] PWM-controlled (monochrome brightness) backlight
  - [x] RGB PWM-controlled (hue brightness) backlight
  - [x] RGB PWM-controlled backlight attached over I2C bus w/ help of PCA9633 LED controller
- Keyboard
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
- Development
  - [x] Hardware UART port for debugging output
  - [x] Software UART port for debugging output
  - [x] Hex String dump of UART output
  - [x] Hex String dump of UART input

Please check 'config.h' and 'config_adv.h' for up-to-date information.

## Design

The code of ag-panel is written on C++ with Arduino Framework.
The code compiles and runs on several embedded CPU platforms:
- [x] AVR Atmega328, Atmega2560
- [ ] AVR SAMD and SAM (to be tested)
- [ ] ESP32 and ESP8266 (to be tested)
- [ ] STM32 (to be tested)
- [ ] RISC-V (planned)

Basic class diagram is shown below:

```nomnoml

[<abstract>AbstractProtocol]
[AbstractProtocol] o-> [AbstractLCD]
[AbstractProtocol] o-> [AbstractUART]
[AbstractProtocol] o-> [AbstractKeyboard]
[LoSPanelProtocol] -:> [AbstractProtocol]
[RawSerialProtocol] -:> [AbstractProtocol]

[<abstract>AbstractUART]
[BufferedUART] -:> [AbstractUART]
[BufferedUART] --> 1 [AbstractUART]
[HardwareUART] -:> [AbstractUART]
[NoneUART] -:> [AbstractUART]
[SoftwareUART] -:> [AbstractUART]
[USBVirtualUART] -:> [AbstractUART]
[TextLoggingUART] -:> [AbstractUART]
[TextLoggingUART] --> 2 [AbstractUART]

[<abstract>AbstractLCD]
[AbstractLCD] o-> [AbstractBacklight]

[<abstract>AbstractTextLCD]
[AbstractTextLCD] -:> [AbstractLCD]
[I2CAIP31068TextLCD] -:> [AbstractTextLCD]
[I2CPCF8574TextLCD] -:> [AbstractTextLCD]
[I2CRGBTextLCD] -:> [AbstractTextLCD]
[PPITextLCD] -:> [AbstractTextLCD]
[SPIAIP31068TextLCD] -:> [AbstractTextLCD]

[<abstract>AbstractBacklight]
[BinaryBacklight] -:> [AbstractBacklight]
[I2CRGBPWMBacklight] -:> [AbstractBacklight]
[NoneBacklight] -:> [AbstractBacklight]
[PWMBacklight] -:> [AbstractBacklight]
[RGBBinaryBacklight] -:> [AbstractBacklight]
[RGBPWMBacklight] -:> [AbstractBacklight]

[<abstract>AbstractKeyboard]
[AnalogJoystick] -:> [AbstractKeyboard]
[AnalogKeypad] -:> [AbstractKeyboard]
[AnalogMatrix] -:> [AbstractKeyboard]
[DigitalMatrix] -:> [AbstractKeyboard]
[I2CMPR121CapacitiveKeypad] -:> [AbstractKeyboard]
[I2CRGBKeypad] -:> [AbstractKeyboard]
[I2CTTP229CapacitiveKeypad] -:> [AbstractKeyboard]
[JoinedKeyboard] -:> [AbstractKeyboard]
[JoinedKeyboard] o-> 1..* [AbstractKeyboard]
[NoneKeyboard] -:> [AbstractKeyboard]
[RotaryEncoder] -:> [AbstractKeyboard]
[SimpleButton] -:> [AbstractKeyboard]

```
The code of ag-panel can be compiled with Arduino IDE or PlatformIO (Atom or VS Code).
Following libraries might be required:
- LiquidCrystal (887)
- LiquidCrystal_I2C (576)
- AdaFruit_RGBLCDShield (3121)
- Adafruit MPR121 (839)
- Adafruit RGB LCD Shield Library (762)
- TTP229 (6690)
- LiquidCrystal_AIP31068 (6972)
- SoftSPIB (6971)
- pca9633 (6980)
- EspSoftwareSerial (168)
- ESP32 AnalogWrite (5819)

## How to help
Your contributions as code, resources or finances are welcome!
Please contact me directly over e-mail andriy.golovnya@googlemail.com or over [GitHub profile](https://github.com/red-scorp).
Link for [Paypal donations](http://paypal.me/redscorp), which are always welcome.
Thanks in advance!

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
  - [x] Hardware UART (up to 10 if supported)
  - [x] USB Virtual UART (for SAMD, SAM and STM32 platforms)
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
- [ ] AVR SAMD and SAM (in test)
- [ ] ESP32 and ESP8266 (to be tested)
- [ ] STM32 (in test)
- [ ] RISC-V (planned)

Basic class diagram is shown below:

```nomnoml

#fill: #eee
#background: transparent
#font: Calibri
#.abstract: fill=#fff
#.note: fill=#ffd

[<abstract>AbstractBacklight||
  +SetOn()
  +SetBrightness()
  +SetRGB()
  -Init()
  -Exit()
]
[AbstractBacklight] <:-- [BinaryBacklight]
[AbstractBacklight] <:-- [I2CRGBPWMBacklight]
[AbstractBacklight] <:-- [NoneBacklight]
[AbstractBacklight] <:-- [PWMBacklight]
[AbstractBacklight] <:-- [RGBBinaryBacklight]
[AbstractBacklight] <:-- [RGBPWMBacklight]

[<abstract>AbstractTextLCD|
  *m_Backlight
  *m_Columns
  *m_Rows|
  +SetBacklight()
  +Clear()
  +SetCursor()
  +Print()
  +GetColumns()
  +GetRows()
  +Write()
  +Command()
  -Init()
  -Exit()
]
[AbstractLCD] <:- [AbstractTextLCD]
[AbstractTextLCD] <:-- [I2CAIP31068TextLCD]
[AbstractTextLCD] <:-- [I2CPCF8574TextLCD]
[AbstractTextLCD] <:-- [I2CRGBTextLCD]
[AbstractTextLCD] <:-- [PPITextLCD]
[AbstractTextLCD] <:-- [SPIAIP31068TextLCD]

[<abstract>AbstractLCD|
  *m_Backlight
  *m_Columns
  *m_Rows|
  +SetBacklight()
  +Clear()
  +SetCursor()
  +Print()
  +GetColumns()
  +GetRows()
  -Init()
  -Exit()
]
[AbstractLCD] o-> 1 [AbstractBacklight]

[<abstract>AbstractUART|
  *m_BaudRate|
  +PutCh()
  +GetCh()
  +Prefill()
  +Available()
  +GetBaudRate()
  +PutStr()
  -Init()
  -Exit()
]
[AbstractUART] <:-- [BufferedUART]
[BufferedUART] o-> 1 [AbstractUART]
[BufferedUART] -- [<note>Uses another UART class and implements an extra buffer for it]
[AbstractUART] <:-- [HardwareUART]
[AbstractUART] <:-- [NoneUART]
[AbstractUART] <:-- [SoftwareUART]
[AbstractUART] <:-- [USBVirtualUART]
[AbstractUART] <:-- [TextLoggingUART]
[TextLoggingUART] o-> 2 [AbstractUART]
[TextLoggingUART] -- [<note>Uses first UART as transparent input/output and second UART for logging of trafic in text form]

[<abstract>AbstractKeyboard||
  +GetKey()
  +GetKeyCount()
  -Init()
  -Exit()
]
[AbstractKeyboard] <:-- [AnalogJoystick]
[AbstractKeyboard] <:-- [AnalogKeypad]
[AbstractKeyboard] <:-- [AnalogMatrix]
[AbstractKeyboard] <:-- [DigitalMatrix]
[AbstractKeyboard] <:-- [I2CMPR121CapacitiveKeypad]
[AbstractKeyboard] <:-- [I2CRGBKeypad]
[AbstractKeyboard] <:-- [I2CTTP229CapacitiveKeypad]
[AbstractKeyboard] <:-- [JoinedKeyboard]
[JoinedKeyboard] o-> 1..* [AbstractKeyboard]
[JoinedKeyboard] -- [<note>Combines several keyboards and presents them as a single keyboard]
[AbstractKeyboard] <:-- [NoneKeyboard]
[AbstractKeyboard] <:-- [RotaryEncoder]
[AbstractKeyboard] <:-- [SimpleButton]

[<abstract>AbstractProtocol|
  *m_UART
  *m_LCD
  *m_Keyboard|
  +Loop()
  +Yield()
  -Init()
  -Exit()
]
[AbstractProtocol] o-> 1 [AbstractLCD]
[AbstractProtocol] o-> 1 [AbstractUART]
[AbstractProtocol] o-> 1 [AbstractKeyboard]
[AbstractProtocol] <:-- [LoSPanelProtocol]
[AbstractProtocol] <:-- [RawSerialProtocol]

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

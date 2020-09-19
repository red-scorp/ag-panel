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

[UML diagram online on nomnoml.com](https://www.nomnoml.com/#view/%23fill%3A%20%23eee%0A%23background%3A%20transparent%0A%23font%3A%20Calibri%0A%23.abstract%3A%20fill%3D%23fff%0A%23.note%3A%20fill%3D%23ffd%0A%0A%5B%3Cabstract%3EAbstractBacklight%7C%7C%0A%20%20%2BSetOn()%0A%20%20%2BSetBrightness()%0A%20%20%2BSetRGB()%0A%20%20-Init()%0A%20%20-Exit()%0A%5D%0A%5BAbstractBacklight%5D%20%3C%3A--%20%5BBinaryBacklight%5D%0A%5BAbstractBacklight%5D%20%3C%3A--%20%5BI2CRGBPWMBacklight%5D%0A%5BAbstractBacklight%5D%20%3C%3A--%20%5BNoneBacklight%5D%0A%5BAbstractBacklight%5D%20%3C%3A--%20%5BPWMBacklight%5D%0A%5BAbstractBacklight%5D%20%3C%3A--%20%5BRGBBinaryBacklight%5D%0A%5BAbstractBacklight%5D%20%3C%3A--%20%5BRGBPWMBacklight%5D%0A%0A%5B%3Cabstract%3EAbstractTextLCD%7C%0A%20%20*m_Backlight%0A%20%20*m_Columns%0A%20%20*m_Rows%7C%0A%20%20%2BSetBacklight()%0A%20%20%2BClear()%0A%20%20%2BSetCursor()%0A%20%20%2BPrint()%0A%20%20%2BGetColumns()%0A%20%20%2BGetRows()%0A%20%20%2BWrite()%0A%20%20%2BCommand()%0A%20%20-Init()%0A%20%20-Exit()%0A%5D%0A%5BAbstractLCD%5D%20%3C%3A-%20%5BAbstractTextLCD%5D%0A%5BAbstractTextLCD%5D%20%3C%3A--%20%5BI2CAIP31068TextLCD%5D%0A%5BAbstractTextLCD%5D%20%3C%3A--%20%5BI2CPCF8574TextLCD%5D%0A%5BAbstractTextLCD%5D%20%3C%3A--%20%5BI2CRGBTextLCD%5D%0A%5BAbstractTextLCD%5D%20%3C%3A--%20%5BPPITextLCD%5D%0A%5BAbstractTextLCD%5D%20%3C%3A--%20%5BSPIAIP31068TextLCD%5D%0A%0A%5B%3Cabstract%3EAbstractLCD%7C%0A%20%20*m_Backlight%0A%20%20*m_Columns%0A%20%20*m_Rows%7C%0A%20%20%2BSetBacklight()%0A%20%20%2BClear()%0A%20%20%2BSetCursor()%0A%20%20%2BPrint()%0A%20%20%2BGetColumns()%0A%20%20%2BGetRows()%0A%20%20-Init()%0A%20%20-Exit()%0A%5D%0A%5BAbstractLCD%5D%20o-%3E%201%20%5BAbstractBacklight%5D%0A%0A%5B%3Cabstract%3EAbstractUART%7C%0A%20%20*m_BaudRate%7C%0A%20%20%2BPutCh()%0A%20%20%2BGetCh()%0A%20%20%2BPrefill()%0A%20%20%2BAvailable()%0A%20%20%2BGetBaudRate()%0A%20%20%2BPutStr()%0A%20%20-Init()%0A%20%20-Exit()%0A%5D%0A%5BAbstractUART%5D%20%3C%3A--%20%5BBufferedUART%5D%0A%5BBufferedUART%5D%20o-%3E%201%20%5BAbstractUART%5D%0A%5BBufferedUART%5D%20--%20%5B%3Cnote%3EUses%20another%20UART%20class%20and%20implements%20an%20extra%20buffer%20for%20it%5D%0A%5BAbstractUART%5D%20%3C%3A--%20%5BHardwareUART%5D%0A%5BAbstractUART%5D%20%3C%3A--%20%5BNoneUART%5D%0A%5BAbstractUART%5D%20%3C%3A--%20%5BSoftwareUART%5D%0A%5BAbstractUART%5D%20%3C%3A--%20%5BUSBVirtualUART%5D%0A%5BAbstractUART%5D%20%3C%3A--%20%5BTextLoggingUART%5D%0A%5BTextLoggingUART%5D%20o-%3E%202%20%5BAbstractUART%5D%0A%5BTextLoggingUART%5D%20--%20%5B%3Cnote%3EUses%20first%20UART%20as%20transparent%20input%2Foutput%20and%20second%20UART%20for%20logging%20of%20trafic%20in%20text%20form%5D%0A%0A%5B%3Cabstract%3EAbstractKeyboard%7C%7C%0A%20%20%2BGetKey()%0A%20%20%2BGetKeyCount()%0A%20%20-Init()%0A%20%20-Exit()%0A%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BAnalogJoystick%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BAnalogKeypad%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BAnalogMatrix%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BDigitalMatrix%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BI2CMPR121CapacitiveKeypad%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BI2CRGBKeypad%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BI2CTTP229CapacitiveKeypad%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BJoinedKeyboard%5D%0A%5BJoinedKeyboard%5D%20o-%3E%201..*%20%5BAbstractKeyboard%5D%0A%5BJoinedKeyboard%5D%20--%20%5B%3Cnote%3ECombines%20several%20keyboards%20and%20presents%20them%20as%20a%20single%20keyboard%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BNoneKeyboard%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BRotaryEncoder%5D%0A%5BAbstractKeyboard%5D%20%3C%3A--%20%5BSimpleButton%5D%0A%0A%5B%3Cabstract%3EAbstractProtocol%7C%0A%20%20*m_UART%0A%20%20*m_LCD%0A%20%20*m_Keyboard%7C%0A%20%20%2BLoop()%0A%20%20%2BYield()%0A%20%20-Init()%0A%20%20-Exit()%0A%5D%0A%5BAbstractProtocol%5D%20o-%3E%201%20%5BAbstractLCD%5D%0A%5BAbstractProtocol%5D%20o-%3E%201%20%5BAbstractUART%5D%0A%5BAbstractProtocol%5D%20o-%3E%201%20%5BAbstractKeyboard%5D%0A%5BAbstractProtocol%5D%20%3C%3A--%20%5BLoSPanelProtocol%5D%0A%5BAbstractProtocol%5D%20%3C%3A--%20%5BRawSerialProtocol%5D)

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

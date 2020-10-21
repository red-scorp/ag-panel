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
- [x] AVR SAMD and SAM
- [ ] ESP32 and ESP8266 (to be tested)
- [x] STM32
- [ ] RISC-V (planned)

Basic class diagram is shown below:

![UML diagram generated from DOT below](/img/class_diagram.png)

[UML diagram online on magjac.com](http://magjac.com/graphviz-visual-editor/?dot=digraph%20class_diagram%20%7B%0A%0A%20%20%20%20node%20%5B%0A%20%20%20%20%20%20%20%20shape%20%3D%20record%0A%20%20%20%20%5D%0A%20%20%20%20compound%20%3D%20true%0A%0A%20%20%20%20%2F%2A%20Header%20with%20version%20information%20%2A%2F%0A%20%20%20%20main_note%20%5B%0A%20%20%20%20%20%20%20%20shape%20%3D%20note%0A%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20fillcolor%20%3D%20yellow%0A%20%20%20%20%20%20%20%20label%20%3D%20%22AG-Panel%20Project%20Class%20Diagramm%20v0.2a%5Cn%28C%29%202020%20Andriy%20Golovnya%5CnAuthor%3A%20Andriy%20Golovnya%20%28andriy.golovnya%40googlemail.com%29%22%0A%20%20%20%20%5D%0A%0A%20%20%20%20%2F%2A%20Backlights%20group%20of%20classes%20%2A%2F%0A%20%20%20%20subgraph%20cluster_backlights%20%7B%0A%20%20%20%20%20%20%20%20node%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20%22pink%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20style%20%3D%20dotted%0A%20%20%20%20%20%20%20%20label%20%3D%20%22Backlights%22%0A%20%20%20%20%20%20%20%20AbstractBacklight%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22%7B%5C%3Cabstract%5C%3EAbstractBacklight%7C%7C%2BSetOn%28%29%5Cn%2BSetBrightness%28%29%5Cn%2BSetRGB%28%29%5Cn-Init%28%29%5Cn-Exit%28%29%7D%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20BinaryBacklight%20-%3E%20AbstractBacklight%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20I2CRGBPWMBacklight%20-%3E%20AbstractBacklight%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20NoneBacklight%20-%3E%20AbstractBacklight%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20PWMBacklight%20-%3E%20AbstractBacklight%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20RGBBinaryBacklight%20-%3E%20AbstractBacklight%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20RGBPWMBacklight%20-%3E%20AbstractBacklight%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%7D%0A%0A%20%20%20%20%2F%2A%20LCDs%20group%20of%20classes%20%2A%2F%0A%20%20%20%20subgraph%20cluster_lcds%20%7B%0A%20%20%20%20%20%20%20%20node%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20%22lightblue%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20style%20%3D%20dotted%0A%20%20%20%20%20%20%20%20label%20%3D%20%22LCDs%22%0A%20%20%20%20%20%20%20%20AbstractLCD%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22%7B%5C%3Cabstract%5C%3EAbstractLCD%7C%2Am_Backlight%5Cn%2Am_Columns%5Cn%2Am_Rows%7C%2BSetBacklight%28%29%5Cn%2BClear%28%29%5Cn%2BSetCursor%28%29%5Cn%2BPrint%28%29%5Cn%2BGetColumns%28%29%5Cn%2BGetRows%28%29%5Cn-Init%28%29%5Cn-Exit%28%29%7D%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20AbstractTextLCD%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22%7B%5C%3Cabstract%5C%3EAbstractTextLCD%7C%2Am_Backlight%5Cn%2Am_Columns%5Cn%2Am_Rows%7C%2BSetBacklight%28%29%5Cn%2BClear%28%29%5Cn%2BSetCursor%28%29%5Cn%2BPrint%28%29%5Cn%2BGetColumns%28%29%5Cn%2BGetRows%28%29%5Cn%2BWrite%28%29%5Cn%2BCommand%28%29%5Cn-Init%28%29%5Cn-Exit%28%29%7D%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20AbstractTextLCD%20-%3E%20AbstractLCD%20%5Bstyle%20%3D%20solid%5D%0A%20%20%20%20%20%20%20%20I2CAIP31068TextLCD%20-%3E%20AbstractTextLCD%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20I2CPCF8574TextLCD%20-%3E%20AbstractTextLCD%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20I2CRGBTextLCD%20-%3E%20AbstractTextLCD%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20PPITextLCD%20-%3E%20AbstractTextLCD%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20SPIAIP31068TextLCD%20-%3E%20AbstractTextLCD%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%7D%0A%0A%20%20%20%20%2F%2A%20UARTSs%20group%20of%20classes%20%2A%2F%0A%20%20%20%20subgraph%20cluster_uarts%20%7B%0A%20%20%20%20%20%20%20%20node%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20%22cyan%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20style%20%3D%20dotted%0A%20%20%20%20%20%20%20%20label%20%3D%20%22UARTs%22%0A%20%20%20%20%20%20%20%20AbstractUART%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22%7B%5C%3Cabstract%5C%3EAbstractUART%7C%2Am_BaudRate%7C%2BPutCh%28%29%5Cn%2BGetCh%28%29%5Cn%2BPrefill%28%29%5Cn%2BAvailable%28%29%5Cn%2BGetBaudRate%28%29%5Cn%2BPutStr%28%29%5Cn-Init%28%29%5Cn-Exit%28%29%7D%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20BufferedUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20BufferedUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20ediamond%2C%20headlabel%20%3D%20%221%22%5D%0A%20%20%20%20%20%20%20%20BufferedUART%20-%3E%20note_for_BufferedUART%20%5Bstyle%20%3D%20dashed%2C%20dir%20%3D%20none%5D%0A%20%20%20%20%20%20%20%20HardwareUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20NoneUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20SoftwareUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20USBVirtualUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20TextLoggingUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20TextLoggingUART%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20ediamond%2C%20headlabel%20%3D%20%222%22%5D%0A%20%20%20%20%20%20%20%20TextLoggingUART%20-%3E%20note_for_TextLoggingUART%20%5Bstyle%20%3D%20dashed%2C%20dir%20%3D%20none%5D%0A%20%20%20%20%20%20%20%20%2F%2A%20UARTs%20Notes%20%2A%2F%0A%20%20%20%20%20%20%20%20note_for_BufferedUART%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20shape%20%3D%20note%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20yellow%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22Uses%20another%20UART%5Cnclass%20and%20implements%5Cnan%20extra%20buffer%20for%20it%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20note_for_TextLoggingUART%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20shape%20%3D%20note%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20yellow%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22Uses%20first%20UART%20as%5Cntransparent%20input%2Foutput%5Cnand%20second%20UART%20for%20logging%5Cnof%20trafic%20in%20text%20form%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%7D%0A%0A%20%20%20%20%2F%2A%20Keyboards%20group%20of%20classes%20%2A%2F%0A%20%20%20%20subgraph%20cluster_keyboards%20%7B%0A%20%20%20%20%20%20%20%20node%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20%22magenta%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20style%20%3D%20dotted%0A%20%20%20%20%20%20%20%20label%20%3D%20%22Keyboards%22%0A%20%20%20%20%20%20%20%20AbstractKeyboard%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22%7B%5C%3Cabstract%5C%3EAbstractKeyboard%7C%7C%2BGetKey%28%29%5Cn%2BGetKeyCount%28%29%5Cn-Init%28%29%5Cn-Exit%28%29%7D%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20AnalogJoystick%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20AnalogKeypad%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20AnalogMatrix%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20DigitalMatrix%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20I2CMPR121CapacitiveKeypad%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20I2CRGBKeypad%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20I2CTTP229CapacitiveKeypad%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20JoinedKeyboard%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20JoinedKeyboard%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20ediamond%2C%20headlabel%20%3D%20%221..%2A%22%5D%0A%20%20%20%20%20%20%20%20JoinedKeyboard%20-%3E%20note_for_JoinedKeyboard%20%5Bstyle%20%3D%20dashed%2C%20dir%20%3D%20none%5D%0A%20%20%20%20%20%20%20%20NoneKeyboard%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20RotaryEncoder%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20SimpleButton%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20%2F%2A%20Keybords%20notes%20%2A%2F%0A%20%20%20%20%20%20%20%20note_for_JoinedKeyboard%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20shape%20%3D%20note%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20yellow%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22Combines%20several%20keyboards%5Cnand%20presents%20them%20as%5Cna%20single%20keyboard%20unit%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%7D%0A%0A%20%20%20%20%2F%2A%20Protocols%20group%20of%20classes%20%2A%2F%0A%20%20%20%20subgraph%20cluster_protocols%20%7B%0A%20%20%20%20%20%20%20%20node%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20%20%20%20%20fillcolor%20%3D%20%22antiquewhite%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20style%20%3D%20dotted%0A%20%20%20%20%20%20%20%20label%20%3D%20%22Protocols%22%0A%20%20%20%20%20%20%20%20AbstractProtocol%20%5B%0A%20%20%20%20%20%20%20%20%20%20%20%20label%20%3D%20%22%7B%5C%3Cabstract%5C%3EAbstractProtocol%7C%2Am_UART%5Cn%2Am_LCD%5Cn%2Am_Keyboard%7C%2BLoop%28%29%5Cn%2BYield%28%29%5Cn-Init%28%29%5Cn-Exit%28%29%7D%22%0A%20%20%20%20%20%20%20%20%5D%0A%20%20%20%20%20%20%20%20LoSPanelProtocol%20-%3E%20AbstractProtocol%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%20%20%20%20RawSerialProtocol%20-%3E%20AbstractProtocol%20%5Bstyle%20%3D%20dashed%5D%0A%20%20%20%20%7D%0A%0A%20%20%20%20%2F%2A%20Relationships%20of%20main%20classes%20%2A%2F%0A%20%20%20%20AbstractLCD%20-%3E%20AbstractBacklight%20%5Bstyle%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20ediamond%2C%20headlabel%20%3D%20%221%22%5D%0A%20%20%20%20AbstractProtocol%20-%3E%20AbstractLCD%20%5Bstyle%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20ediamond%2C%20headlabel%20%3D%20%221%22%5D%0A%20%20%20%20AbstractProtocol%20-%3E%20AbstractUART%20%5Bstyle%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20ediamond%2C%20headlabel%20%3D%20%221%22%5D%0A%20%20%20%20AbstractProtocol%20-%3E%20AbstractKeyboard%20%5Bstyle%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20ediamond%2C%20headlabel%20%3D%20%221%22%5D%0A%0A%20%20%20%20main%20%5B%0A%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20fillcolor%20%3D%20%22crimson%22%0A%20%20%20%20%20%20%20%20label%20%3D%20%22setup%28%29%20and%20loop%28%29%22%0A%20%20%20%20%5D%0A%20%20%20%20main%20-%3E%20AbstractBacklight%20%5Blhead%20%3D%20cluster_backlights%2C%20style%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20diamond%2C%20headlabel%20%3D%20%221%22%5D%0A%20%20%20%20main%20-%3E%20AbstractLCD%20%5Blhead%20%3D%20cluster_lcds%2C%20style%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20diamond%2C%20headlabel%20%3D%20%221%22%5D%0A%20%20%20%20main%20-%3E%20AbstractKeyboard%20%5Blhead%20%3D%20cluster_keyboards%2C%20style%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20diamond%2C%20headlabel%20%3D%20%221%22%5D%0A%20%20%20%20main%20-%3E%20AbstractProtocol%20%5Blhead%20%3D%20cluster_protocols%2C%20style%20%3D%20solid%2C%20dir%20%3D%20both%2C%20arrowhead%20%3D%20open%2C%20arrowtail%20%3D%20diamond%2C%20headlabel%20%3D%20%221%22%5D%0A%0A%20%20%20%20main%20-%3E%20note_for_main%20%5Bstyle%20%3D%20dashed%2C%20dir%20%3D%20none%5D%0A%20%20%20%20note_for_main%20%5B%0A%20%20%20%20%20%20%20%20shape%20%3D%20note%0A%20%20%20%20%20%20%20%20style%20%3D%20filled%0A%20%20%20%20%20%20%20%20fillcolor%20%3D%20yellow%0A%20%20%20%20%20%20%20%20label%20%3D%20%22Create%20instances%20of%5Cnproper%20classes%20based%20on%5Cnuser%20defined%20configuration%2C%5Cnlinks%20all%20classes%20together%5Cnand%20starts%20the%20protocol%20execution%22%0A%20%20%20%20%5D%0A%7D%0A)

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

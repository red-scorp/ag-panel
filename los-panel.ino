// https://www.milesburton.com/USD_LCD_Display_(HD44780)_Running_on_Linux_via_Arduino
// https://mlf.home.xs4all.nl/los/

// include the library code:
#include <LiquidCrystal.h>

#define FW_VERSION          __TIME__ " " __DATE__

#define LCD_PIN_RS          12
#define LCD_PIN_RW          11
#define LCD_PIN_ENABLE      10
#define LCD_PIN_BACKLIGHT   9

#define LCD_PIN_D4          5
#define LCD_PIN_D5          4
#define LCD_PIN_D6          3
#define LCD_PIN_D7          2

#define LCD_ROWS            2
#define LCD_COLS            16

#define LOS_INSTRUCTION     0xFE
#define LOS_KEYPAD          0xFE
#define LOS_BACKLIGHT       0xFD

#define LOS_BACKLIGHT_INIT  0x20
#define LOS_BACKLIGHT_OFF   0x00
#define LOS_BACKLIGHT_ON    0xFF

#define LOG_UART_BOD        9600

LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
  LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);

void setup() { 

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LCD_PIN_BACKLIGHT, OUTPUT);
  Serial.begin(LOG_UART_BOD);

  digitalWrite(LED_BUILTIN, HIGH);
  analogWrite(LCD_PIN_BACKLIGHT, LOS_BACKLIGHT_INIT);

  lcd.begin(LCD_ROWS, LCD_COLS);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LoS-Panel Ready...");
  lcd.setCursor(0, 1);
  lcd.print(FW_VERSION);

  digitalWrite(LED_BUILTIN, LOW);
}

byte serial_getch() {

  while(Serial.available() == 0) {
//    delay(10);
  }

  return Serial.read();
}

void loop() {

  byte rxbyte;

  rxbyte = serial_getch();

  switch(rxbyte) {

  case LOS_INSTRUCTION:
    lcd.command(serial_getch());
    break;

  case LOS_BACKLIGHT:
//    digitalWrite(LED_BUILTIN, HIGH);
    analogWrite(LCD_PIN_BACKLIGHT, serial_getch());
    break;

  default:
    lcd.write(rxbyte);
    break;
  }

  // TODO: add check of keyboard pins and send data to pc
}

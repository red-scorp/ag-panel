// https://www.milesburton.com/USD_LCD_Display_(HD44780)_Running_on_Linux_via_Arduino
// https://mlf.home.xs4all.nl/los/

// include the library code:
#include <LiquidCrystal.h>

#define FW_VERSION        __TIME__ " " __DATE__

// these constants won't change.  But you can change the size of
// your LCD using them:
#define LCD_ROWS          2
#define LCD_COLS          16

#define LOS_INSTRUCTION   0xFE
#define LOS_KEYPAD        0xFE
#define LOS_BACKLIGHT     0xFD

#define LOS_BACKLIGHT_OFF 0x00
#define LOS_BACKLIGHT_ON  0xFF

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
// RS, RW, Enable, 4,5,6,7 (Refer to the back of your LCD for details)

void setup() { 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  // set up the LCD's number of rows and columns: 
  digitalWrite(LED_BUILTIN, HIGH);
  analogWrite(9, 25);
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

  // read the incoming byte:
  return Serial.read();
}

void loop() {

  byte rxbyte;

  rxbyte = serial_getch(); // Fetch byte

  switch(rxbyte) {

  case LOS_INSTRUCTION:
    lcd.command(serial_getch());
    break;

  case LOS_BACKLIGHT:
    digitalWrite(LED_BUILTIN, HIGH);
    analogWrite(9, serial_getch());
    break;

  default:
    lcd.write(rxbyte);
    break;
  }
}

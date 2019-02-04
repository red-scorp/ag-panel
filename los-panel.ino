// https://www.milesburton.com/USD_LCD_Display_(HD44780)_Running_on_Linux_via_Arduino
// https://mlf.home.xs4all.nl/los/

// include the library code:
#include <LiquidCrystal.h>

#define FW_NAME             "ALoS" /* Arduino LCD over Serial Panel */
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

#define UART_BOD            9600
#define UART_BUF_SIZE       128

LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
  LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);

byte uart_buf[UART_BUF_SIZE] = {0};
word uart_buf_filled = 0;

void setup() { 

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LCD_PIN_BACKLIGHT, OUTPUT);
  Serial.begin(UART_BOD);

  digitalWrite(LED_BUILTIN, HIGH);
  analogWrite(LCD_PIN_BACKLIGHT, LOS_BACKLIGHT_INIT);

  lcd.begin(LCD_ROWS, LCD_COLS);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(FW_NAME " Ready...");
  lcd.setCursor(0, 1);
  lcd.print(FW_VERSION);

  digitalWrite(LED_BUILTIN, LOW);
}

byte serial_fill_buffer() {

  while(uart_buf_filled < UART_BUF_SIZE && Serial.available() != 0) {
    byte rxbyte = Serial.read();
    uart_buf[uart_buf_filled++] = rxbyte;
  }

  return uart_buf_filled;
}

byte serial_push_buffer() {

  byte top_byte = uart_buf[0];

  for(word i = 1; i < uart_buf_filled; i++) {
    uart_buf[i - 1] = uart_buf[i];
  }

  uart_buf_filled--;
  return top_byte;
}

byte serial_getch() {

  while(serial_fill_buffer() == 0) {
  }

  return serial_push_buffer();
}

void loop() {

  byte rxbyte = serial_getch();

  switch(rxbyte) {

  case LOS_INSTRUCTION:
    lcd.command(serial_getch());
    break;

  case LOS_BACKLIGHT:
    analogWrite(LCD_PIN_BACKLIGHT, serial_getch());
    break;

  default:
    lcd.write(rxbyte);
    break;
  }

  // TODO: add check of keyboard pins and send data to uart
}

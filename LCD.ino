#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

const int Button = 7;
int ButtonVal;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(Button, INPUT);
}

void loop() {
  ButtonVal = digitalRead(Button);

  if (ButtonVal == LOW) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("OPBMS Smart Home");

    lcd.setCursor(0, 1);
    lcd.print("By:  Yug & Sufal");

    delay(1000);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("  You 're   ");

    lcd.setCursor(0, 1);
    lcd.print("       Welcome   ");

    delay(1000);

    lcd.backlight();
  } else if (ButtonVal == HIGH) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("DO  NOT  DISTURB!");

    lcd.setCursor(0, 1);
    lcd.print("Nobody  At  Home");

    lcd.backlight();
  }

  delay(500);
}

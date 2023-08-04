#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte eye[] = { //eye
  B00000,
  B00000,
  B00110,
  B00110,
  B00110,
  B00110,
  B00000,
  B00000
};
byte mouth[] = { //mouth
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B00000,
  B00000
};

byte smile[] = {
  B00000,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000,
  B00000
};
byte selectLeft[] = {
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B11000
};
byte selectRight[] = {
  B00011,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00011
};
byte water[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11101,
  B11011,
  B01110,
  B00000
};
byte berry[] = {
  B00000,
  B01110,
  B00100,
  B11111,
  B10111,
  B11011,
  B01110,
  B00100
};
byte closedEye[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00111,
  B00000,
  B00000,
  B00000
};
byte hat[] = {
  B00000,
  B00000,
  B01110,
  B01010,
  B11011,
  B11111,
  B00000,
  B00000
};
byte sparkle[] = {
  B00000,
  B00001,
  B00011,
  B01001,
  B11100,
  B01010,
  B00111,
  B00010
};

char s = 97;
void setup() {
  lcd.begin(23, 22);
  lcd.backlight();  
  lcd.createChar(0, eye);
  lcd.createChar(1, smile);
  lcd.createChar(2, selectLeft);
  lcd.createChar(3, selectRight);

}

void loop() {
  lcd.setCursor(6, 0); //eye
  lcd.write(0);
  lcd.setCursor(8, 0); //eye
  lcd.write(0);
  lcd.setCursor(7, 1);
  lcd.write(1); //mouth
  delay(1000);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("_");
  lcd.setCursor(8, 0);
  lcd.print("_");
  lcd.setCursor(7, 1);
  lcd.write(1);
  lcd.setCursor(10,0);
  lcd.print("Z");
  lcd.setCursor(9, 1);
  lcd.print("z");
  delay(1000);
}
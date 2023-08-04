#include <analogWrite.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int redPin = 13;
const int greenPin = 12; 
const int bluePin = 33;
const int buttonPin = 21;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int buttonPushCounter = 0;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button

const int swPin = 15;
const int VrxPin = A0;
const int VryPin = A1;
int selected = 0; 
int xDirection = 0;
int yDirection = 0;
int switchState = 0;
int clickCount = 0;
int mouthCount = 0;
int waterCount;
int hydration = 100;
int lives = 100; 
bool deadStat = false;

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

byte heart[] = {
  B00000,
  B00000,
  B01010,
  B10111,
  B11101,
  B01110,
  B00100,
  B00000
};

byte sparkle[] = {
  B00100,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00100,
  B00000
};

byte smileEye[] = {
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(23, 22);
  lcd.backlight();
  lcd.createChar(0, eye);
  lcd.createChar(1, smile);
  lcd.createChar(2, water);
  lcd.createChar(3, heart);
  lcd.createChar(4, sparkle);
  lcd.createChar(5, smileEye);
  lcd.createChar(6, selectLeft);
  lcd.createChar(7, selectRight);
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
  digitalWrite(swPin, HIGH);
}

void loop() {
  button();
  waterTimer();
  // heartStatus();
  // customEyeButton();
  // customMouthButton();
  joystickTrack();
  if(!deadStat){
    customEyeButton();
    customMouthButton();
  }
  if(deadStat){
    lcd.clear();
    lcd.print("reviving...");
    delay(5000);
    lcd.clear();
    deadStat = false;
    lives = 100;
    hydration = 100;
  }
}

void button(){
  buttonState = digitalRead(buttonPin);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    lcd.clear();
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      Serial.println("off");
    }
  }
  lastButtonState = buttonState;
  if (buttonPushCounter % 2 == 0) {
    digitalWrite(bluePin, HIGH);
    //call the sleeping animation
    sleep();
  } else {
    digitalWrite(bluePin, LOW);
    // awake();
    joystickClick();
  }

}
void awake(int val){
  lcd.setCursor(6, 0); //eye
  lcd.write(val);
  lcd.setCursor(8, 0); //eye
  lcd.write(val);
  switchState = digitalRead(swPin);
  mouthCustom(mouthCount);
  // lcd.setCursor(7, 1);
  // lcd.write(1); //mouth
}

void dead(){
  lcd.setCursor(6, 0);
  lcd.print("x");
  lcd.setCursor(8, 0);
  lcd.print("x");
  lcd.setCursor(7, 1);
  lcd.print("x");  
  lcd.setCursor(0, 0);
  lcd.print("RIP");
}

String mouthOptions[] = {"", "3", "o", "_", "="};

void mouthCustom(int val){
  // awake(clickCount);
  lcd.setCursor(7, 1);
  if(val == 0){
    lcd.write(1);
  }
  else {
    lcd.print(mouthOptions[val]);
  }  
}

void sleep(){
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
}

void waterStatus(int val){
  for(int i = 1; i < val+1; i++){
    lcd.setCursor(i, 0);
    lcd.write(2);    
  }
}
void heartStatus(int val){
  for(int i = 1; i < val+1; i++){
    lcd.setCursor(i, 1);
    lcd.write(3);
  }
}
void waterTimer(){
  if(hydration > 70){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    waterStatus(3);
    heartStatus(3);
  }
  if(hydration < 69 && hydration > 40){
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    waterStatus(2);
    heartStatus(3);
  }
  if(hydration < 40 && hydration > 0){
    digitalWrite(redPin, HIGH);
    delay(100);
    digitalWrite(redPin, LOW);
    waterStatus(1);
    heartStatus(3);
  }
  if(hydration < 0){
    lives -=1;
  }
  if(lives > 70){
    heartStatus(3);
  }
  if(lives < 69 && lives > 40){
    heartStatus(2);    
  }
  if(lives < 40 && lives > 0){
    heartStatus(1);
  }
  if(lives < 0){
    deadStat = true;
  }
}

void customEyeButton(){
  lcd.setCursor(12, 0);
  lcd.print("<");
  lcd.setCursor(13, 0);
  lcd.write(0);
  lcd.setCursor(14, 0);
  lcd.print(">");
}

void customMouthButton(){
  lcd.setCursor(12, 1);
  lcd.print("<");
  lcd.setCursor(13, 1);
  lcd.write(1);
  lcd.setCursor(14, 1);
  lcd.print(">");
}

void joystickTrack(){
  xDirection = analogRead(VryPin);
  xDirection = analogRead(VryPin);
  yDirection = analogRead(VrxPin);
  switchState = digitalRead(swPin);
  if(xDirection == 0 && yDirection == 4095){ //water selected
    selected = 0;
    lcd.clear();
    selectLeftDisplay(0, 0);
    selectRightDisplay(4, 0);
  }
  if(xDirection == 4095 && yDirection == 4095){ //eye selected
    selected = 1;
    lcd.clear();
    selectLeftDisplay(11, 0);
    selectRightDisplay(15, 0);    
  }
  if(xDirection == 4095 && yDirection ==0){
    selected = 2;
    lcd.clear();
    selectLeftDisplay(11, 1);
    selectRightDisplay(15, 1);    
  }
}
void selectLeftDisplay(int x, int y){
  lcd.setCursor(x, y);
  lcd.write(6);
}
void selectRightDisplay(int x, int y){
  lcd.setCursor(x, y);
  lcd.write(7);  
}
void joystickClick(){
  awake(clickCount);
  switchState = digitalRead(swPin);
  if(clickCount > 5){
    clickCount = 0;
  }
  if(mouthCount > 4){
    mouthCount = 0;
  }
  if(waterCount > 3){
    waterCount = 3;
  }
  if(switchState==0 && selected == 0){
    hydration +=5;
  }
  if(switchState != 0 && selected !=0){
    hydration -=1;
  }
  if(switchState == 0 && selected ==1){
    awake(clickCount);
    clickCount++;
  }
  if(switchState == 0 && selected ==2){
    mouthCustom(mouthCount);
    mouthCount++;
    delay(100);
  }
}
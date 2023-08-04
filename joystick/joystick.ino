int joyX = A0;
int joyY = A1;

const int redPin = 32;
const int greenPin = 33; 
const int bluePin = 13;
//digital pin 14 is connected to SW
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);

  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);
  delay(1000);
}

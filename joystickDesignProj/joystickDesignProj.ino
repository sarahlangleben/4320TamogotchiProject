const int swPin = 15;
const int VrxPin = A0;
const int VryPin = A1;

int xDirection =0;
int yDirection = 0;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(swPin, INPUT_PULLUP);
  // digitalWrite(swPin, HIGH);
}

void loop() {
  buttonState = digitalRead(swPin);
  // put your main code here, to run repeatedly:
  Serial.println(buttonState);
}

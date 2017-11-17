int potPin=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val=map(analogRead(potPin),0,1023,0,255);
  Serial.println(val);
  delay(50);
}

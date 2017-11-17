#include <SoftwareSerial.h>
SoftwareSerial my(9, 10);

void setup() {
  Serial.begin(9600);
  my.begin(9600);
  my.print("AT");
  delay(2000);
  my.print("AT + CUSD=1");
  delay(2000);
  my.print("AT + CUSD=1");
  my.print(",*123#" );
  delay(2000);
  my.print("AT+CUSD=1,");
  my.print("2");
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:

}

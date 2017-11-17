const int buzzer = 12; //buzzer to arduino pin 9

 
void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

}

void loop(){
 
   tone(12, 261); //Middle C
  delay(1000);

  tone(12, 277); //C#
  delay(1000);

  tone(12, 294); //D
  delay(1000);
 noTone(12);
 delay(1000);

  tone(12, 311); //D#
  delay(1000);
  noTone(12);
 delay(1000);

  tone(12, 330); //E
  delay(1000);
  noTone(12);
 delay(1000);
  
  tone(12, 349); //F
  delay(1000);
  noTone(12);
 delay(1000);

  tone(12, 370); //F#
  delay(1000);
  noTone(12);
 delay(1000);

  tone(12, 392); //G
  delay(1000);
  noTone(12);
 delay(1000);

  tone(12, 415); //G#
  delay(1000);
  noTone(12);
 delay(1000);

  tone(12, 440); //A
  delay(1000);
  noTone(12);
 delay(1000);
  // put your main code here, to run repeatedly:
}

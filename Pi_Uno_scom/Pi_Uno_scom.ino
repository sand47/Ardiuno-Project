
int ledPin = 8;

void setup(){
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}

void loop(){
if (Serial.available()) {  //is data is received 
  int flag=Serial.read();
light(flag-'0'); // read the number -'0' to convert into ASIC number 
}
delay(500);
}

void light(int n){
switch(n)
{
  case 1:
     digitalWrite(ledPin, HIGH); //ON BUTTON 
     delay(5000);
     break;
  case 2:
     digitalWrite(ledPin, LOW); //OFF BUTTON
     delay(1000);
     break;
  case 3:
     digitalWrite(ledPin, HIGH); // BLINK BUTTON
     delay(1000);
     digitalWrite(ledPin, LOW);
     delay(1000);
     digitalWrite(ledPin, HIGH); // BLINK BUTTON
     delay(500);
     digitalWrite(ledPin, LOW);
     delay(500);
     digitalWrite(ledPin, HIGH); // BLINK BUTTON
     delay(500);
     digitalWrite(ledPin, LOW);
     delay(500);
     break;
 default :
   digitalWrite(ledPin, HIGH); // BLINK BUTTON
     delay(500);
     digitalWrite(ledPin, LOW);
     delay(500);
     digitalWrite(ledPin, HIGH); // BLINK BUTTON
     delay(500);
     digitalWrite(ledPin, LOW);
     delay(500);
       
         
}

}

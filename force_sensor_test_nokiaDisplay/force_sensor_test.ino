int pressurePin1 = A0;
/*int pressurePin2 = A1;
int pressurePin3 = A2;
int pressurePin4 = A3;*/
int force1;
//,force2,force3,force4;

void setup() {
  Serial.begin(9600);
  //digitalWrite(12,LOW);
}
void loop() {
 delay(1000); 
 force1 = analogRead(pressurePin1);
 /*force2 = analogRead(pressurePin2);
 force3 = analogRead(pressurePin3);
 force4 = analogRead(pressurePin4);
*/
  
  Serial.print("front");
  Serial.println(force1);
   /*Serial.print("back");
  Serial.println(force2);
   Serial.print("right");
  Serial.println(force3);
   Serial.print("forward");
  Serial.println(force4);
  */
  Serial.print("----------------------------------------------");
  
}

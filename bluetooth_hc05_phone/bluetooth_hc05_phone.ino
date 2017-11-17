/*
 * 
 * HC05 bluetooth control using phone to on/off or do anything 
 */

int led = 13;
void setup()
{
  Serial.begin(9600);
  
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}
void loop()
{
 if(Serial.available())
 {
   String value = Serial.readStringUntil('\n');
   Serial.println(value);
   if(value == "*hello#")
   {
     digitalWrite(led,HIGH);
   }
   else if(value == "*1#") 
   {
     digitalWrite(led,LOW);
   }
  
 }
}

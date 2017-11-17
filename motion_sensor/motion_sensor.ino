int pir=7;


void setup() {
  // put your setup code here, to run once:
pinMode(pir,INPUT);
Serial.begin(9600);
for(int i=0;i<60;i++)
{
  delay(1000);
}
  Serial.println("Done calibrating");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pir))
  {
    Serial.println("1");
    delay(10000);
  }
  else
  {
    Serial.println("0");
    
    }

    //delay(500);
}

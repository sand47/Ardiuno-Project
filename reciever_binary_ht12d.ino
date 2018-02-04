int ledPin[] = {2,3,4,5};

void setup()
{
  Serial.begin(9600);
  for (int i=0;i<4;i++)
  {
    pinMode(ledPin[i], INPUT);
  }
}
bool c[4];
void loop() 
{
  for(int i=0;i<4;i++)
  {
    c[i]=digitalRead(i+2);
    Serial.println(c[i]);
    
  }
  Serial.println();
  delay(500);
  for(int j=0;j<4;j++)
  {
    c[j]=false;
  }
}





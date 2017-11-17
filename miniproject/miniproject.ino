//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(9, 10); 

int led =7;
int motor =8;
int sensor =6;

void setup() {
  //mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(sensor,INPUT);
  for(int i = 0; i < 15; i++){
      delay(1000);
    }
}

void loop() {

  if(Serial.available()>0)
  {
    char c = Serial.read();
    switch(c)
    {
      case 'a':digitalWrite(led,HIGH); break;
      case 'b':digitalWrite(led,LOW); break;
      case 'c':digitalWrite(motor,HIGH); break;
      case 'd':digitalWrite(motor,LOW); break;
    }
  }
  if(digitalRead(sensor))
  {
   // SendMessage();  
   //digitalWrite(led,HIGH);
   Serial.print("ji");
   delay(1000); 
  }

}
/*
void SendMessage()
 
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918248737320\"\r"); // Replace x with mobile number
  delay(200);
  mySerial.println("Alert someone opened the gate");// The SMS text you want to send
  mySerial.println((char)26);// ASCII code of CTRL+Z
  //Serial.println("first over");
  //SendMessage1();    
}*/

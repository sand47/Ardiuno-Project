#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);  //10 to Rx 
int state=1, laststate = 0, count = 0, pirPin = 7;
const int buzzer =12;
int calibrationTime = 60;


void setup() {
  //Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(buzzer,OUTPUT);
  for(int i = 0; i < calibrationTime; i++){
      delay(1000);
    }
  tone(buzzer,277); 
  delay(1000);
  noTone(buzzer);
  delay(1000);   
  //Serial.print("done ");     
 
  }
 void SendMessage()
 
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919345688790\"\r"); // Replace x with mobile number
  delay(200);
  mySerial.println("Alert someone opened the gate");// The SMS text you want to send
  mySerial.println((char)26);// ASCII code of CTRL+Z
  //Serial.println("first over");
  //SendMessage1();    
}
    
 void SendMovement()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919884084224\"\r"); // Replace x with mobile number
  delay(200);
  mySerial.println("Movement alert");// The SMS text you want to send
  mySerial.println((char)26);// ASCII code of CTRL+Z
  //Serial.print("first over");
}
 void SendExit()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919884040029\"\r"); // Replace x with mobile number
  delay(200);
  mySerial.println("High movement call police .exiting project alert");// The SMS text you want to send
  mySerial.println((char)26);// ASCII code of CTRL+Z
  
}

 void Call()
{
mySerial.begin(9600);
delay(2000);
mySerial.println("ATD9345688790;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

}

void loop() {

 if(digitalRead(pirPin) == HIGH)
   {
       
                
       if(state!=laststate)
       {
          if(state==1)
          {
           count++;
           //Serial.println(count);
           switch(count)
           {
             case 1: SendMessage();
                     break;

             case 2: Call();
                     break;

             case 3: SendMovement();
                     break;

             case 4: SendExit();
                     exit(0);

             default: Call();
                      break;
                          
           }
           
          delay(10000);s
          }
        else
        laststate=state;
      }
 }} 

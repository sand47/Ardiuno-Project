#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
        
long unsigned int lowIn;  
long unsigned int pause = 5000;  
boolean lockLow = true;
boolean takeLowTime;  
int pirPin = 6; 
int state,laststate=1,count=0;

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600); 
  pinMode(pirPin, INPUT);
  Serial.println(" Done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
  }

 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919345688790\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Alert someone opened the gate");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 void Call()
{
   Serial.println("Calling through GSM Modem");

// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
delay(2000);
mySerial.println("ATD919345688790;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

Serial.println("Called ATD9345688790");
// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}
  
void loop(){

   if(digitalRead(pirPin) == HIGH)
   {
       if(lockLow)
       {  
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
       
       }
        takeLowTime = true;
        
       if(count>=1){
          Call();
        }   
       else
       {
         SendMessage();
       }
       int state=0;
       Serial.println(state);      
       if(state!=laststate)
       {
          if(state==0)
          {
           count++;
           
           Serial.println(count);
          }
        else
        laststate=state;
       }
       if(count>1)
       {
        count=0;   
       }
      
   } 
   
    
     if(digitalRead(pirPin) == LOW)
     {       
        if(takeLowTime)
        {
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }

     
        
       if(!lockLow && millis() - lowIn > pause)
       {  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
       }
       
     }

  }  



 

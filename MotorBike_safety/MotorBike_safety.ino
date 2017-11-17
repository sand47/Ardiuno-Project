/* Motobike safety is the project theme , the force sensor is kept on the bike ie on front,back and sides of bike.  
 *  On reaching the threshold level of accident the thats is force of about 50kg can be produced in a accident if it happens
 *  The GPS value is read and using GSM the latitude and longitude is sent to his family memebers and friends number already regisitered
 *  Here i have to send mutiple message actually i have to use AT+CMSS but for some reason it not working so i used 2 function call to send message 
 * Step 1 - Wait till u receive a message containing vehicle details 
 * Step 2- Start the loop function ,montior the force sensor values 
 * Step 3- On accident Get GPS value and send mutiple message 
 * Step 4-On sending message the app on that phone understands it and buzzer the sound 
 * Step 5- Send the latitude and longitude value to database via app and in app using this value we can see it on Google Map ..there are many features on the app like calling ambulance , posting on 108 twiiter page , calling road side assitance etc ..
 * 
 * I had problem in the reading the message i sent from my phone since it is not a String it was a " long " i could not using substring to get the vehicle details  
 *  
 */



#include <SoftwareSerial.h>
#include <TinyGPS.h>
SoftwareSerial mySerial(9, 10);
SoftwareSerial gpsSerial(3, 5);
TinyGPS gps;

char incoming_char=0;
int pressurePin1 = A0; //front 
int pressurePin2 = A1; //back
int pressurePin3 = A2; //right
int pressurePin4 = A3; //left
int force1,force2,force3,force4; 
int flag=1;
long lat,lon;


void SendMessage(long lat,long lon)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919941055412\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.print("lat ");
  mySerial.print(lat);
  mySerial.print(",lon ");
  mySerial.print(lon);
  mySerial.print(",TN10CX6666,Name:Harish_Det:Silver_Platina_100cc"); 
  delay(100);
  mySerial.println((char)26);
  delay(1000); 
 
}
void get_gps()
{
  Serial.print("Getting GPS location");
  while(gpsSerial.available()){ // check for gps data
   if(gps.encode(gpsSerial.read()))  // encode gps data
   { 
  
    gps.get_position(&lat,&lon);
    Serial.print("Position: ");
    Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
    Serial.print("lon: ");Serial.println(lon);
    Serial.print("Sending message"); 
    SendMessage(lat,lon);
    
    }  
}
} 

void SendAlert(long lat,long lon)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917358332016\"\r"); // Replace x with mobile number
  delay(1000);
  // send message of predefined detials ..its just a example so i typed it manaully
  mySerial.print("lat "); 
  mySerial.print(lat);
  mySerial.print(",lon ");
  mySerial.print(lon);
  mySerial.print(",TN10CX6666,Name:Harish_Det:Silver_Platina_100cc"); 
  mySerial.println((char)26);
  delay(2000); 
}


void setup()
{
  
  Serial.begin(19200); // for serial monitor
  mySerial.begin(9600); // for GSM shield
  gpsSerial.begin(9600);
  Serial.println("**********************************************************************************************************");
  Serial.println("Ready State TCP-RIDE Enter the data");
  Serial.println("**********************************************************************************************************");  
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(3,LOW);
  mySerial.print("AT+CMGF=1\r");  // set SMS mode to text
  delay(1000);
  mySerial.print("AT+CNMI=2,2,0,0,0\r"); // wait till u recevie the message 
  delay(1000);
  
  while(flag)
 {
    if(mySerial.available() > 0)
    {
      
      incoming_char=mySerial.read(); //Get the character from the cellular serial port.
      Serial.println(incoming_char);
      Serial.print("TN10CX7777,Name:Harish_Det:Silver_Platina_100cc");
      flag=0;
    }
 }
}



void loop()
{
 force1 = analogRead(pressurePin1) ;
 force2 = analogRead(pressurePin2);
 force3 = analogRead(pressurePin3);
 force4 = analogRead(pressurePin4);
 Serial.println(" \n ");
 Serial.print("Front -->  ");
 Serial.println(force1);
 Serial.print("Rear  --> ");
 Serial.println(force2);
 Serial.print("left  --> ");
 Serial.println(force3);
 Serial.print("right --> ");
 Serial.println(force4);
 delay(500);
 Serial.print("----------------------------------------------------------------------------------------------------------");

if(force1<10)
{
   //SendHow("frontside"); // can send how the accident happened but i didt do it 
   Serial.print(" \n");
   Serial.println("Head-on collision ");
   delay(1000);
   
}
else if (force2<10)
{
  //SendHow("backside");
  Serial.print(" \n");
  Serial.println("Rear-end collision ");
  delay(1000);
  }
else if (force3<10)
{
  //SendHow("rightside");
  Serial.print(" \n");
  Serial.println("left side collision ");
  delay(1000);
  }
else if (force4<10)
{
  //SendHow("leftside");
  Serial.print(" \n");
  Serial.println("right side collision ");
  delay(1000);
  
}
if(((force1) ==0)||((force3)==00)||((force4)==0))
{
  get_gps();
  SendAlert(lat,lon);  // sending second message
}  

 delay(4000); // for easy displaying of data 
}



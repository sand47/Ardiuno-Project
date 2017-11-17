
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <string.h>

char incoming_char;
int i;
//String Name,Vehicle_no,Vehicle_det;
int pressurePin1 = A0; //front
int pressurePin2 = A1; //back
int pressurePin3 = A2; //right
int pressurePin4 = A3; //left
int force1,force2,force3,force4; 
long lat,lon; // create variable for latitude and longitude object
int flag=1; 
SoftwareSerial gpsSerial(3, 5); // create gps sensor connection 5 is rx 
SoftwareSerial mySerial(9, 10); //10 is rx 
TinyGPS gps; // create gps object


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919941055412\"\r"); // Replace x with mobile number
  delay(2000);
  //mySerial.print("lat ");+lat+",lon "+lon+",Name:Suriya Vehicle_no:TN O7 AP 4477 Vehicle_det:Black Pulsar 150cc");
  mySerial.print(12.989386);
  mySerial.print(",lon ");
  mySerial.print(80.229669);
  mySerial.print("Name: ");
  mySerial.print(Name);
  mySerial.print(" Vehicle_no: ");
  mySerial.print(Vehicle_no);
  mySerial.print("Vehicle_det: ");
  mySerial.print(Vehicle_det); 
 //lat 12.989386,lon 80.229669
  mySerial.println((char)26);
   
}

void SendPlace(String message)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919941055412\"\r"); // Replace x with mobile number
  delay(2000);
  mySerial.print("High possibilty of ");
  mySerial.print(message);
  mySerial.println((char)26);
   
}

void get_gps()
{
  Serial.print("Getting GPS location");
  delay(5000);
  Serial.print("Position: ");
  Serial.print("lat: ");Serial.print(12.989386);Serial.print(" ");// print latitude
  Serial.print("lon: ");Serial.println(80.229669); 
/*while(gpsSerial.available()){ // check for gps data
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    // display position
    Serial.print("Position: ");
//    12.989386,lon 80.229669
    Serial.print("lat: ");Serial.print(12.989386);Serial.print(" ");// print latitude
    Serial.print("lon: ");Serial.println(80.229669); // print longitude
    SendMessage();
   }
  }  
 */
}
 
void setup(){
  Serial.begin(19200); // connect serial
  gpsSerial.begin(9600); // connect gps sensor
  mySerial.begin(19200);
  mySerial.print("AT+CMGF=1\r");  // set SMS mode to text
  delay(100);
  mySerial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  Serial.println("Ready State TCP-RIDE Enter the data");
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  
  
}

void loop(){
delay(2000);  
   while(flag)
   {
    if(mySerial.available() > 0)
  {
    Serial.print("message arrived");
    incoming_char=mySerial.read();
    Serial.print(incoming_char);
    flag=0;
  } 
   } 
      
   /*     if (incoming_char.substring(0,4) == "Name:") {
            for(i=5;i<15;i++)
            {
              // substring(index) looks for the substring from the index position to the end:
                      if (incoming_char.substring(i) == "Vehicle_no") {
                             break;
                        }
            }
              
              Name=incoming_char.substring(6,i);
        }
    if (incoming_char.substring(i+1,i+12 ) == "Vehicle_no:") {
      
        Vehicle_no=incoming_char.substring(i+13,i+25);
  }
   if (incoming_char.substring(i+26,i+39 ) == "Vehicle_det:") {
        Vehicle_det=incoming_char.substring(i+40,i+55);
        flag=0;
        break;
  }

     */ 
  


 
 force1 = analogRead(pressurePin1);
 force2 = analogRead(pressurePin2);
 force3 = analogRead(pressurePin3);
 force4 = analogRead(pressurePin4);
 Serial.println(force1);
 Serial.println(force2);
 Serial.println(force3);
 Serial.println(force4);
if(((force1) ==0)||((force2) ==0)||((force3) ==0)||((force4) ==0))
{
  get_gps(); 
}  
if(force1==0)
{
   //SendPlace("frontside");
   //SendMessage(lon,lat);
   Serial.print("Head-on collision ");
}
/*else if (force2==0)
{
  SendPlace("backside");
  Serial.print("Rear-end collision ");
}*/
else if (force3>400)
{
  //SendPlace("rightside");
  Serial.print("right side collision ");
}
else if (force4==0)
{
  //SendPlace("leftside");
  Serial.print("Left collision ");
}

  
}



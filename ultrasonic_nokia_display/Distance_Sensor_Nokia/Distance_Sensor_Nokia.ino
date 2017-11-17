#include <LCD5110_Graph.h>

#define echoPin 6 // Echo Pin
#define trigPin 7 // Trigger Pin

LCD5110 lcd(8,9,10,12,11);

extern unsigned char BigNumbers[];
extern uint8_t ui[];

int maximumRange = 250; // Maximum range needed
int minimumRange = 1; // Minimum range needed
long duration, distance; // Duration used to calculate distance


String distanceString = "0";

void setup() {
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 lcd.InitLCD();
 lcd.setFont(BigNumbers);
}

void loop() {
 int stringLength = 0; 
 
 lcd.clrScr();
 lcd.drawBitmap(0, 0, ui, 84, 48);
 distanceString = readSensor();

 stringLength = distanceString.length();
 printDistance(stringLength);
 lcd.update();
 delay(50);
}

void printDistance(int length)
{
  switch(length)
  {
    case 1:  lcd.print(distanceString,38,19); break;
    case 2:  lcd.print(distanceString,24,19); break;
    case 3:  lcd.print(distanceString,10,19); break;
    default:  lcd.print(distanceString,0,19); break;
  }
}

String readSensor()
{
  String distanceS = "0";
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 distance = duration/58.2;
 distanceS = String(distance);
 if(distance>maximumRange || distance<minimumRange)
 {
   distanceS = "---";
 }
 
 delay(50);
 return distanceS;
}



#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int lm1= 24;        //setting up left motor pins
int lm2= 25;
int rm1= 0;        //setting up right motor pins
int rm2= 1;
int e1=13;         //elbow 
int e2=14;
int w1=15;         //wrist
int w2=16;

void Forward()     //Forward
{
  lcd.print(" Moving Forward");
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
  
}

void Stop()        //Stop
 {
  lcd.print("Stopped ");
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}
void Reverse()     //Reverse
{
  lcd.print("Reversing");
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}
void Right()        //Right 
{
  lcd.print("Moving Right");
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}
void Left()         //Left
{
  lcd.print("Moving Left");
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

void ElbowUp()
{
  lcd.print("Elbow up");  
  digitalWrite(e1,1);
  digitalWrite(e2,0);
  delay(500);
}

void ElbowDown()
{
  
  lcd.print("Elbow down");
  digitalWrite(e1,0);
  digitalWrite(e2,1);
  delay(400);
 }
 
void wristOpen()
{
  lcd.print("Wrist up");  
  digitalWrite(w1,1);
  digitalWrite(w2,0);
  delay(500);
}

void wristClose()
{
  
  lcd.print("Wrist down");
  digitalWrite(w1,0);
  digitalWrite(w2,1);
  delay(500);  
 } 
 
 
void setup()
{
   lcd.begin(16,2);
   lcd.clear();
   lcd.print("IRON MAN");
   delay(2000);
   Serial.begin(9600);
   pinMode(lm1,OUTPUT);
   pinMode(lm2,OUTPUT);
   pinMode(rm1,OUTPUT);
   pinMode(rm2,OUTPUT);
   pinMode(e1,OUTPUT);
   pinMode(e2,OUTPUT);
   pinMode(w1,OUTPUT);
   pinMode(w2,OUTPUT);
   
}

void loop()
{
   if(Serial.available())
   {
      lcd.clear();
      
      char c =Serial.read();
      lcd.print(c);
      delay(1000);
      switch (c)
      {
         case 'w':
                  Forward();
               break;
               
         case 'a':
               Left();
               break;
         case 'd':
               Right();
               break;
         
          case 's':
               Reverse();
               break;
         
          case 'c':
               ElbowUp();
               break;
         
         case 'v':
               ElbowDown();
               break;
               
         case 'z':
               wristOpen();
               break;
         
         case 'x':
               wristClose();
               break;
         
      }
   }
      else
       Stop();
   }               

#include <LedControl.h>
void BlueBlink();
void GreenBlink();
void Start();

int DIN = 4;
int CS =  5;
int CLK = 6;
int Button=7;
int Green=8;
int Blue=9;
int randNumber;
int dum=0;

byte x[8]={0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};
byte o[8]={0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
byte one[8]={0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
byte two[8]={0x7C,0x0C,0x0C,0x0C,0x1C,0x20,0x40,0xFF};
byte three[8]={0x1F,0x10,0x10,0x10,0x1F,0x10,0x10,0x1F};
byte blank[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

LedControl lc=LedControl(DIN,CLK,CS,0);

void setup(){
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,10);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
 pinMode(Button, INPUT);
 pinMode(Green, OUTPUT);
 pinMode(Blue, OUTPUT);
 randomSeed(analogRead(0));
 Start();
} 


void loop() 
{  
   
   
   randNumber = random(200,2000); 
  
     printByte(x);
         int buttonState = digitalRead(Button);
          if(buttonState==1)
          { 
            BlueBlink(); 
          }  
    delay(randNumber);
        
     printByte(o);
         buttonState = digitalRead(Button);
         if(buttonState==1)
        {
          GreenBlink();
        } 
    delay(500);
  
}


void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
  
  
} 

void GreenBlink()
{
  
   for(int i=0;i<=3;i++)  
   {
    digitalWrite(Green, HIGH);
    delay(200);
    digitalWrite(Green, LOW);
    delay(200);
    BlinkByte(o);
   } 
      
}

void BlueBlink()
{
  for(int i=0;i<=3;i++)  
  {
    digitalWrite(Blue, HIGH);
    delay(200);
    digitalWrite(Blue, LOW);
    delay(200);
    BlinkByte(x);
  }  
    
}


void  BlinkByte(byte character [])
{
 
      for(int i=0;i<8;i++)
     {
       lc.setRow(0,i,character[i]);
      }
     delay(300);    
     printByte(blank);
      
}  
  
  
void  Start()
{
  
   printByte(three);  
   delay(800);
   printByte(two);
   delay(800);
   printByte(one);
   delay(800);
    
}  
  
  
  
  
  
  
 


















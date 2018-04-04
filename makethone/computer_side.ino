#include<Mouse.h>
#include<Keyboard.h>

int st=1;                                                                       //Status of last arrow key used
int mode=3;                                                                     //Mode 1 - Mouse , 2 - Keyboard , 3 - Disable
int pr=1;
# define mo Serial3                                                             //Define Serial 3 as mo

void setup()
{
   mo.begin(9600);
   Serial.begin(9600);
   pinMode(A0,OUTPUT);                                                          //Set as output pins for led indication
   pinMode(A1,OUTPUT);
}

 void nothing()
{
                                                                                //Blank function Mode 3 - disable
}

void kb(char val)                                                               //Keyboard function for Mode 2 - Keyboard
{
  Keyboard.begin();                                                             //Start Keyboard data transmission
  int y = (int(val))%10;
  if(y==0&&st==2)
  {
   Keyboard.press(216);                                                         //Left key press
     st=1;
   Keyboard.release(216);
  }
  else if(y==9&&st==2)
  {
    Keyboard.press(215);                                                        //Right key press
       st=1;                                                                    
    Keyboard.release(215);
  }
  else if(y==4||y==5)
   st=2;
  Keyboard.end();                                                                //End keyboard transmission
  
}

void mouse(char val)                                                              //Mouse function for Mode 1 - Mouse
{
  Mouse.begin();                                                                  //Mouse begin
  int x = (int(val))/10;
  int y = (int(val))%10;
  x = map(x,0,9,10,-10);
  y = map(y,0,9,-10,10);
  Mouse.move(y,x,0);
  Mouse.end();                                                                     //End mouse 
}

void loop()
{
  while(mo.available())                                                           //Check if data is available
  {
    char a = mo.read();
    
    if(int(a)==120&&pr!=120)                                                      //Check if a mode change has been called
     {                                                                            // with character 120
      if(mode==1)
      mode=2;                                                                     //Cyclically assign modes
      else if(mode==2)
      mode=3;
      else
      mode=1;
     }
     else if(int(a)==121&&pr!=121)                                                         //Check if button click is requeste
   {  Mouse.click();
     delay(500);}     
     //If true click it
     else{
     if(mode==1)
      kb(a);
     else if(mode==2)
      mouse(a);
     else if(mode==3)
      nothing();
     }
     if(mode==3)                                                                    //If mode 3 , turn off all LEDs
     {
       digitalWrite(A0,0);
       digitalWrite(A1,0);
     }
     else if(mode==2)                                                                //For mode 2 turn on one LED
     {
       digitalWrite(A0,1);
       digitalWrite(A1,0);
     }
     else if(mode==1)                                                                 //For mode 1 turn on the other LED
     {
       digitalWrite(A0,0);
       digitalWrite(A1,1);
     }
     pr = int(a);
      
  }
}


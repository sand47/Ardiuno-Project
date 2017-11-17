#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
unsigned long start;
float flag;
int rm1=0;
int rm2=1;
int lm1=24;
int lm2=25;
int l,c1,c2,c3,r;
int tdelay=725;
int fdelay=100;
int buzzer=6;

void Stop()            //stop fn
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}
void forward()        //forward fn
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}
void smallright()    //right for line follower
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}
void smallleft()    //left for line follower
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}
void right()        //differential right
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}
void left()          //differential left
{
   digitalWrite(lm1,0);
   digitalWrite(lm2,1);
   digitalWrite(rm1,1);
   digitalWrite(rm2,0);
}
int eosens()
{
   readsens();
  if(((c1+c2+c3)==1)||((c1+c2+c3)==2))
     return 1;
   else 
     return 0;
}
void readsens()  //reading sensor values
{
  l=digitalRead(26);
  c1=digitalRead(27);
  c2=digitalRead(28);
  c3=digitalRead(29);
  r=digitalRead(30);
  
  /*lcd.print(1);
  lcd.print("--");
  lcd.print(c1);
  lcd.print("--");

  lcd.print(c2);
  lcd.print("--");
  lcd.print(c3);
  lcd.print("--");
  lcd.print(r);
  lcd.print("--");*/
}
void inch()      //inch function
{
  lcd.print("inch function");
  Stop();   //stop
  delay(100);
  forward();    //forward
  delay(650);
  Stop();
  delay(100);
  readsens();     //read sensor values
  lcd.clear();
}
void align()
{
   Stop();       //stop
   delay(500);
   forward();    //forward
   delay(60);
   Stop();
   delay(500);
   lcd.clear();
   readsens();  //read sensor values
}


void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);  //initialize lcd
  lcd.print("MSR with LHR");        
  delay(500);
  lcd.clear();   //clear lcd
  pinMode(lm1,OUTPUT);  //declare output pins
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(buzzer,OUTPUT);
  
  pinMode(26,INPUT);      //decalre input pins
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  pinMode(30,INPUT);
}

//--------------------------------

void loop()

{
  lcd.clear();
  lcd.print("Started"); 
  start=millis();
  if(Serial.available())
  {
   char d= Serial.read();
   if(d=='c')
  { 
   Stop();
   digitalWrite(buzzer,1);
   delay(500);
   digitalWrite(buzzer,0);
   delay(500); 
   digitalWrite(buzzer,1);
   delay(500);
   digitalWrite(buzzer,0); 
  }
  }
 if(((l==0)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==0))||((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))
{
   digitalWrite(buzzer,1);
   delay(800);
   digitalWrite(buzzer,0); 
   delay(800);
   digitalWrite(buzzer,1);
   delay(800);
   digitalWrite(buzzer,0); 
 
} 
  lcd.clear();   //clear lcd
  readsens();   //read sensor values
  lcd.clear();   //clear lcd
  //line follower
  //fwd
  if((l==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))
  {
    
    lcd.print("Forward");
    forward();      //forward
  }
  
  //left
  else if(((l==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1))||((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
  {
    lcd.print("small left");
    smallleft();//small left
    delay(2);
  }
  //right
  else if(((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1)))
  {
    lcd.print("small right");
    smallright();   //small right
    delay(2);
  }
  
  //dead end
  else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
  {
     lcd.print("u turn");
     left();     //U turn
     delay(1400);
  }
  else if(((l==0)&&(c1==0))||((c3==0)&&(r==0)))
  {
      align();   //allign
      //right only and str and ryt
      if(((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0))||((l==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))
      {
        lcd.print("RT/Strt n rt?");
        inch();       //inch
        if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
        {
          lcd.print("right");
          right();      //turn right
        
          delay(tdelay);            //turn delay
        }
        else if((l==1)&&(r==1)&&(eosens()))
        {
          lcd.print("straight");
          forward();           //forward
          delay(fdelay);
        }
      }
      
      //decide left and str left
      else if(((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1)))
      {
        lcd.print("Lft/str n lft ?");
        inch();    //inch
        if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
        {
          lcd.print("left");
          left();          //turn left
          delay(tdelay);                 //turn delay
        }
       else if((l==1)&&(r==1)&&(eosens()))
        {
          lcd.print("left");
          forward();   //turn lrft
          delay(tdelay);              //turn delay
        }
      }
      
      //4 way/T-tint/End of maze
      
      else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
      {
        lcd.print("T/END/4");
        inch();        //inch
       if((l==1)&&(r==1)&&(eosens()))
       {
         lcd.print("4 way");
         forward();      //turn left
         delay(tdelay);             //turn delay
       }
       else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
       {
         lcd.print("T-int"); 
         forward();       //turn left
         delay(tdelay);          //turn delay
       }
       else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
       {
         lcd.print("End of maze");
         digitalWrite(buzzer,1);
         delay(800);
         digitalWrite(buzzer,0); 
         delay(800);
         digitalWrite(buzzer,1);
         delay(800);
         digitalWrite(buzzer,0);
               
         lcd.clear();
         lcd.print("Total time taken");
         delay(400);
         lcd.clear();
         flag=start/1000;
         lcd.print(flag);
          
         while(1)
         {
         
         Stop();

               
         
         }
      }
  }
}
}



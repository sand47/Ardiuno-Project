char reshortn[30];
char directions[30];

#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

int rm1=0;
int rm2=1;
int lm1=24;
int lm2=25;
int l,c1,c2,c3,r;
int i;
int k=0;
int tdelay=725;
int fdelay=100;

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
void printing(char prtdirection[])  //fn to print values on lcd
{
  lcd.clear();
  for(i=0;prtdirection[i]!='E';i++)
  {
    lcd.print(prtdirection[i]);
  }
  delay(2000);
}

void setup()
{
  lcd.begin(16,2);  //initialize lcd
  lcd.print("MSR with RHR");        
  delay(500);
  lcd.clear();   //clear lcd
  pinMode(lm1,OUTPUT);  //declare output pins
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  
  pinMode(26,INPUT);      //decalre input pins
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  pinMode(30,INPUT);
}

//--------------------------------

void loop()
{
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
     delay(1700);
     directions[i]='U';
     i++;
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
          lcd.print("right");
          directions[i]='R';        //store r in array
          i++;
          right();           //forward
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
          lcd.print("right");
          directions[i]='S';   //store L in array
          i++;
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
         directions[i]='R';    //store L into array
         i++;
         right();      //turn left
         delay(tdelay);             //turn delay
       }
       else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
       {
         lcd.print("T-int"); 
         directions[i]='R';   //store L in array
         i++;
         right();       //turn left
         delay(tdelay);          //turn delay
       }
       else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
       {
         lcd.print("End of maze");
         directions[i]='E';
         printing(directions);
         Stop();
         delay(5000);
         lcd.clear();
         replacement(directions);
       }
      }
  }
}


//--------------------------------

void replacement(char shortn[])
{
  lcd.print("Entered Replacement");
  delay(1000);
  lcd.clear();
  
  for(i=0;shortn[i]!='E';i++)
  {
    if(shortn[i]=='U')
    {
      if((shortn[i-1]=='S') && (shortn[i+1]=='R'))    //SUL replaced with XXL
      {
        shortn[i-1]='X';
        shortn[i]='X';
        shortn[i+1]='L';
      }
      else if((shortn[i-1]=='R') && (shortn[i+1]=='R'))    //S=RUR replaced with XXS
      {
        shortn[i-1]='X';
        shortn[i]='X';
        shortn[i+1]='S';
      }
      else if((shortn[i-1]=='R') && (shortn[i+1]=='S'))    //RUS replaced with XXL
      {
        shortn[i-1]='X';
        shortn[i]='X';
        shortn[i+1]='L';
      }
      else if((shortn[i-1]=='R') && (shortn[i+1]=='L'))    //Rul replaced with XXU
      {
        shortn[i-1]='X';
        shortn[i]='X';
        shortn[i+1]='U';
      }
      else if((shortn[i-1]=='L') && (shortn[i+1]=='R'))    //lur replaced with XXU
      {
        shortn[i-1]='X';
        shortn[i]='X';
        shortn[i+1]='U';
      }
      else if((shortn[i-1]=='S') && (shortn[i+1]=='S'))    //SUS replaced with XXU
      {
        shortn[i-1]='X';
        shortn[i]='X';
        shortn[i+1]='U';
      }
    }
  }
  lcd.clear();
  lcd.print("Finished new path");
  delay(1000);
  lcd.print("New : ");
  j=0;
  for(i=0;shortn[i]!='E';i++)    //to eliminate X
  {
    if(shortn[i]!='X')
    {
      reshortn[j]=shortn[i];    //remove the X
      j++;
    }
  }
  reshortn[j]='E';
  lcd.print("SPA = ");
  printing(reshortn);
  delay(1000);
  
  for(i=0;reshortn[i]!='E';i++)
  {
    if(reshortn[i]=='U')
    {
      replacement(reshortn);
    }
  } 
  lcd.print("FINAL =");
  printing(reshortn);
  final();
}


void decisions()
{
  lcd.print("Entered decisions ");
  lcd.clear();
  if(reshortn[k]=='S')
  {
    forward();
    delay(fdelay);
  }
  else if(reshortn[k]=='L')
  {
   left();
   delay(tdelay);   
  } 
    else if(reshortn[k]=='R')
  {
   right();
   delay(tdelay);
  } 
  k++;
}

void final()
{
   lcd.clear();
   lcd.print("Entered final ");
   delay(500);
   while(1)
   {
     lcd.clear();
     readsens();
     if((l==1 )&(c1==1 )&&(c2==0 )&&(c3==1 )&&(r== 1))
     {
       forward();
     }
     else if(((l==1 )&(c1== 0)&&(c2== 1)&&(c3==1 )&&(r==1 ))||((l== 1)&&(c1==0 )&&(c2== 0)&&(c3==1 )&&(r==1 )))
     {
       smallleft();
     } 
      else if(((l==1 )&(c1== 1)&&(c2==1 )&&(c3==0 )&&(r==1 ))||((l==1 )&&(c1==1 )&&(c2==0 )&&(c3==0 )&&(r==1)))
     {
       smallright();
     }
     else  if((l==0 )&(c1==0 )&&(c2==0 )&&(c3== 0)&&(r== 0))
     {
       align();
      if(((l==1 )&(c1==1 )&&(c2==0 )&&(c3==0 )&&(r== 0))||((l==1 )&&(c1==0 )&&(c2==0 )&&(c3== 0)&&(r==0 )))
     {
       inch();
      if((l== 1)&(c1==1 )&&(c2== 1)&&(c3== 1)&&(r==1 ))
     {
       right();
       delay(tdelay);
     }
     else if((l==1 )&&(r==1 )&&(eosens()))
     {
       decisions();
     
     }
     }
     
     else if(((l==0 )&(c1==0 )&&(c2==0 )&&(c3==1 )&&(r==1 ))||((l==0 )&&(c1==0 )&&(c2==0 )&&(c3== 0)&&(r==1 )))
     {
      inch();
     if((l== 1)&(c1==1 )&&(c2==1 )&&(c3== 1)&&(r==1 ))
     {
       lcd.print("= left");
       left();
       delay(tdelay);
     }
     else if((l== 1)&&(r==1 )&&(eosens()))
     {
       lcd.print("= stnlt");
       decisions();
     
     }
   }
     else if((l== 0)&(c1== 0)&&(c2==0 )&&(c3==0 )&&(r== 0))
     {
       inch();
      if((l== 1)&&(r==1 )&&(eosens()))
     {
       decisions();
     }
     else  if((l== 1)&(c1==1 )&&(c2==1 )&&(c3==1 )&&(r==1 ))
     {
       decisions();
     }
     else  if((l== 0)&(c1==0 )&&(c2== 0)&&(c3==0 )&&(r==0 ))
     {
       
       while(1)
       {
       Stop();
       }
     }
           
    }
           
  }
          
 }
     
}

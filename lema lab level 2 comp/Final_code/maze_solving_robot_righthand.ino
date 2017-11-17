
char directions[30];

#include<LiquidCrystal.h>//lcd library

//LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

LiquidCrystal lcd(12,11,5,4,3,2);

int lm1 = 24; // naming motors pins
int lm2 = 25;
int rm1 = 0;
int rm2 = 1;

int l,c1,c2,c3,r; //naming sensor pins
int tdelay=700 ; //turn delay
int fdelay=500; //forward delay to be used when decisions are taken
int i;

void Stop() //stop function
{
    digitalWrite(lm1,0);
    digitalWrite(lm2,0);
    digitalWrite(rm1,0);
    digitalWrite(rm2,0);   
}

void forward()//forward function
{
    digitalWrite(lm1,1);
    digitalWrite(lm2,0);
    digitalWrite(rm1,1);
    digitalWrite(rm2,0);
}

void smallright()//right for line follower
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}

void smallleft()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

void right()
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}

void left()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

int eosens()
{
    readsens();
    if ( (( c1+c2+c3) ==  1) || ((c1+c2+c3) ==  2) )
    return 1;
    else
    return 0;
}

void readsens() //reading the sensor values
{
  
  l=digitalRead(26);
  c1=digitalRead(27);
  c2=digitalRead(28);
  c3=digitalRead(29);
  r=digitalRead(30);
  
  lcd.print(l);
  lcd.print("--");
  lcd.print(c1);
  lcd.print("--");
  lcd.print(c2);
  lcd.print("--");  
  lcd.print(c3);
  lcd.print("--");  
  lcd.print(r);
  lcd.print("--");
  
}

void inch() //inch function
{
  
  lcd.print("Inch Function");
  
  Stop();  //stop
  delay(100);
  
  forward(); //forward
  delay(650);//delay(500);
  
  Stop();  //stop
  delay(100);
  readsens(); //read the values of sensor
  
  
  lcd.clear();

}

 void align()  // align function
 {
   
   Stop(); //stop
   delay(500);
   
   forward(); //forward
   delay(60);
   
   Stop(); //stop
   delay(500);
   
   lcd.clear();
   
   readsens(); //read the values of sensor
 }

void printing(char prtdirection[]) //function to print values on the lcd
{
  
  lcd.clear();
  
  for( i=0;prtdirection[i] != 'E'; i++)
  {
    lcd.print(prtdirection[i]);
  }
  delay(2000);
}


  
void setup()
{
  Serial.begin(9600); //set the bord rate
  
  
  lcd.begin(16,2); // initialize the lcd
  lcd.print("MSR with LHR");
  delay(500);

  lcd.clear(); //clearlcd
  pinMode(lm1,OUTPUT); //declare output pins
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(26,INPUT); //declare input pins
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  pinMode(30,INPUT);

}

void loop()
{
  lcd.clear(); //clear lcd
  
  readsens(); //read sensor values
  lcd.clear(); // clear lcd
  
  
  //line follower
  //fwd
  
  if ( ( l== 1) &&  ( c1== 1) &&  ( c2== 0) &&  ( c3==1 ) &&  ( r==1 )  )
  {
    lcd.print("Forward");
    forward(); //forward
  }
  //left
  else if (   ( ( l== 1) &&  ( c1== 0) &&  ( c2==1 ) &&  ( c3== 1) &&  ( r== 1) )   ||  ( ( l==1 ) &&  ( c1== 0) &&  ( c2== 0) &&  ( c3==1 ) &&  ( r==1 ) )   )
  {
    lcd.print("Left");
    smallleft(); //small left
  }
   //right
  else if (   ( ( l== 1) &&  ( c1== 1) &&  ( c2== 1) &&  ( c3== 0) &&  ( r== 1) )   ||  ( ( l==1 ) &&  ( c1==1 ) &&  ( c2== 0) &&  ( c3==0 ) &&  ( r==1 ) )   )
  {
    lcd.print("Right");
    smallright(); //small right
  } 
  //dead end
  else if (    ( l== 1) &&  ( c1== 1) &&  ( c2==1 ) &&  ( c3==1 ) &&  ( r==1 )   )
  {
    lcd.print("U turn");
    
    right();         //U turn
    delay(2600); //delay for u turn
    directions[1] = 'U'; //incremet the position
    i++;
  }
  else if (   ( ( l== 0) &&  ( c1==0 ) ) ||  (  ( c3==0 ) &&  ( r==0 ) )  )
  { 
  
      align();     //align
     //Right only and str and ryt.
     if (   ( ( l== 1) &&  ( c1== 1) &&  ( c2==0 ) &&  ( c3==0 ) &&  ( r==0 ) )   ||  ( ( l== 1) &&  ( c1== 0) &&  ( c2== 0) &&  ( c3== 0) &&  ( r== 0) )   )
     {
       
       lcd.print("RT/Strt n rt?");
       inch();  //inch
       if( ( l== 1) &&  ( c1== 1) &&  ( c2==1 ) &&  ( c3==1 ) &&  ( r== 1) )
       {
         lcd.print("right");
         right();           //turn right
         delay(tdelay);       //turn delay
             
       }
       else if(  ( l==1 ) && (r==1 ) && (eosens()))
       {  
         lcd.print("straight");
         directions[i] = 'S'; // store S in the array
         i++;  // increment to the next position in the arrary
             
         forward();  //forward
         delay(fdelay);  //forward delay
       }
     }
     
     //decide left and str left
     else if (   ( ( l==0 ) &&  ( c1== 0) &&  ( c2== 0) &&  ( c3==1) &&  ( r== 1) )   ||  ( ( l== 0) &&  ( c1==0 ) &&  ( c2==0 ) &&  ( c3==0 ) &&  ( r== 1) )   )
     {
       
       lcd.print("Lfty/Strt n lft?"); 
       inch();  //inch
       if( ( l==1 ) &&  ( c1==1 ) &&  ( c2==1 ) &&  ( c3==1 ) &&  ( r== 1) )
       {
         lcd.print("left");
         left();           //turn left
         delay(tdelay);       //turn delay
             
       }
       else if(  ( l==1 ) && (r==1 ) && ( eosens()   ))
       {  
         lcd.print("left");
         directions[i] = 'L'; //store L in the array
         i++;   //increment to the next position in the array
             
         right();  //turn right 
         delay(tdelay);  //turn delay
       }
     }
     
     // 4 way /T-tint /End of maze
     
     else if ( ( l== 0) &&  ( c1== 0) &&  ( c2== 0) &&  ( c3== 0) &&  ( r==0 ) )  
     {
       
        lcd.print("T/END/4"); 
        inch(); //inch
        if( ((l== 0) && ( r== 0))  && (eosens()) )
        {
          lcd.print("4 way");
          directions[i] = 'R';// store L into the array
          i++;              //increment the position in the array
          right();           // turn left
          delay(tdelay);       //turn delay
        }
        else if( ( l== 1) &&  ( c1== 1) &&  ( c2== 1) &&  ( c3== 1) &&  ( r==1 ) ) 
        {  
          lcd.print("T-int");
          directions[i] = 'R'; //store L into the array
          i++;                  // increment the position in the array
             
          right();  //turn left
          delay(tdelay);  //turn delay
         }
         else if( ( l== 0) &&  ( c1==0 ) &&  ( c2== 0) &&  ( c3== 0) &&  ( r==0 ) ) 
         {  
           lcd.print("End of maze");
           directions[i] = 'E'; //store E into the array
           printing(directions);                 // print the final path on the lcd
           while(1)
           {
             Stop(); //stop
           }
         }
      }       
   }
             
}




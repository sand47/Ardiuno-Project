
char directions[30];

#include<LiquidCrystal.h>//lcd library

//LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

LiquidCrystal lcd(12,11,5,4,3,2);

int lm1 = 24; // naming motors pins
int lm2 = 25;
int rm1 = 0;
int rm2 = 1;

int l,c1,c2,c3,r; //naming sensor pins
int tdelay=850 ; //turn delay
int fdelay=100; //forward delay to be used when decisions are taken
int i;
int bp=13;
int counter =0;
unsigned long StartTime = millis();
unsigned long CurrentTime;
unsigned long ElapsedTime;

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
  
  pinMode(bp,OUTPUT);

}

void loop()
{
  lcd.clear(); //clear lcd
  
  readsens(); //read sensor values
  lcd.clear(); // clear lcd
  
  char c = Serial.read(); // Check if any key is pressed and copy the character value into c
  
  Serial.println(c);

//  while(Serial.available())
//  {

  if(c=='O') // Obstacle
  { 
     while(c=='O')
     {
        c = Serial.read();
        lcd.print(c);
        delay(5);
        Stop(); //Stop 
        digitalWrite(bp,1); // beep
        lcd.print("Stop and Beep until no obstacle");

        if(c=='F')
        {
            digitalWrite(bp,0); //OFF THE BEEP
            forward();
    
            lcd.print("Moving forward");
            delay(100);
            break;
        }
     }
  }
  else if (c=='F')
  {
            digitalWrite(bp,0); //OFF THE BEEP
            forward();
    
            lcd.print("Moving forward");
            delay(100);
  }
     
  

 // }
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
    lcd.print("small Left");
    smallleft(); //small left
  }
   //right
  else if (   ( ( l== 1) &&  ( c1== 1) &&  ( c2== 1) &&  ( c3== 0) &&  ( r== 1) )   ||  ( ( l==1 ) &&  ( c1==1 ) &&  ( c2== 0) &&  ( c3==0 ) &&  ( r==1 ) )   )
  {
    lcd.print("small Right");
    smallright(); //small right
  } 
  else if ( ((l== 1) &&  ( c1== 1) &&  ( c2== 1) &&  ( c3== 1) &&  ( r== 0) ) ||  ((l== 1) &&  ( c1== 1) &&  ( c2== 1) &&  ( c3== 0) &&  ( r== 0)) )
  {
    lcd.print("small left");
    smallright(); //small right
  }
  else if (  ( (l== 0) &&  ( c1== 1) &&  ( c2== 1) &&  ( c3== 1) &&  ( r== 1) )  || ((l== 0) &&  ( c1== 0) &&  ( c2== 1) &&  ( c3== 1) && ( r== 1) )   )
  {
    lcd.print("small right");
    smallleft(); //small right
  }
  else if( (l== 1) &&  ( c1== 0) &&  ( c2== 0) &&  ( c3== 0) &&  ( r== 1) )
  {
    lcd.print("forward");
    forward(); //forward
  }
    
  //dead end
//  else if (    ( l== 1) &&  ( c1== 1) &&  ( c2==1 ) &&  ( c3==1 ) &&  ( r==1 )   )
//  {
//    lcd.print("U turn");
//    
//    left();         //U turn
//    delay(2600); //delay for u turn
//    directions[1] = 'U'; //incremet the position
//    i++;
//  }
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
     else if (   ( ( l==0 ) &&  ( c1== 0) &&  ( c2== 0) &&  ( c3==1 ) &&  ( r== 1) )   ||  ( ( l== 0) &&  ( c1==0 ) &&  ( c2==0 ) &&  ( c3==0 ) &&  ( r== 1) )   )
     {
       
       lcd.print("Lfty/Strt n lft?"); 
       inch();  //inch
       if( ( l==1 ) &&  ( c1==1 ) &&  ( c2==1 ) &&  ( c3==1 ) &&  ( r== 1) )
       {
         lcd.print("left");
         left();           //turn left
         delay(tdelay);       //turn delay
             
       }
//       else if(  ( l==1 ) && (r==1 ) && ( eosens()   ))
//       {  
//         lcd.print("left");
//         directions[i] = 'L'; //store L in the array
//         i++;   //increment to the next position in the array
//             
//         left();  //turn left
//         delay(tdelay);  //turn delay
//       }
     }
     
     // 4 way /T-tint /End of maze
     
     else if ( ( l== 0) &&  ( c1== 0) &&  ( c2== 0) &&  ( c3== 0) &&  ( r==0 ) )  
     {
        counter++;
        Stop(); //Stop 
        digitalWrite(bp,1); // beep
        lcd.print("Stop and Beep for few minutes");
        delay(100);
        digitalWrite(bp,0);
        forward();
        delay(200);//delay(500);
       
        lcd.print("T/END/4"); 
        inch(); //inch
        if( ((l== 0) && ( r== 0))  && (eosens()) )
        {
          
          if((l==0)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1)) 
          {
            forward();
          }
          else
          {
              lcd.print("4 way");
              directions[i] = 'L';// store L into the array
              i++;              //increment the position in the array
              left();           // turn left
              delay(tdelay);       //turn delay
          }
        }
        else if( ( l== 1) &&  ( c1== 1) &&  ( c2== 1) &&  ( c3== 1) &&  ( r==1 ) ) 
        {  
          lcd.print("T-int");
          directions[i] = 'L'; //store L into the array
          i++;                  // increment the position in the array
             
          left();  //turn left
          delay(tdelay);  //turn delay
         }
         else if( ( l== 0) &&  ( c1==0 ) &&  ( c2== 0) &&  ( c3== 0) &&  ( r==0 ) ) 
         {  
           lcd.print("End of maze");
           directions[i] = 'E'; //store E into the array
           printing(directions);                 // print the final path on the lcd
         
           digitalWrite(bp,1); // beep
           lcd.print("Stop and Beep for few minutes");
           delay(100);
           digitalWrite(bp,0);
              unsigned long CurrentTime = millis();
              unsigned long ElapsedTime = CurrentTime - StartTime;
              unsigned int timesec=(ElapsedTime/1000);
              Serial.println("THE ROBOT TOOK ");
              Serial.println(timesec);
              Serial.println(" Seconds");
              
              lcd.print("The Robot took");
              lcd.print(timesec);
              lcd.print(" seconds time");
              delay(1000);
              Serial.println("THE ROBOT CROSS MARKS ");
              Serial.println(counter);
              lcd.clear();
              lcd.print("The robot crossed ");
              lcd.print(counter);
              lcd.print(" markers");
              delay(1000);

           while(1)
           {
              Stop(); //stop

            
           }
         }
      }       
   }
             
}




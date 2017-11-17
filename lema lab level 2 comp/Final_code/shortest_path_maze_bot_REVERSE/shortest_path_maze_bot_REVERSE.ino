char reshortn[30];
char directions[30];
char rev_reshortn[30];

//change U turn delay 1700
//change inch fn forward delay 650


#include<LiquidCrystal.h>//lcd library
//LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);
LiquidCrystal lcd(12,11,5,4,3,2);

int rm1 = 0;
int rm2 = 1;
int lm1 = 24; // naming motors pins
int lm2 = 25;
int l,c1,c2,c3,r; //naming sensor pins
int i;
int k=0;
int tdelay=725 ; //turn delay
int fdelay=100; //forward delay to be used when decisions are taken

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
    Serial.print(prtdirection[i]);
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
  
  if ((l== 1)&&(c1== 1)&&(c2== 0)&&(c3==1)&&(r==1))
  {
    lcd.print("Forward");
    forward(); //forward
  }
  //small left
  else if (((l== 1)&&(c1==0)&&(c2==1)&&(c3== 1)&&(r==1))||((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
  {
    lcd.print("Small Left");
    smallleft(); //small left
    delay(2);
  }
   //small right
  else if (((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1)))
  {
    lcd.print("Small Right");
    smallright(); //small right
    delay(2);
  } 
  //dead end
  else if ((l== 1)&&(c1== 1) &&(c2==1)&&(c3==1)&&(r==1))
  {
    lcd.print("U turn");
    left();         //U turn
    delay(1650); //delay for u turn
    directions[i] = 'U'; //incremet the position
    i++;
  }
  else if (((l==0)&&(c1==0))||((c3==0)&&(r==0)))
  { 
  
    align();     //align
    //Right only and str and ryt.
    if (((l== 1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0))||((l==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))
     {
       
       lcd.print("RT/Strt n rt?");
       inch();  //inch
       if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
       {
         lcd.print("right");
         right();           //turn right
         delay(tdelay);       //turn delay
             
       }
       else if((l==1)&&(r==1)&&(eosens()))
       {  
         lcd.print("straight");
         directions[i] = 'S'; // store S in the array
         i++;  // increment to the next position in the arrary   
         forward();  //forward
         delay(fdelay);  //forward delay
       }
     }
     
     //decide left and str left
     else if (((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r== 1))||((l== 0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r== 1)))
     {
       
       lcd.print("Lfty/Strt n lft?"); 
       inch();  //inch
       if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r== 1))
       {
         lcd.print("left");
         left();           //turn left
         delay(tdelay);       //turn delay
             
       }
       else if((l==1)&& (r==1)&&(eosens()))
       {  
         lcd.print("left");
         directions[i] = 'L'; //store L in the array
         i++;   //increment to the next position in the array   
         left();  //turn left
         delay(tdelay);  //turn delay
       }
     }
     
     // 4 way /T-tint /End of maze
     
     else if ((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))  
     {
       
        lcd.print("T/END/4"); 
        inch(); //inch
        if(((l==1)&&(r==1))&&(eosens()))
        {
          lcd.print("4 way");
          directions[i] = 'L';// store L into the array
          i++;              //increment the position in the array
          left();           // turn left
          delay(tdelay);       //turn delay
        }
        else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) 
        {  
          lcd.print("T-int");
          directions[i] = 'L'; //store L into the array
          i++;                  // increment the position in the array  
          left();  //turn left
          delay(tdelay);  //turn delay
         }
         else if((l== 0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)) 
         {  
           lcd.print("End of maze");
           directions[i] = 'E'; //store E into the array
           printing(directions);                 // print the final path on the lcd
           Stop(); //stop
           delay(5000);
           lcd.clear();
           replacement(directions);
         }
      }       
   }
             
}

void replacement(char shortn[]) //replacement function
{
  
  lcd.print("Entered Replacement");
  delay(1000);
  lcd.clear();  //clearn the LCD
  for( i = 0;shortn[i] != 'E' ; i++) //Read all the elements in the array
  {
    if(shortn[i] =='U'  ) //check if the element is U
    {
      if( (shortn[i-1] == 'S') && (shortn[i+1] == 'L')) // SUL is replaced by xxR
      {
        shortn[i-1]= 'X';
        shortn[i]='X';
        shortn[i+1] = 'R';
      }
      else if( (shortn[i-1] == 'L') && (shortn[i+1] == 'L')) // LUL is replaced by xxR
      {
        shortn[i-1]= 'X';
        shortn[i]='X';
        shortn[i+1] = 'S';
      }
      else if( (shortn[i-1] == 'L') && (shortn[i+1] == 'S')) // LUS is replaced by xxR
      {
        shortn[i-1]= 'X';
        shortn[i]='X';
        shortn[i+1] = 'R';
      }
      else if( (shortn[i-1] == 'L') && (shortn[i+1] == 'R')) // LUR is replaced by xxU
      {
        shortn[i-1]= 'X';
        shortn[i]='X';
        shortn[i+1] = 'U';
      }
      else if( (shortn[i-1] == 'R') && (shortn[i+1] == 'L')) // RUL is replaced by xxU
      {
        shortn[i-1]= 'X';
        shortn[i]='X';
        shortn[i+1] = 'U';
      }
      else if( (shortn[i-1] == 'S') && (shortn[i+1] == 'S')) // SUS is replaced by xxU
      {
        shortn[i-1]= 'X';
        shortn[i]='X';
        shortn[i+1] = 'U';
      }
    }
  }
  lcd.clear(); //clear LCD
  lcd.print("Finished New Path:");
  delay(1000);
  lcd.print("New:");
  int j=0;

  for(i= 0; shortn[i] !='E'; i++) //Read every element in the array
  {
    if(shortn[i] !='X') //check is the element is not x
    {
      reshortn[j]=shortn[i]; //if it is not x copy it to the new array
      j++;
    }
  }
  
  reshortn[j] = 'E' ;
  lcd.print("SPA=");
  printing(reshortn); //print the path in the LCD
  delay(1000);


  for(i= 0; reshortn[i] != 'E'; i++) //Read the new array
  {
    if(reshortn[i] == 'U') //check if the element is U
    {
      replacement(reshortn); // implement the replacement rules again
    }
  }
  
  lcd.clear(); //clear the LCD
  lcd.print("FINAL = "); 
  printing(reshortn); //Print the shortest path
  final();          // call the final path
}



void decisions(char str_reshortn[])
{
  
  lcd.print("Entered decisions");
  lcd.clear(); //clear the LCD
  
  if(str_reshortn[k] == 'S') // if the element is S
  {
    forward(); //Forward
    delay(fdelay); //fdelay
  }
  else if(str_reshortn[k] == 'L') // if the element is L
  {
    left(); //left
    delay(tdelay); // turn delay
  }
  else if(str_reshortn[k] == 'R') // if the element is R
  {
    right(); //right
    delay(tdelay); // turn delay
  } 
  k++; //increment position in the array
} 

void reversefu()
{
  lcd.clear(); //Clear the LCD
  lcd.print("Entered reverse directions");
  delay(500);
  
  lcd.clear();
  lcd.print("Stop before U turn");
  Stop();
  delay(500);
  
  lcd.clear();
  lcd.print("U turn");
  left();         //U turn
  delay(1650);//delay(1700); //delay for u turn

  lcd.clear();
  lcd.print("Stop After U turn");
  Stop();
  delay(500);
  
  lcd.clear();
  lcd.print("value of k is");
  delay(1000);
  
  Serial.print("value of k is");
  Serial.print(k);
  
  //reverse the array and store L as R ,  R as L , S as S only in new array rev_reshortn
  for(int m=k-1, n=0; m >= 0 ; --m, ++n)
  { 
    if(reshortn[m] == 'L')
    {
      rev_reshortn[n] = 'R';
    }
    else if(reshortn[m] == 'R')
    {
      rev_reshortn[n] = 'L';  
    }
    else if(reshortn[m] == 'S')
    {
      rev_reshortn[n] = 'S';
    }
  }
  
  Serial.print("the value of reversed path array ");
  lcd.clear();
  lcd.print("Reversed Shortest path");
  printing(rev_reshortn);
  delay(2000);
  
  // re-assign k value to 0
  k=0;

  

  while(1)
  {
    lcd.clear();
    readsens();  // read the value of sensors
    
    
    //*************************************
       //    LINE FOLLOWER SENSORS
    //*************************************
    
    if ((l==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))  
    {
      lcd.print("forward");
      forward(); // Forward
    }
    else if (((l==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1))||((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
    {
      lcd.print(" small left");
      smallleft(); // small left
    }
    else if (((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1)))
    {
      lcd.print("small right");
      smallright(); // small right
    }
    
    // ***********************************
     //     MAZE ROBOT 3 CATEGORIES
    // ***********************************
    else if (((l==0)&&(c1==0))||((c3==0)&&(r== 0)))
    {
        align();   //align right and straight and right
        if (((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0))||((l== 1)&&(c1== 0)&&(c2==0)&&(c3==0)&&(r==0)))
          //Before Inch
        {     
            inch();  //Inch
            if ((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //Right only
            {
              lcd.print("right");
              right(); //turn Right
              delay(tdelay); //tdelay
            }
            else if ((l==1)&&(r==1)&&(eosens()))  // Straight and left
            {
              decisions(rev_reshortn);   //check what decision to take
            } 
             
           // _____________________________________________________
           //     Left and straight and left
           // ______________________________________________________
         }
         else if(((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1)))
            //Before Inch 
         {
              inch();// Inch
              if ((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //Left only  
              {
                lcd.print(" = left");
                left();  // turn left
                delay(tdelay);  //tdelay
              }
              else if ((l==1)&&(r==1)&&(eosens()))  // Straight and left
              {
                 
                decisions(rev_reshortn);  // check what decision to take
              }            
          }
              
           // --------------------------------------------------------
           //        T Intersection/Fourway /End of Maze
           // ________________________________________________________
              
         else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)) //Before Inch
         {
              inch(); //Inch
              if((l==1)&&(r==1)&&(eosens()))  // Four way Intersection
              {
                decisions(rev_reshortn);  //check what decision to take
              }
              else if ((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //T Intersection  
              {     
        
                decisions(rev_reshortn);  //check what decision to take
              }
              
              else if ((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //End of Maze 
              {  
              CurrentTime = millis();
              ElapsedTime = CurrentTime - StartTime;
              unsigned int timeinsec =(ElapsedTime/1000);
              Serial.print("the time took by robot is  ");
              Serial.print(timeinsec);
              lcd.clear();
              lcd.print("The Robot took");
              lcd.print(timeinsec);
              lcd.print(" time");
              delay(100);   
                  while(1)
                  {
                   Stop();
                  }
              }
        }

     }
  } 
  
}  
        
void final()
{
  lcd.clear(); //Clear the LCD
  lcd.print("Entered final");
  delay(500);
  while(1)
  {
    lcd.clear();
    readsens();  // read the value of sensors
    
    
    //*************************************
       //    LINE FOLLOWER SENSORS
    //*************************************
    
    if ((l==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))  
    {
      forward(); // Forward
    }
    else if (((l==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1))||((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
    {
      smallleft(); // small left
    }
    else if (((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1)))
    {
      smallright(); // small right
    }
 
 
    // ***********************************
     //     MAZE ROBOT 3 CATEGORIES
    // ***********************************
    else if (((l==0)&&(c1==0))||((c3==0)&&(r== 0)))
    {
      align();   //align right and straight and right
      if (((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0))||((l== 1)&&(c1== 0)&&(c2==0)&&(c3==0)&&(r==0)))
      //Before Inch
      {     
        inch();  //Inch
        if ((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //Right only
        {
          right(); //turn Right
          delay(tdelay); //tdelay
        }
        else if ((l==1)&&(r==1)&&(eosens()))  // Straight and left
        {
          decisions(reshortn);   //check what decision to take
        } 
      }  
       // _____________________________________________________
       //     Left and straight and left
       // ______________________________________________________
        
        else if(((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1)))
        //Before Inch 
        {
          inch();// Inch
          if ((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //Left only  
          {
            lcd.print(" = left");
            left();  // turn left
            delay(tdelay);  //tdelay
          }
          else if ((l==1)&&(r==1)&&(eosens()))  // Straight and left
          {
            lcd.print("= stnlt");  
            decisions(reshortn);  // check what decision to take
          }            
        }
          
       // --------------------------------------------------------
       //        T Intersection/Fourway /End of Maze
       // ________________________________________________________
          
        else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)) //Before Inch
        {
          inch(); //Inch
          if((l==1)&&(r==1)&&(eosens()))  // Four way Intersection
          {
           decisions(reshortn);  //check what decision to take
          }
          else if ((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //T Intersection  
          {     
    
           decisions(reshortn);  //check what decision to take
          }
          else if ((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)) //End of Maze 
          {     
             lcd.print("End of shortest path maze");
             Stop();
             delay(1000);
             reversefu();
          }
        }
      }
    }
  
}


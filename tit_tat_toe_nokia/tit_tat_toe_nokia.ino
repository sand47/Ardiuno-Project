#include <LCD5110_Graph.h>
#include <Keypad.h>

LCD5110 lcd(8,9,10,12,11);                     // nokia display connections 

extern unsigned char SmallFont[];               //font for printing in nokia display 
char customKey;                                //reading data from 3x3 keypad
int count=0;                                     //count the number of moves
int pacy;                                     // o random position
bool moves[2][2];                            // storing x as true and o as false
int g=0;                                     //place index value
int place[8];                                // store postion value 
const byte ROWS = 3; 
const byte COLS = 3; 

char keys[ROWS][COLS] = { 
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  
};
byte rowPins[ROWS] = { 3,2,13 };
byte colPins[COLS] = { 7,6,5 }; 

Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  
  Serial.begin(9600);
  lcd.InitLCD();
  lcd.setFont(SmallFont);
  randomSeed(analogRead(7));
  lcd.clrScr();
  lcd.print("START", CENTER, 25);
  lcd.update();
  delay(1000);
  start();
  for(int a=0;a<3;a++)
   {
    for(int b=0;b<3;b++)
    {
      moves[a][b]=NULL;
    }
   }
}

void start()
{
    lcd.clrScr();
    lcd.print("4", CENTER, 25);
    lcd.update();
    delay(500);
    lcd.clrScr();
    lcd.print("3", CENTER, 25);
    lcd.update();
    delay(500);
    lcd.clrScr();
    lcd.print("2", CENTER, 25);
    lcd.update();
    delay(500);
    lcd.clrScr();
    lcd.print("1", CENTER, 25);
    lcd.update();
    delay(500);
    lcd.clrScr();
        
}

int comp_move()
{
   int z;
   pacy=random(1,10);                                 // generating random number for o position
   bool s=true;
  while(s)                                            //until s is false while is true till we get a empty spot
  { 
       for(int s=0;s<g;s++)
      {
        
        if(pacy==place[s])                             // checking if current pacy is occupied by previous x and o position
        {
            pacy=random(1,10);                        // if yes again generate random number 
        }
        else
         {
          z=1;                                       // if empty position is found put z=1
         }
       
      }
  
      if(z=1)
      {
        place[g]=pacy;                                // adding current o position to the place array 
        plc(pacy,1);                                  // calling plc function so that we put false in pacy position and 1 is used to differeniate with fn call from loop
        g++;
        s=false;        
        return pacy;                                 // returing pacy to o printing function to print o in pacy position
           
      }
   
  } 
}
int win()
{ 
  for(int a=0;a<3;a++)
  {
    for (int b=0;b<3;b++)
    {
      Serial.println(moves[a][b]);
    }
    Serial.println();
  }
               
   if(((moves[0][0]==true)&&(moves[0][1]==true)&&(moves[0][2]==true))||((moves[1][0]==true)&&(moves[1][1]==true)&&(moves[1][2]==true))||((moves[2][0]==true)&&(moves[2][1]==true)&&(moves[2][2]==true))||((moves[0][0]==true)&&(moves[1][0]==true)&&(moves[2][0]==true))||((moves[0][1]==true)&&(moves[1][1]==true)&&(moves[2][1]==true))||((moves[0][2]==true)&&(moves[1][2]==true)&&(moves[2][2]==true))||((moves[0][0]==true)&&(moves[1][1]==true)&&(moves[2][2]==true))||((moves[0][2]==true)&&(moves[1][1]==true)&&(moves[2][0]==true)))
   {

      
      lcd.clrScr();
      Serial.println("x won");
      lcd.print("X WON",CENTER,25);
      lcd.update();
      delay(2000);
      lcd.clrScr();
      lcd.print("Starting in 2s",CENTER,25);
      lcd.update();
      delay(2000);
      lcd.clrScr();
      count=0;                                                    // initiziling count to 0 
      g=0;                                                        //place index
      for(int i=0;i<8;i++)
      {  place[i]=0;
      }
      for(int a=0;a<3;a++)
      {
          for(int b=0;b<3;b++)
          {
            moves[a][b]=NULL;
          }
        
        
      }
      return 1;
                            
   }

   if(((moves[0][0]==false)&&(moves[0][1]==false)&&(moves[0][2]==false))||((moves[1][0]==false)&&(moves[1][1]==false)&&(moves[1][2]==false))||((moves[2][0]==false)&&(moves[2][1]==false)&&(moves[2][2]==false))||((moves[0][0]==false)&&(moves[1][0]==false)&&(moves[2][0]==false))||((moves[0][1]==false)&&(moves[1][1]==false)&&(moves[2][1]==false))||((moves[0][2]==false)&&(moves[1][2]==false)&&(moves[2][2]==false))||((moves[0][0]==false)&&(moves[1][1]==false)&&(moves[2][2]==false))||((moves[0][2]==false)&&(moves[1][1]==false)&&(moves[2][0]==false)))
   {

    
      lcd.clrScr();
      Serial.println("O won");
      lcd.print("O WON",CENTER,25);
      lcd.update();
      delay(2000);
      lcd.clrScr();
      lcd.print("Starting in 2s",CENTER,25);
      lcd.update();
      delay(2000);
      lcd.clrScr();
      count=0;                                                    // initiziling count to 0 
      g=0;                                                        // place index to 0
       for(int i=0;i<8;i++)
          place[i]=0;
      for(int a=0;a<3;a++)
      {
          for(int b=0;b<3;b++)
          {
            moves[a][b]=NULL;
          }
        
        
      }
      return 1;
      
                            
}

           
 return 0;    
}


void animation(char x)
{
 lcd.setFont(SmallFont); 
 count++;                                              // incrementing count and count should be less than 9 for 3x3 matrix tit tac toe
 
 // all box used and result of win didt come 
 
    if(count>9)
    {
        lcd.clrScr();
        lcd.print("DRAW",CENTER,25);
        lcd.update();
        delay(2500);
        lcd.clrScr();
        lcd.print("Starting in 2s",CENTER,25);
        lcd.update();
        delay(2000);
        lcd.clrScr();
        count=0;
        g=0;
        for(int i=0;i<8;i++)
            place[i]=0;
        for(int a=0;a<3;a++)
        {
            for(int b=0;b<3;b++)
            {
              moves[a][b]=NULL;
            }
          
          
        }
    }
    
    // odd moves are x moves 
    
    if(count%2!=0 )
    {
            
      switch(x)         // goes to required postion and print x 
      {
        case '1':
                 lcd.print("x",10,5);
                 lcd.update();
                 break;
                 
        case '2':
                 lcd.print("x",36,5);
                 lcd.update();
                 break;
                 
        case '3':
                 lcd.print("x",62,5);
                 lcd.update();
                 break;
                 
        case '4':
                lcd.print("x",10,22);
                lcd.update();
                break;
 
        case '5':
                lcd.print("x",36,22);
                lcd.update();
                break;
 
        case '6':
                lcd.print("x",62,22);
                lcd.update();
                break;
                
        case '7':
               lcd.print("x",10,38);
               lcd.update();
               break;

        case '8':
               lcd.print("x",36,38);
               lcd.update();
               break;
       
        case '9':
              lcd.print("x",62,38);
              lcd.update();
              break;


      }
      count++;                             // count is incremented so that computer take its turn 

     if(count>6)                          //>6 because to win we shld have min move of 3 of x  
     {
         int readx= win();                // readx is 1 it means result of the game has occured
         
         if(readx==1)
         {
          return;
         }
     }
    }

  
  // o moves are even number of count  
   if(count%2==0)
    {
      
       int computer_move=comp_move();
                  
        switch(computer_move)
        {          
             
        
        case 1:
                 lcd.drawCircle(15,5,5);
                 lcd.update();
                 break;
                 
        case 2:
                 lcd.drawCircle(40,5,5);
                 lcd.update();
                 break;
                 
        case 3:
                 lcd.drawCircle(65,5,5);
                 lcd.update();
                 break;
        case 4:
                lcd.drawCircle(15,22,5);
                lcd.update();
                break;
 
        case 5:
                lcd.drawCircle(40,22,5);
                lcd.update();
                break;
 
        case 6:
                lcd.drawCircle(65,22,5);
                lcd.update();
                break;
        case 7:
               lcd.drawCircle(15,38,5);
              lcd.update();
               break;

        case 8:
               lcd.drawCircle(40,38,5);
               lcd.update();
               break;
       
        case 9:
              lcd.drawCircle(65,38,5);
              lcd.update();
              break;
    
      }

    if(count>4)
    {
      Serial.println("calling win from o");
    int reado= win();
    if(reado==1)                                    //if reado is 1 then result has occured 
    {
      return;
    }
     
   }
  
}
}

int plc(int fg,int x)
{
  if(x==1)                                                      // converting char to int 
  {
      place[g] =fg;
         
        for(int h=0;h<g;h++)                                               //checking if current pressed postion is already occuiped
        {
          if(place[g]==place[h])
          {
             Serial.println("same location");
             return 1;                                                    //if occuiped return 1 meaning dont count this press
          }
        }
      g++;                                                               
           
        switch(fg)
        {
          case 1:
             moves[0][0]=true;
             break;
      
          case 2:
             moves[0][1]=true;
             break;
             
          case 3:
             moves[0][2]=true;
             break;
          
          case 4:
             moves[1][0]=true;
             break;
          
          case 5:
             moves[1][1]=true;
             break;
          
         case 6:
             moves[1][2]=true;
             break;
          
        case 7:
             moves[2][0]=true;
             break;
          
        case 8:
             moves[2][1]=true;
             break;
      
         case 9:
             moves[2][2]=true;
             break;
        }
      }
  }
  else
  { Serial.print("entered false ,called from comp_move");
    switch(fg)
    {
      case 1:
         moves[0][0]=false;
         break;
  
      case 2:
         moves[0][1]=false;
         break;
         
      case 3:
         moves[0][2]=false;
         break;
      
      case 4:
         moves[1][0]=false;
         break;
      
      case 5:
         moves[1][1]=false;
         break;
      
     case 6:
         moves[1][2]=false;
         break;
      
    case 7:
         moves[2][0]=false;
         break;
      
    case 8:
         moves[2][1]=false;
         break;
  
     case 9:
         moves[2][2]=false;
         break;
    }
    
  }
  
  return 0;
}

void loop() {

 
  //vertical line across the screen
  lcd.drawLine(25,0,25,70);
  lcd.drawLine(55,0,55,70);
  //horziontal line across the screen
  lcd.drawLine(10,15,70,15);
  lcd.drawLine(10,30,70,30);
  lcd.update();
 
  char customKey = customKeypad.getKey();                      // reading pressed position value 
  
  if (customKey){
    int fg=customKey-'0';  
    int catchm=plc(fg,0);                                 // if return value is 1 its mean there is a reptition of press on the same location 
    
    if(catchm!=1)
    {
      
      animation(customKey);                                   // passing the position value to animation function 
    }
     
  }  

}
  
  


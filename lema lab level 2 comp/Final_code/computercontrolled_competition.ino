#include<LiquidCrystal.h>//lcd library

//LiquidCrystal lcd(RS,EN,D4,D5,D6,D7); //Declare LCD pins rs, enable, d4,d5,d6,d7

LiquidCrystal lcd(12,11,5,4,3,2);

const int lm1 = 24; // naming left motor pins
const int lm2 = 25;
const int rm1 = 0;  // naming right motor pins
const int rm2 = 1;
const int bp =  13;
const int ledpin = 15;
unsigned long StartTime = millis();
unsigned long CurrentTime;
unsigned long ElapsedTime;
int counter=0;

void Stop() // stop
{
    digitalWrite(lm1,0);
    digitalWrite(lm2,0);
    digitalWrite(rm1,0);
    digitalWrite(rm2,0);   
}


void Forward() // forward
{
    digitalWrite(lm1,1);
    digitalWrite(lm2,0);
    digitalWrite(rm1,1);
    digitalWrite(rm2,0);
}
void Reverse() // reverse
{
    digitalWrite(lm1,0);
    digitalWrite(lm2,1);
    digitalWrite(rm1,0);
    digitalWrite(rm2,1);
}

void Left() // left
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

void Right()  //right
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}


void setup()
{
  Serial.begin(9600); // Baud rate 9600
  
  pinMode(lm1,OUTPUT); // Left motor
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT); // right motor
  pinMode(rm2,OUTPUT);
  pinMode(bp,OUTPUT);
  
  pinMode(ledpin,OUTPUT);

  lcd.begin(16,2); //Declaring the 16*2 LCD
  lcd.print("WELCOME Aboard"); // Initial display
  delay(1000);
}

void loop() // Infinite loop
{
  lcd.clear(); //Clearing the LCD
  
  while(!Serial.available())
  {
    lcd.clear();
    lcd.print("no data available---- STOP"); // Print that no data is available
    delay(5);
    Stop(); // Robot should stop
  }
  
  char c = Serial.read(); // Check if any key is pressed and copy the character value into c
  
  Serial.println(c);
  lcd.print(c);
  delay(5);
  
  if(c=='F')  //Forward
  {
    digitalWrite(bp,0); //OFF THE BEEP
    Forward();
    lcd.print("Moving forward");
   
  }

  
  if(c=='B') //Reverse
  {
    Reverse();
    lcd.print("Moving reverse");
    

  }
  if(c=='L') //Left
  {
    Left();
    lcd.print("Moving left");
    

  }
  if(c=='R') //Right
  {
    Right();
    lcd.print("Moving right");
   
  }
  if(c=='M') //Marker
  {
    counter++;
    Stop(); //Stop 
    digitalWrite(bp,1); // beep
    lcd.print("Stop and Beep for few minutes");
    delay(1000);
    digitalWrite(bp,0);
  } 
  if(c=='O') // Obstacle
  { 
      Stop(); //Stop 
      digitalWrite(bp,1); // beep
      lcd.print("Stop and Beep until no obstacle");
      
  }
  if(c=='S')
  {
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
   
  }
  if(c=='N')
  {
//    while(1)
//    {
//      c=Serial.read();
//      Serial.print(c);
//     if (c != 'N')
//      break;
      for(int i=0; i <256; i=i+50)
      {
        analogWrite(ledpin,i);
        delay(1000);
      }
      for(int i=255; i>=0; i=i-50)
      {
        analogWrite(ledpin,i);
        delay(1000);
      }
//    } 

   }
    //digitalWrite(ledpin,LOW);
  
}

#include <LCD5110_Graph.h>

LCD5110 lcd(8,9,10,12,11);

extern unsigned char SmallFont[];
extern uint8_t gamer[];
extern uint8_t ball[];


const int sensorPin = A0; 
int value,j;


const int buzzerPin = 2;
const int songLength = 18;
char notes[] = "cdfda ag cdfdg gf "; 
int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};
int tempo = 113;

void beep()
{

  int i, duration;

  for (i = 0; i < songLength; i++) // step through the song arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')          // is this a rest? 
    {
      delay(duration);            // then pause for a moment
    }
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }

  
  while(true){}
  
    
  
}

int frequency(char note) 
{

  int i;
  const int numNotes = 8;  // number of notes we're storing
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  
  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0); 
}

int c[10];
int g;

void check()
{
  while(true)
  {
    Serial.println("no data");
    if(Serial.available())
    {
         g=Serial.read()-'0';
         lcd.clrScr();
         lcd.printNumI(g, CENTER, 25);
         lcd.update();
         delay(2000);
                  
    }
  }
}


  
void setup() 
{
   //beep();
  Serial.begin(9600);  
  pinMode(buzzerPin, OUTPUT);
  lcd.InitLCD();
  lcd.setFont(SmallFont);
  randomSeed(analogRead(7));
  lcd.clrScr();
  lcd.print("START", CENTER, 25);
  lcd.update();
  delay(5000);
  //check(); 
 
}

void animation()
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
     lcd.print("0", CENTER, 25);
    lcd.update();
    delay(500);
    lcd.clrScr();
    lcd.drawBitmap(-10, 0, gamer, 84, 48);   
    lcd.update();
    delay(3000);
  
  value = analogRead(sensorPin);  
  j = map(value, 0, 1023, 10,2 );
  //Serial.println(value);
       if(value<100)
         {
           
               for(int i=0;i<j;i++)
             {
                  lcd.clrScr();
                 lcd.drawBitmap(i,5, ball, 84, 48);
                 lcd.update();
                 delay(20);   
             }    
             lcd.clrScr();
              lcd.print("WON",CENTER,25);
              lcd.update();
              delay(2000);
             
         }
       else
       {
        
                  lcd.clrScr(); 
                  lcd.setFont(SmallFont);          
                  lcd.print("Try again", CENTER, 25);
                  lcd.update();
                  delay(2000);
                  lcd.clrScr(); 
 
        }
             
}               


void loop() 
{
  
  //Serial.print("in loop");
  animation();

  
}




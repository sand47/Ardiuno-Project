#include <LCD5110_Graph.h>
#include <Keypad.h>
const byte ROWS = 3; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 3, 2,13 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 7,6,5 }; 

// Create the Keypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LCD5110 lcd(8,9,10,12,11);
extern unsigned char SmallFont[];

void setup() {
 Serial.begin(9600);
  lcd.InitLCD();
  lcd.setFont(SmallFont);
  randomSeed(analogRead(7));
  lcd.clrScr();
  lcd.print("START", CENTER, 25);
  lcd.update();
  delay(5000);
   start();
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
     lcd.print("0", CENTER, 25);
    lcd.update();
    delay(500);
    lcd.clrScr();
     
}

void loop() {

 
  //vertical line
  lcd.drawLine(25,0,25,70);
  lcd.drawLine(55,0,55,70);
  //horziontal line
  lcd.drawLine(10,15,70,15);
  lcd.drawLine(10,30,70,30);
  lcd.update();
  delay(500);
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
  
  
}

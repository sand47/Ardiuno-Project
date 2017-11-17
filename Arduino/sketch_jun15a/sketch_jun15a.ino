#include <HCMAX7219.h>
#include "SPI.h"
 
/* Set the LOAD (CS) digital pin number*/
#define LOAD 11
  
/* Create an instance of the library */
HCMAX7219 HCMAX7219(LOAD);
 
 
void setup() 
{       
}
 
 
/* Main program */
void loop() 
{
  byte Loopcounter;
  int Position;
 
  /* Clear the output buffer */
  HCMAX7219.Clear();
   
  /* SCROLL SOME TEXT 2 TIMES BEFORE MOVING ON */
  for (Loopcounter = 0; Loopcounter <= 2; Loopcounter++)
  {
    for(Position=0; Position <= 64; Position++)
    {
      HCMAX7219.printMatrix("HELLO!! ", Position);
      HCMAX7219.Refresh();
      delay(80);
    }
  }
   
   
  /* SCROLL SOME INVERTED TEXT 2 TIMES BEFORE MOVING ON */
  HCMAX7219.Invert(INVERTON);
  for (Loopcounter = 0; Loopcounter <= 2; Loopcounter++)
  {
    for(Position=0; Position <= 64; Position++)
    {
      HCMAX7219.Clear();
      HCMAX7219.printMatrix("HELLO!! ", Position);
      HCMAX7219.Refresh();
      delay(80);
    }
  }
  HCMAX7219.Invert(INVERTOFF);
   
   
   
  /* SCROLL AN INTEGER NUMBER */
  for(Position=0; Position <= 80; Position++)
  {
    HCMAX7219.Clear();
    HCMAX7219.printMatrix(-12345678, Position);
    HCMAX7219.Refresh();
    delay(80);
  }
   
   
   
  /* SCROLL AN INTEGER NUMBER WITH DECIMAL PLACE */
  for(Position=0; Position <= 96; Position++)
  {
    HCMAX7219.Clear();
    HCMAX7219.printMatrix(-12345678, 2, Position);
    HCMAX7219.Refresh();
    delay(80);
  }
   
} 

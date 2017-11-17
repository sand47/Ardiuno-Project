//We always have to include the library
#include "LedControl.h"

//pin 12 is connected to the DataIn 
//pin 11 is connected to the CLK 
//pin 10 is connected to LOAD 

//LedControl(int dataPin, int clkPin, int csPin, int numDevices);
LedControl lc=LedControl(4,5,11,1);

void setup() {
  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call   
  lc.shutdown(0,false);
  //Set the brightness to a medium values (0~15 possible values)
  lc.setIntensity(0,2);
  //and clear the display
  lc.clearDisplay(0);
}

#define SP {0, 0, 0, 0, 0}               //Espacio
#define EX {0, 125, 0, 0, 0}             //Exclamacion !
#define A {31, 36, 68, 36, 31}
#define B {127, 73, 73, 73, 54,}
#define C {62, 65, 65, 65, 34}
#define D {127, 65, 65, 34, 28}
#define E {127, 73, 73, 65, 65}
#define F {127, 72, 72, 72, 64}
#define G {62, 65, 65, 69, 38}
#define H {127, 8, 8, 8, 127}
#define I {0, 65, 127, 65, 0}
#define J {2, 1, 1, 1, 126}
#define K {127, 8, 20, 34, 65}
#define L {127, 1, 1, 1, 1}
#define M {127, 32, 16, 32, 127}
#define N {127, 32, 16, 8, 127}
#define O {62, 65, 65, 65, 62}
#define P {127, 72, 72, 72, 48}
#define Q {62, 65, 69, 66, 61}
#define R {127, 72, 76, 74, 49}
#define S {50, 73, 73, 73, 38}
#define T {64, 64, 127, 64, 64}
#define U {126, 1, 1, 1, 126}
#define V {124, 2, 1, 2, 124}
#define W {126, 1, 6, 1, 126}
#define X {99, 20, 8, 20, 99}
#define Y {96, 16, 15, 16, 96}
#define Z {67, 69, 73, 81, 97}

//Escribimos la frase separando cada letra por comas
//En el primer numero lo adaptaremos la longitud de la frase (caracteres)
byte frase[5][5]={H,O,L,A,SP};
int largo = sizeof(frase)/5;
int gnd[18]={-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12};

void loop() { 

  for (int letra=0; letra<largo; letra++){
    for (int desplaza = 18; desplaza>=5; desplaza--) {
      for (int i=0; i<5; i++){ 
        lc.setRow(0,gnd[i+desplaza-5],frase[letra][i]); 
      }
    delay(100); // speed of animation
    lc.clearDisplay(0);
    } 
    if(letra == largo){
    letra = 0;}
  }//end for letra  

}

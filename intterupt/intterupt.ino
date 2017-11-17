/*

Board  Digital Pins Usable For Interrupts
Uno, Nano, Mini, other 328-based  2, 3
Mega, Mega2560, MegaADK 2, 3, 18, 19, 20, 21
Micro, Leonardo, other 32u4-based 0, 1, 2, 3, 7
Zero  all digital pins, except 4
MKR1000 Rev.1 0, 1, 4, 5, 6, 7, 8, 9, A1, A2
Due all digital pins
101 all digital pins


About Interrupt Service Routines

ISRs are special kinds of functions that have some unique limitations most other functions do not have. An ISR cannot have any parameters, and they shouldn't return anything.

Generally, an ISR should be as short and fast as possible. If your sketch uses multiple ISRs, only one can run at a time, other interrupts will be executed after the current one finishes in an order that depends on the priority they have. millis() relies on interrupts to count, so it will never increment inside an ISR. Since delay() requires interrupts to work, it will not work if called inside an ISR. micros() works initially, but will start behaving erratically after 1-2 ms. delayMicroseconds() does not use any counter, so it will work as normal.

Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

For more information on interrupts, see Nick Gammon's notes.

Syntax

attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);  (recommended)
attachInterrupt(interrupt, ISR, mode);  (not recommended)
attachInterrupt(pin, ISR, mode) ; (not recommended Arduino Due, Zero, MKR1000, 101 only)
Parameters

interrupt:  the number of the interrupt (int)
pin:  the pin number  (Arduino Due, Zero, MKR1000 only)
ISR:  the ISR to call when the interrupt occurs; this function must take no parameters and return nothing. This function is sometimes referred to as an interrupt service routine.
mode: 
defines when the interrupt should be triggered. Four constants are predefined as valid values:
LOW to trigger the interrupt whenever the pin is low,
CHANGE to trigger the interrupt whenever the pin changes value
RISING to trigger when the pin goes from low to high,
FALLING for when the pin goes from high to low.
The Due board allows also:
HIGH to trigger the interrupt whenever the pin is high.
(Arduino Due, Zero, MKR1000 only)

*/

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
s}

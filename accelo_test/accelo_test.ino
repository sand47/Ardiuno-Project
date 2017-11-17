// reading value from accelometer for gesture control robot movemenets 

int x,y;

int xpin= A0;
int ypin= A1; // analog input pins 

void setup()
{
   Serial.begin(9600);
}

void loop()
{
  x =analogRead(xpin); // reading analog input from acclometer
  y =analogRead(ypin);
  Serial.print("x = ");
  Serial.println(x);
  Serial.print("y = ");
  Serial.println(y);
  delay(1000);}78      bbvg m

#define trigPin 13
#define echoPin 12
int buzzer = 7;
int lm1= 2;        //naming left motor pins
int lm2= 3;
int rm1= 4;        //naming right motor pins
int rm2= 5;


void Forward()     //Forward
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
  
}

void Stop()        //Stop
 {
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}
void Reverse()     //Reverse
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}
void Right()        //Right 
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}
void Left()         //Left
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}
 
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
}

int distance()
{
   long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

void loop() {

   if(Serial.available()>0)
   {
      char c =Serial.read();
      switch (c)
      {
         case 'w':
               Forward();
               break;
               
         case 'a':
               Left();
               break;
         case 'd':
               Right();
               break;
         
          case 's':
               Reverse();
               break;

          case 'r':
            Stop();
            break;
         
      }
   }
  int distances = distance();
  
  if (distances <25 ) {  // This is where the LED On/Off happens
     Stop();
     
     for(int i=0;i<3;i++)
     {
    digitalWrite(buzzer,HIGH); // When the Red condition is met, the Green LED should turn off
    delay(1000);
    digitalWrite(buzzer,LOW);
    delay(1000);
     }
     Forward();
     delay(100);
}
}
  


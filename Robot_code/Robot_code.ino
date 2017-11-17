int lm1= 24;        //naming left motor pins
int lm2= 25;
int rm1= 0;        //naming right motor pins
int rm2= 1;
int up=3;
int down=4; 

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

void Up()
{
    
  digitalWrite(up,1);
  delay(400);
  digitalWrite(up,0);
  
}

void Down()
{
  
  
  digitalWrite(down,1);
  delay(400);
  digitalWrite(down,0);
  
 }
void setup()
{
  Serial.begin(9600);            //Baud rate for thr serial communications
  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(up,OUTPUT);
  pinMode(down,OUTPUT);
}
void loop()               
{
  while(!Serial.available());        //check if serial data is available
  char c= Serial.read();             //read the serial data and copyit into a variable "c"  
  Serial.println();   
  if(c=='f')    //Forward range
  Forward();
  if(c=='s')    //stop range
  Stop();
  if(c=='b')    //Reverse range
  Reverse();
  if(c=='l')    //Left range
  Left();
  if(c=='r')   //Right range
  Right();
  if(c=='u')
  Up();
  if(c=='d')
  Downwr();
   if(c=='e')
  Up();
  if(c=='f')
  Down();
}


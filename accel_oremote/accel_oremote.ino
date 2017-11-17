int xpin= A0; 
int ypin= A1;
int up=0;
int down=1

;

void setup()
{
  Serial.begin(9600);
  pinMode(up,INPUT);
  pinMode(down,INPUT);
}

void loop()
{
  int x= analogRead(A0);
  int y= analogRead(A1);
  
  
  if ((x>=445&&x<=515)&&(y>=450&&y<=510)) // stop
  {
    Serial.print('s');
  }
  
  if(y<450) // forward 
  {
    Serial.print('r');
  }
  
  if(y>515) // reverse 
  {
    Serial.print('l');
  }
  
   if(x>515) // left
  {
    Serial.print('b');
  }
  
 if(x<445) // right
  {
    Serial.print('f');
  } 

 if(digitalRead(up)==HIGH)
 {
  
  Serial.print('u'); 
}
if(digitalRead(up)==LOW)
{
  Serial.print('e');
  
  }
if(digitalRead(down)==HIGH)

{
  Serial.print('d');
  }

if(digitalRead(down)==HIGH)

{
  Serial.print('f');
  }  
}

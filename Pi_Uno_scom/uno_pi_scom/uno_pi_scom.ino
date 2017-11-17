int forward=2;
int rewinde=4;
int count=0;
int maxi=4;

void setup() {
  
  Serial.begin(9600);
  pinMode(forward,INPUT);
  digitalWrite(forward,HIGH);
  pinMode(rewinde,INPUT);
  digitalWrite(rewinde,HIGH);
}

void loop() {

 if( digitalRead(forward) == LOW)
 {
   
   count++;
   Serial.println(count);
   delay(1000);
   if(count==maxi)
    {
     count=0;
    }
 }

 if(digitalRead(rewinde) == LOW)
 {
    if(count==1)
    {
      Serial.println(maxi);
      delay(1000);
      count=4;
    }
    if(count>1 &&count<5)
    {
     count--;
     delay(1000);
     Serial.println(count);
    }
    if(count<1)
    {
     count =0;
    }
  
  }

}

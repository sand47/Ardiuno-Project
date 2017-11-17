#include <Time.h>  

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 


void setup() {
  // put your setup code here, to run once:
 pinMode(4, OUTPUT);
 
}

void loop() {
  float time1,time2;
  time1=0;
  

while(1)
{
  time2=50000;
  if((time2-time1==0))
  {
     digitalWrite(4, HIGH)
     delay(200000); 
  }
  else
    time1=second();
     
}
}

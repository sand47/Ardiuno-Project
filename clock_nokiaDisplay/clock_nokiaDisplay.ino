#include <ArduinoJson.h>

#include <LCD5110_Graph.h>

LCD5110 lcd(8,9,10,12,11);                                      // calling nokia display constructor

extern unsigned char SmallFont[];  

int buzzer=4;
int hour,minute,alarms;
String json="";
int alr_hr=0,alr_mint=0;


void show(int hr,int mint,int sec)
{
     lcd.printNumI(hr,23,25); 
     lcd.update();
     lcd.print(":",52,25);
     lcd.update();
     lcd.printNumI(mint,40,25);
     lcd.update();
     lcd.print(":",35,25);
     lcd.update();
     lcd.printNumI(sec,57,25);
     lcd.update();
}

 bool beign =false;
 int d=1;
 int k=0;
 char in;
 //String jsons="";
int gettime()
{
  /*
   * We need to first get the current time and then only proceed to print so we might use while (true) and with one condition we might break
   * we parse the input json and call the toint function and we access the hour,minute,alarm variable globally
   */
  
   if(d==1)
   {
    while(true)
    {
       while(Serial.available())
       {
        in =Serial.read();
        //Serial.println(in);
        //delay(1000);
        if(in=='{')
        {
          beign=true;
        }
        if(beign)
         json +=(in);
    
        if(in=='}')
          { beign = false;
            k=1;
           // Serial.println("out of serial"); 
           break;
          }
       
       delay(5);
       
        }
        if(k==1)
        {
          toint();
          k=0;
          break;
        }
        //Serial.print("inside true while");
    }
    //Serial.print("outside while");
    d=0;
   }
   else
   { 

    if(Serial.available())
    {
      while(Serial.available())
      {
        in =Serial.read();
        //Serial.println(in);
       
        if(in=='{')
        {
          beign=true;
        }
        if(beign)
         json +=(in);

        if(in=='}')
        {  k=8;
          //Serial.println("value of k");
          beign =false;
        }
        delay(1);
   
      }
    }   
    
    if(k==8)
    {
      //Serial.println("Calling from here");
      toint();
      k=0;
    }
   }    

   
}

void toint()
{
  //Serial.println("inside toint");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  alarms = root["alarm"];
  if(alarms==1)
  {
  alr_hr = root["hours"];
  alr_mint = root["minute"];
  }
  else
  {
    hour = root["hours"];
    minute = root["minute"];
  }
  
  //Serial.println("inside toints s2e");
  //Serial.println(hour);
  //Serial.println(minute);
  //Serial.println(alarms);
   json=""; 
}


void alarm()
{
  
 if(hour==alr_hr && minute == alr_mint && hour!=0 && minute!=0)
    {
      digitalWrite(buzzer,HIGH);
      delay(3000);
      digitalWrite(buzzer,LOW);
    }
   
}

void start()
{
   //Serial.println("Into start function ");
   while (true)
   {    
      for(int sec=0;sec<61;sec++)
      {
          gettime();
          alarm();
          //Serial.println();
          //Serial.println(hour);
          //Serial.println(minute);
                                             
          if(sec==60)                             // after 60 second sec=0 and mint++
          {         
            //Serial.println("changed minute");
            minute=minute+1;
            sec=0;   
            if(minute==60)
            {
              hour=hour+1;
              minute=0;
              sec=0;
            }
          }
      
       delay(1000);                              // one second delay = 1sec 
       lcd.clrScr();
       show(hour,minute,sec);
      }    
     
    }

}

void setup()
{
   
   Serial.begin(9600);
   lcd.InitLCD();
   lcd.setFont(SmallFont);
   lcd.clrScr();
   lcd.print("CLOCK",CENTER,25);
   lcd.update();
   delay(2000);
   lcd.clrScr();
   pinMode(buzzer,OUTPUT);
   start();
   
}

void loop()
{
   
}




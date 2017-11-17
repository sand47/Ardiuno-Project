char directions[30];
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int lm1= 24;        //setting up left motor pins
int lm2= 25;
int rm1= 0;        //setting up right motor pins
int rm2= 1;
int i,l,c1,c2,c3,r;
int tdelay=700;
int fdelay=500;

void forward()     //Forward
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
void smallright()     //Reverse
{
 
  digitalWrite(lm1,1;
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0;
}
void smallleft()        //Right 
{
  
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}
void right()         //Left
{
  
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}

void left()         //Left
{
  
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

int eosens()
{
	
readsens();
if(((c1+c2+c3)== 1)|| ((c1+c2+c3)== 2 ))
   return 1;
 else
  return 0;  
}

void readsens()
{
 	
    l=digitalRead(26);
    c1=digitalRead(27);
    c2=digitalRead(28);
    c3=digitalRead(29);
    r=digitalRead(30);
    lcd.print(l);
    lcd.print("--");
    lcd.print(c1);
    lcd.print("--");
    lcd.print(c2);
    lcd.print("--");
    lcd.print(c3);
    lcd.print("--");
    lcd.print(r);
    lcd.print("--");

}

void inch()
{
	lcd.print("Inch Function");
        Stop();
	delay(100);
        forward();
	delay(0);
        Stop();
	delay(100);
	lcd.clear();
        readsens();
}

void align()
{
	Stop();
	delay(500);
        forward();
	delay(60);
        Stop();
        delay(500);
	lcd.clear();
        readsens();
        
}

void printing(char prtdirection[])
{
	lcd.clear();
	for(int i=0;prtdirection[i]!='E';i++)
	{
        lcd.print(prtdirection[i]);

	}
	delay(2000);
}

void setup()
{
      lcd.begin(16,2);	
      lcd.print("Maze Solving robot");
      delay(1000);
      lcd.clear();
      pinMode(lm1,OUTPUT );
      pinMode(lm2,OUTPUT );
      pinMode(rm1,OUTPUT );
      pinMode(rm2,OUTPUT );
      
      pinMode(26,INPUT );
      pinMode(27,INPUT );
      pinMode(28,INPUT );
      pinMode(29,INPUT );
      pinMode(30,INPUT );

}

void loop()
{
	
	lcd.clear();
        readsens();
        lcd.clear();
	//line follower
    //fwd

    if((l==1 )&&(c1==1) &&(c2== 0)&&(c3==1)&&(r==1))
    {
      lcd.print("FORWARD");
      forward();

    }//left
    else  if(((l==1)&&(c1==0) &&(c2==1  )&&(c3==1  )&&(r== 1 ))||((l==1 )&&(c1== 0 ) &&(c2== 0 )&&(c3==1  )&&(r== 1 )))
    {
     lcd.print("Small Left");
     smallleft();
    }
    //right
    else  if(((l==1 )&&(c1==1  ) &&(c2==1  )&&(c3==0  )&&(r==1  ))||((l==1 )&&(c1==1  ) &&(c2==0  )&&(c3==0  )&&(r==1  )))
    {
        lcd.print("Small Right");
        smallright();
    }
    //dead end
    else  if((l== 1)&&(c1==1  ) &&(c2==1  )&&(c3==1  )&&(r==1  ))
    {
       lcd.print("U turn");
       left();
       delay(1300);
       directions[i]='U';
       i++;

    }
    else if(((l==1 )&&(c1==1  )) ||((c3== 0 )&&(r== 0 )))
    {
       align();
      
       if(((l==1 )&&(c1==1  ) &&(c2==0  )&&(c3==0  )&&(r==0  ))||((l==1 )&&(c1== 0 ) &&(c2== 0 )&&(c3==0  )&&(r==0  )))
       {
       lcd.print("RT/Strt n rt?");
       inch();
       
       if((l== 1)&&(c1==1  ) &&(c2==1  )&&(c3==1  )&&(r==1  ))
       {
          lcd.print("right");
          right();
          delay(tdelay);

       }
       else if((l== 1)&&(r==1  )&& ( eosens() ))
       {
        
        lcd.print("straight");
        directions[i]='S';
        i++;
        forward();
        delay(fdelay);
       }

       }
       else if(((l==0 )&&(c1== 0 ) &&(c2== 0 )&&(c3==0  )&&(r== 1 ))||((l==0 )&&(c1==0  ) &&(c2==0  )&&(c3==1  )&&(r== 1 )))
       {

        lcd.print("Lft/str n lft?");
        inch();
        if((l==1)&&(c1==1  ) &&(c2==  1)&&(c3== 1 )&&(r== 1 ))
        {
           lcd.print("left");
           left();
           delay(tdelay);
        }
        else if((l==1 )&&(r==1  )&&(eosens()   ))
        {
          lcd.print("left");
          directions[i]='L';
          i++;
          left();
          delay(tdelay);

        }        

       }

       else if((l== 0)&&(c1==0  ) &&(c2==0  )&&(c3==0  )&&(r==  0))
       {

         lcd.print("T/END/4");
         inch();

          if((l==1 )&&(r==1  )&& ( eosens()  ))
          
          {
            lcd.print("4 way");
            directions[i]='L';
            i++;
            left();
            delay(tdelay);
          }
          else if((l==1 )&&(c1==1  ) &&(c2==1  )&&(c3== 1 )&&(r==  1))
          {

            lcd.print("T-int");
            directions[i]='L';
            i++;
            left();
            delay(tdelay);
          }

          else if((l== 0)&&(c1==0  ) &&(c2==0  )&&(c3==0  )&&(r==0))
          {

           lcd.print("End of maze");
           directions[i]='E';
           printing(directions);
           while(1)
           {
              Stop();

           }
          }
       }


    }


}

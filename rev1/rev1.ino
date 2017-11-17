char reshortn[30];
char directions[30];
char rereshortn[30];
//char shortn[30];
#include<LiquidCrystal.h>
LiquidCrystal lcd (12,11,5,4,3,2);
int rm1=0;
int rm2=1;
int lm1=24;
int lm2=25;
int l,c1,c2,c3,r;
int i=0;
int k=0;
int j=0;
int tdelay=750;
int fdelay=500;




void Stop()
{

digitalWrite(lm1,0);
digitalWrite(lm2,0);
digitalWrite(rm1,0);
digitalWrite(rm2,0);
}

void forward()

{

digitalWrite(lm1,1);
digitalWrite(lm2,0);
digitalWrite(rm1,1);
digitalWrite(rm2,0);
}

void smallright()

{

digitalWrite(lm1,1);
digitalWrite(lm2,0);
digitalWrite(rm1,0);
digitalWrite(rm2,0);
}

void smallleft()

{

digitalWrite(lm1,0);
digitalWrite(lm2,0);
digitalWrite(rm1,1);
digitalWrite(rm2,0);
}


void right()

{

digitalWrite(lm1,1);
digitalWrite(lm2,0);
digitalWrite(rm1,0);
digitalWrite(rm2,1);
}


void left()

{

digitalWrite(lm1,0);
digitalWrite(lm2,1);
digitalWrite(rm1,1);
digitalWrite(rm2,0);
}


int eosens()

{
readsens();
if (((c1+c2+c3)==1)||((c1+c2+c3)==2))
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
delay(600);
Stop();
delay(100);
readsens();
delay(50);
lcd.clear();
}

void align()

{
Stop();
delay(500);
forward();
delay(60);
Stop();
delay(500);
readsens();
delay(50);
lcd.clear();

}

void printing(char prtdirection[])

{
lcd.clear();
for(i=0;prtdirection[i]!='E';i++)

{
lcd.print(prtdirection[i]);
}
delay(2000);
}

void setup()

{
 lcd.begin(16,2);
 lcd.print("MSR with LHR");
 delay(500);
 lcd.clear();
 pinMode(lm1,OUTPUT);

 pinMode(lm2,OUTPUT);


 pinMode(rm1,OUTPUT);

 pinMode(rm2,OUTPUT);

 pinMode(26,INPUT);

 pinMode(27,INPUT);

 pinMode(28,INPUT);

 pinMode(29,INPUT);

 pinMode(30,INPUT);

}

void loop()

{
  lcd.clear();
  readsens();
  lcd.clear();

//line follower

if ((l==1) && (c1==1) && (c2==0) && (c3==1) && (r==1))

{

lcd.print("Forward");
forward();
}

else if (( (l==1) && (c1==0) && (c2==1) && (c3==1) && (r==1)) || ( (l==1) && (c1==0) && (c2==0) && (c3==1) && (r==1)))

{

lcd.print("Left");
smallleft();
}

else if (( (l==1) && (c1==1) && (c2==1) && (c3==0) && (r==1)) || ( (l==1) && (c1==1) && (c2==0) && (c3==0) && (r==1)) )


{

lcd.print("Right");
smallright();
}

else if ( (l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))
{
lcd.print("U Turn");
left();
delay(1800);
directions[i]='U';
i++;
}


else if ( ((l==0) && (c1==0)) || ((c3==0) && (r==0))) //every other case in the maze
{
 align();
 //r8 only/str n r8
if (( (l==1) && (c1==1) && (c2==0) && (c3==0) && (r==0)) || ( (l==1) && (c1==0) && (c2==0) && (c3==0) && (r==0)) )

{

lcd.print("RT/Strt n rt?");
inch();

if  ((l==1) && (c1==1) && (c2==1) &&  (c3==1) && (r==1))

{

lcd.print("right");
right();
delay(tdelay);

}


else if ( (l==1) && (r==1) && (eosens()))


{

 lcd.print("straight");


 directions[i]='S';
 i++;
 forward();

 delay(fdelay);

 }
}

//decide left n str left

else if (( (l==0) && (c1==0) && (c2==0) && (c3==1) && (r==1)) || ( (l==0) && (c1==0) && (c2==0) && (c3==0) && (r==1)) )

{

lcd.print("Lft/Strt n lft?");
delay(100);
lcd.clear();
inch();

if  ((l==1) && (c1==1) && (c2==1) &&  (c3==1) && (r==1))

{

lcd.print("Left");
left();
delay(tdelay);

}
else if ( (l==1) && (r==1) && (eosens()))


{

 lcd.print("Left");


 directions[i]='L';
 i++;
 left();
 delay(tdelay);

 }
}


//4 way 
else if ((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))

{

lcd.print("T/END/4");
inch();
if  ((l==1)  && (r==1) && (eosens()))

{

lcd.print("4 Way");

directions[i]='L';
i++;
left();
delay(tdelay);

}

else if ((l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))

{

lcd.print("T-int");

directions[i]='L';
i++;
left();
delay(tdelay);

}

 else if ((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))

{

lcd.print("End of maze");

directions[i]='E';
Stop();
printing(directions);
left();
delay(1750);
forward();
delay(500);
align();
lcd.clear();
replacement(directions);
}
}
}
}




void replacement(char shortn[])

{
lcd.print("Entered Replacement");
delay(1000);
lcd.clear();
for(i=0; shortn[i]!='E'; i++)
{

if(shortn[i]=='U' )
{

if((shortn[i-1]=='S') && (shortn[i+1]=='L'))

{

shortn[i-1]='x';

shortn[i]='x';

shortn[i+1]='R';

}
else if ((shortn[i-1]=='L') && (shortn[i+1]=='L'))

 {

shortn[i-1]='x';

shortn[i]='x';

shortn[i+1]='S';

}

else if ((shortn[i-1]=='L') && (shortn[i+1]=='S'))

 {

shortn[i-1]='x';

shortn[i]='x';

shortn[i+1]='R';

}

else if ((shortn[i-1]=='L') && (shortn[i+1]=='R'))

 {

shortn[i-1]='x';

shortn[i]='x';

shortn[i+1]='U';

}

else if ((shortn[i-1]=='R') && (shortn[i+1]=='L'))

 {

shortn[i-1]='x';

shortn[i]='x';

shortn[i+1]='U';

}

else if ((shortn[i-1]=='S') && (shortn[i+1]=='S'))

 {

shortn[i-1]='x';

shortn[i]='x';

shortn[i+1]='U';

}

}
}

lcd.clear();
lcd.print("Finish New Path:");
delay(1000);
lcd.print("New:");
int j=0;
for(i=0;shortn[i]!='E';i++)
{
if(shortn[i]!='x')
{
reshortn[j]=shortn[i];
j++;
}
}

reshortn[j]='E';


lcd.print("SPA =");
printing(reshortn);
delay(1000);
//int m=0;
for(i=0;reshortn[i]!='E';i++)
{
if(reshortn[i]=='U')
{
replacement (reshortn);
}
if(reshortn[j]=='L')
{
  right();
  delay(tdelay);
  
  //rereshortn[m]=='R';
  //m++;
}
else if(reshortn[j]=='R')
{
  left();
  delay(tdelay);
  //rereshortn[m]=='L';
  //m++;
}
}
reshortn[j]='E';

lcd.clear();

lcd.print("Final =");
printing(reshortn);
final();
}


void decisions()
{
lcd.print("Entered decisions");
lcd.clear();
if(reshortn[j]=='S')
{
forward();
delay(tdelay);
}

else if(reshortn[j]=='R')
{
left();
delay(tdelay);
}

else if(reshortn[j]=='L')

{
right();
delay(tdelay);
}
j++;
}



void final()
{
  
lcd.clear();
lcd.print("Entered final");

while(1)
{
  lcd.clear();
  readsens();
  lcd.clear();

if ((l==1) && (c1==1) && (c2==0) && (c3==1) && (r==1))

{
forward();
}

else if (( (l==1) && (c1==0) && (c2==1) && (c3==1) && (r==1)) || ( (l==1) && (c1==0) && (c2==0) && (c3==1) && (r==1)))
{
smallleft();
}

else if (( (l==1) && (c1==1) && (c2==0) && (c3==0) && (r==1)) || ( (l==1) && (c1==1) && (c2==1) && (c3==0) && (r==1)))

{
 smallright();
}

else if (( (l==0) && (c1==0))  || ((c3==0) && (r==0)))

{
  align();
if (( (l==1) && (c1==1) && (c2==0) && (c3==0) && (r==0)) || ( (l==1) && (c1==0) && (c2==0) && (c3==0) && (r==0)))

{
inch();

if ((l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))

{
right();
delay(tdelay);

}

else if ((l==1) && (r==1) && (eosens()))

{

decisions();

} }


else if (( (l==0) && (c1==0) && (c2==0) && (c3==1) && (r==1)) || ( (l==0) && (c1==0) && (c2==0) && (c3==0) && (r==1)))

{
 inch();

if ((l==1)&& (c1==1) && (c2==1) && (c3==1) && (r==1))

{

lcd.print("= left");
left();
delay(tdelay);

}

else if ((l==1) && (r==1) && (eosens))

{

lcd.print("= stnlt");
decisions();


}

}



else if ((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))

{
inch();
 if ((l==1) && (r==1) && (eosens()))
 
 {
   decisions();
 }
 
 
else if ((l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))

{
//decisions();
//}

//else if ((l==1)&& (c1==1) && (c2==1) && (c3==0) && (r==0))

//{

while(1)
{
 Stop();
}



} }

}  }

}


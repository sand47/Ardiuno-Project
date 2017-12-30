String msg,crc,encoded="",output_crc;
int t[5];
int TE=9;

void setup() {
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(4,INPUT);
 pinMode(5,INPUT); 
 pinMode(9,OUTPUT);
}

 
void crc_check(){

  crc ="1101";
  int m = msg.length(), n = crc.length();
  encoded+=msg;
  for (int i=1;i<=n-1;i++)                         // zero padding
    encoded+='0';
  for (int i=0;i<encoded.length()-n;)             // xor and crc check bit generation
  {
    for (int j=0;j<n;j++)
      encoded[i+j]=encoded[i+j]==crc[j]?'0':'1';  
    for ( ;i<encoded.length() && encoded[i]!='1';i++);  // find value of i for next bitor
  }
  for (char i: encoded.substring(encoded.length()-crc.length()) ) // checking for error bit
    if(i!='0')
    {
      digitalWrite(TE,LOW);
      return ;
    }
    else
      digitalWrite(TE,HIGH);  
  
}

void readData()
{
  
  for(int i=0;i<4;i++)
  {
    t[i] = digitalRead(i+2);  // connected AD0 from ht12e to D2 in arduino 
         
  }
 crc_check();
 
}


void loop() {
  readData();
}



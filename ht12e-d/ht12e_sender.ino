String msg,crc,encoded="",output_crc;
int t[3],k[3] ;
char er[4],err[4];
void setup() {
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(4,INPUT);
 pinMode(5,INPUT); 
}


 
String crc_check(){

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

  encoded = encoded.substring(encoded.length()-n+1);   // getting check bit alone 
  return encoded;
}
 
void sendData(String output_crc)
{
  output_crc.toCharArray(er,3) ;
  for(int i=0;i<4;i++)
  {
    digitalWrite(i+2,er[i]);  // connected AD0 from ht12e to D2 in arduino 
         
  }

}

String readData()
{
  for(int i=0;i<4;i++) 
    t[i]=0;
    
  for(int i=0;i<4;i++)
  {
    t[i] = digitalRead(i+2);  // connected AD0 from ht12e to D2 in arduino 
         
  }
 String output = crc_check();
 return output; 
}


void loop() {
  output_crc = readData();
  sendData(output_crc);
}



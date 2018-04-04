
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;
int mode = 3;

void setup() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
  #endif
  Serial.begin(9600);
  pinMode(8, OUTPUT);                                                                                         
  digitalWrite(8, HIGH);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  pinMode(7, INPUT);                                                          //Switch for Mode selection
  pinMode(14, OUTPUT);                                      
  pinMode(A1,INPUT);                                                          //Switch for click
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  delay(5);
  if (digitalRead(7) == 0)                                                 //Check if switch mode button is pressed
  { 
      Serial.print(char(120));
      delay(100);
   }
   else if (digitalRead(A1)==0)                                               //Check if click button is pressed
   {
      Serial.print(char(121));
    }
    else {
      int x1 = map(ax, -15000, 15000, 0, 9);                                        //Mapping values of gyroscope to mouse X axis
      int y1 = map(ay, -15000, 15000, 0, 9);                                        //Mapping values of gyroscope to mouse Y axis
      int z1 = x1 * 10 + y1;                                                        //Converting data to a single character
      Serial.print(char(z1));                                                       //Sending the data to the other Arduino 
    
  }

}

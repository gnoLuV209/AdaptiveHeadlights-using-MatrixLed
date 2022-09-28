#include <LedControl.h>
#include <Servo.h>
/*_________________________________________________________________*/
// Set 4 pin of Arduino connect with IC Max7219
LedControl lc=LedControl(12,11,10,2);
// Create 2 Servo
Servo myServo1;
Servo myServo2;
/*_________________________________________________________________*/
// Declare variable
String x;
byte module_left =0;
byte module_right=0;
int servo1 = 6;
int servo2 = 5;
int c;
int angle;
/*_________________________________________________________________*/
// High Beam in 4 area
byte normal_mode[] =                             
{
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111
};
// Low Beam in area left
byte area_left_mode[] =                             
{
B00001111,
B00001111,
B00001111,
B00001111,
B00001111,
B11111111,
B11111111,
B11111111
};
// Low Beam in area left
byte area_mid1_mode[] =                             
{
B11110000,
B11110000,
B11110000,
B11110000,
B11110000,
B11111111,
B11111111,
B11111111
};
// Low Beam in area mid
byte area_mid2_mode[] =                             
{
B00001111,
B00001111,
B00001111,
B00001111,
B00001111,
B11111111,
B11111111,
B11111111
};
// Low Beam in area right
byte area_right_mode[] =                             
{
B11110000,
B11110000,
B11110000,
B11110000,
B11110000,
B11111111,
B11111111,
B11111111
};
/*_________________________________________________________________*/
void setup() {
Serial.begin (115200);
myServo1.attach(servo1);
myServo2.attach(servo2);
Serial.setTimeout(1);
// we deal with two MAX7219 modules, and we can power them on and set intensity independenty:
// the MAX7219 is in power-saving mode on startup,
// we have to do a wakeup call
lc.shutdown (0,false);
lc.shutdown (1,false);
// set the brightness to a medium values
lc.setIntensity (0,2);                       // 0 = low; 8 = high – first variable is module number i.e. module 0
lc.setIntensity (1,2);                       // 0 = low; 8 = high – first variable is module number i.e. module 1
// clear the displays
lc.clearDisplay (0);
lc.clearDisplay (1);
module_left  = 0; // Left Headlight
module_right = 1; // Right Headlight
}
/*_________________________________________________________________*/
void loop() {
  normal();
  x = Serial.readString();
  if (x=='1eft') {
    lc.clearDisplay (0);
    lc.clearDisplay (1);
    area_left();
    delay(2000);
    } 
  if (x=='mid') {
    lc.clearDisplay (0);
    lc.clearDisplay (1);
    area_mid();
    delay(2000);
    } 
  if (x=='right') {   
    lc.clearDisplay (0);
    lc.clearDisplay (1);
    area_right(); 
    delay(2000);
    }
  c = analogRead(A0);
  angle = map(c,0,1023,0,180);
  myServo1.write(angle);
  myServo2.write(angle);      
  }
/*_________________________________________________________________*/
// Normal mode function
void normal(){
  for (int i = 0; i < 8; i++){
    lc.setRow (0,i,normal_mode[i]);
    lc.setRow (1,i,normal_mode[i]);
    }
    }
// Area 1 mode function
void area_left(){
  for (int i = 0; i < 8; i++){
    lc.setRow (0,i,area_left_mode[i]);
    lc.setRow (1,i,normal_mode[i]);
    }
    }
// Area 2 mode function
void area_mid(){
  for (int i = 0; i < 8; i++){
    lc.setRow (0,i,area_mid1_mode[i]);
    lc.setRow (1,i,area_mid2_mode[i]);
    }
    }
// Area 4 mode function
void area_right(){
  for (int i = 0; i < 8; i++){
    lc.setRow (1,i,area_right_mode[i]);
    lc.setRow (0,i,normal_mode[i]);
    }
    }

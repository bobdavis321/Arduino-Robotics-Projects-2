/*************************************** 
15 DOF Humanoid with PCA9685

// Define our Servo's
Servo servo0; // Left Ankle
Servo servo1; // Left Knee
Servo servo2; // Left Hip F-B
Servo servo3; // Left Hip R-L
Servo servo4; // Right Ankle
Servo servo5; // Right Knee
Servo servo6; // Right Hip F-B
Servo servo7; // Right Hip R-L
Servo servo8; // Left Hand
Servo servo9; // Left Elbow
Servo servo10; // Left Shoulder
Servo servo11; // Right Hand
Servo servo12; // Right Elbow
Servo servo13; // Right Shoulder
Servo servo14; // Head
***************************/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
// The Max7219 library
#include "LedControl.h"
// The Max7219 on D8, D9, D10 as Data Clock CS
LedControl lc=LedControl(8,9,10,1);
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t snum = 0;
int twait =200;

// Create arrays for the expresions
byte a[8]={B00000000,B01100110,B01100110,B00000000,B00011000,B00000000,B01111110,B00000000};//normal
byte b[8]={B00000000,B01100110,B01100000,B00000000,B00011000,B01000010,B00111100,B00000000};//wink+smile
byte c[8]={B00000000,B01100110,B01100110,B00000000,B00011000,B01000010,B00111100,B00000000};//smile
byte d[8]={B00000000,B01100110,B01100110,B00000000,B00011000,B00000000,B00111100,B01000010};//frown
byte e[8]={B00000000,B01100110,B01100110,B00000000,B00011000,B01111110,B01000010,B01111110};//open mouth

byte walkf[10][8] = {
// 0    1    2    3    4    5    6    7
{ 80,  80,  90,  90,  90,  90,  90,  90}, // Left Ankle
{ 90,  90,  90,  90,  90,  90,  90,  90}, // Ankle F-B
{ 80,  75,  80,  85,  90,  90,  90,  90}, // Knee
{ 80,  75,  80,  85,  90,  90,  90,  90}, // Hip F-B
{ 90,  90,  90,  85,  85,  85,  90,  90}, // Hip
{ 90,  90,  90,  99,  99,  95,  90,  90}, // Right Ankle
{ 90,  90,  90,  90,  90,  90,  90,  90}, // Ankle F-B
{ 90,  85,  80,  75,  80,  85,  90,  90}, // Knee
{ 90,  85,  80,  75,  80,  85,  90,  90}, // Hip F-B
{ 95,  95,  90,  90,  90,  90,  90,  90}, // Hip
};
byte walkb[10][8] = {
// 0    1    2    3    4    5    6    7   
{ 80,  80,  90,  90,  90,  90,  90,  90}, // Left Ankle
{ 90,  90,  90,  90,  90,  90,  90,  90}, // Knee
{ 99, 105,  99,  95,  90,  90,  90,  90}, // Knee
{ 99, 105,  99,  95,  90,  90,  90,  90}, // Hip
{ 90,  90,  90,  85,  85,  85,  90,  90}, // Hip
{ 90,  90,  90,  99,  99,  95,  90,  90}, // Right Ankle
{ 90,  90,  90,  90,  90,  90,  90,  90}, // Knee
{ 90,  95,  99, 105,  99,  95,  90,  90}, // Knee
{ 90,  95,  99, 105,  99,  95,  90,  90}, // Hip
{ 95,  95,  90,  90,  90,  90,  90,  90}, // Hip
};
byte walkl[10][4] = {
// 0    1    2    3   
{ 80,  80,  90,  90, }, // Left Ankle
{ 90,  90,  90,  90, }, // Knee
{ 80,  75,  80,  85, }, // Knee
{ 80,  75,  80,  85, }, // Hip
{ 90,  90,  90,  85, }, // Hip
{ 90,  90,  90,  90, }, // Right Ankle
{ 90,  90,  90,  90, }, // Knee
{ 90,  85,  80,  75, }, // Knee
{ 90,  85,  80,  75, }, // Hip
{ 95,  95,  90,  90, }, // Hip
};
byte walkr[10][4] = {
// 0    1    2    3  
{ 80,  80,  90,  90, }, // Left Ankle
{ 90,  90,  90,  90, }, // Knee
{ 99, 105,  99,  95, }, // Knee
{ 99, 105,  99,  95, }, // Hip
{ 90,  90,  90,  85, }, // Hip
{ 90,  90,  90,  90, }, // Right Ankle
{ 90,  90,  90,  90, }, // Knee
{ 90,  95,  99, 105, }, // Knee
{ 90,  95,  99, 105, }, // Hip
{ 95,  95,  90,  90, }, // Hip
};

void writeOnMatrixa() {
  lc.setRow(0,0,(a[0]));
  lc.setRow(0,1,(a[1]));
  lc.setRow(0,2,(a[2]));
  lc.setRow(0,3,(a[3]));
  lc.setRow(0,4,(a[4]));
  lc.setRow(0,5,(a[5]));
  lc.setRow(0,6,(a[6]));
  lc.setRow(0,7,(a[7]));
  delay(100);  }

void writeOnMatrixb() {  
  lc.setRow(0,0,(b[0]));
  lc.setRow(0,1,(b[1]));
  lc.setRow(0,2,(b[2]));
  lc.setRow(0,3,(b[3]));
  lc.setRow(0,4,(b[4]));
  lc.setRow(0,5,(b[5]));
  lc.setRow(0,6,(b[6]));
  lc.setRow(0,7,(b[7]));
  delay(100);   }

void writeOnMatrixc() {  
  lc.setRow(0,0,(c[0]));
  lc.setRow(0,1,(c[1]));
  lc.setRow(0,2,(c[2]));
  lc.setRow(0,3,(c[3]));
  lc.setRow(0,4,(c[4]));
  lc.setRow(0,5,(c[5]));
  lc.setRow(0,6,(c[6]));
  lc.setRow(0,7,(c[7]));
  delay(100);   }

void writeOnMatrixd() {  
  lc.setRow(0,0,(d[0]));
  lc.setRow(0,1,(d[1]));
  lc.setRow(0,2,(d[2]));
  lc.setRow(0,3,(d[3]));
  lc.setRow(0,4,(d[4]));
  lc.setRow(0,5,(d[5]));
  lc.setRow(0,6,(d[6]));
  lc.setRow(0,7,(d[7]));
  delay(100);   }

void writeOnMatrixe() {  
  lc.setRow(0,0,(e[0]));
  lc.setRow(0,1,(e[1]));
  lc.setRow(0,2,(e[2]));
  lc.setRow(0,3,(e[3]));
  lc.setRow(0,4,(e[4]));
  lc.setRow(0,5,(e[5]));
  lc.setRow(0,6,(e[6]));
  lc.setRow(0,7,(e[7]));
  delay(100);   }


void setup() {
  Serial.begin(9600);
  Serial.println("Commands: Test Wave Clap Forward Back Right Left");
  pwm.begin();
  pwm.setOscillatorFrequency(28000000); //was 27
  pwm.setPWMFreq(50); // Analog servos at ~50 Hz updates

  // The MAX72XX starts in power-saving mode
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  delay(10);
}

void loop() {
  writeOnMatrixa(); // default expression
  
  // Center Servos
  for (snum=0; snum<11; snum++){
    pwm.setPWM(snum, 0, 300);}
    pwm.setPWM(11, 0, 200);    
    pwm.setPWM(12, 0, 150); // Sholder   
    pwm.setPWM(13, 0, 300);
    pwm.setPWM(14, 0, 400);    
    pwm.setPWM(15, 0, 450); // Sholder
    delay(50);
  
  if ( Serial.available()) {
    char sinch = Serial.read();
    switch(sinch) {
      case 't': //Test servos
      // Test servos using setPWM()
      for (snum=0; snum<16; snum++){
        Serial.println(snum);
        pwm.setPWM(snum, 0, 250);    
        delay(500);
        pwm.setPWM(snum, 0, 350);    
        delay(500);
        pwm.setPWM(snum, 0, 300); }
      break;
      case 'w': // wave hand
          writeOnMatrixb(); // smile
          pwm.setPWM(15, 0, 250);
          delay(200);
          pwm.setPWM(13, 0, 200);
          delay(500);
          pwm.setPWM(13, 0, 400);
          delay(500);
          pwm.setPWM(13, 0, 200);
          delay(500);
          pwm.setPWM(13, 0, 400);
          delay(500);
          pwm.setPWM(13, 0, 200);
          delay(500);
      break;
      case 'c': // clap
          writeOnMatrixc(); // smile
          pwm.setPWM(15, 0, 300);
          pwm.setPWM(12, 0, 300);
          pwm.setPWM(14, 0, 480);
          pwm.setPWM(11, 0, 120);
          delay(500);
          pwm.setPWM(13, 0, 420);
          pwm.setPWM(10, 0, 180);
          delay(500);
          pwm.setPWM(13, 0, 300);
          pwm.setPWM(10, 0, 300);
          delay(500);
          pwm.setPWM(13, 0, 420);
          pwm.setPWM(10, 0, 180);
          delay(500);
          pwm.setPWM(13, 0, 300);
          pwm.setPWM(10, 0, 300);
          delay(500);
          pwm.setPWM(13, 0, 420);
          pwm.setPWM(10, 0, 180);
          delay(500);
      break;

      case 'f': // forward key
        writeOnMatrixe(); // O
          pwm.setPWM(15, 0, 400); // Shift weight forward
          pwm.setPWM(12, 0, 200);
        for (int i=0; i<7; i++){
          pwm.setPWM(0, 0, (walkf[0][i]*3.33));  
          pwm.setPWM(1, 0, (walkf[1][i]*3.33));  
          pwm.setPWM(2, 0, (walkf[2][i]*3.33));  
          pwm.setPWM(3, 0, (walkf[3][i]*3.33));  
          pwm.setPWM(4, 0, (walkf[4][i]*3.33));  
          pwm.setPWM(5, 0, (walkf[5][i]*3.33)); 
          pwm.setPWM(6, 0, (walkf[6][i]*3.33));  
          pwm.setPWM(7, 0, (walkf[7][i]*3.33)); 
          pwm.setPWM(8, 0, (walkf[8][i]*3.33));  
          pwm.setPWM(9, 0, (walkf[9][i]*3.33)); 
          delay(twait);
        }
        break;  

      case 'b':  // back key
        writeOnMatrixe(); // O
          pwm.setPWM(15, 0, 400); // Shift weight forward
          pwm.setPWM(12, 0, 200);
        for (int i=0; i<7; i++){
          pwm.setPWM(0, 0, (walkb[0][i]*3.33));  
          pwm.setPWM(1, 0, (walkb[1][i]*3.33));  
          pwm.setPWM(2, 0, (walkb[2][i]*3.33));  
          pwm.setPWM(3, 0, (walkb[3][i]*3.33));  
          pwm.setPWM(4, 0, (walkb[4][i]*3.33));  
          pwm.setPWM(5, 0, (walkb[5][i]*3.33)); 
          pwm.setPWM(6, 0, (walkb[6][i]*3.33));  
          pwm.setPWM(7, 0, (walkb[7][i]*3.33)); 
          pwm.setPWM(8, 0, (walkb[8][i]*3.33));  
          pwm.setPWM(9, 0, (walkb[9][i]*3.33)); 
          delay(twait);
        }
        break;        
        
      case 'r':  // Right key
        writeOnMatrixd(); // frown
          pwm.setPWM(15, 0, 400); // Shift weight forward
          pwm.setPWM(12, 0, 200);
        for (int i=0; i<4; i++){
          pwm.setPWM(0, 0, (walkr[0][i]*3.33));  
          pwm.setPWM(1, 0, (walkr[1][i]*3.33));  
          pwm.setPWM(2, 0, (walkr[2][i]*3.33));  
          pwm.setPWM(3, 0, (walkr[3][i]*3.33));  
          pwm.setPWM(4, 0, (walkr[4][i]*3.33));  
          pwm.setPWM(5, 0, (walkr[5][i]*3.33)); 
          pwm.setPWM(6, 0, (walkr[6][i]*3.33));  
          pwm.setPWM(7, 0, (walkr[7][i]*3.33)); 
          pwm.setPWM(8, 0, (walkr[8][i]*3.33));  
          pwm.setPWM(9, 0, (walkr[9][i]*3.33)); 
          delay(twait);
        }
        break;    

      case 'l':  // Right key
        writeOnMatrixd(); // frown
          pwm.setPWM(15, 0, 400); // Shift weight forward
          pwm.setPWM(12, 0, 200);
        for (int i=0; i<4; i++){
          pwm.setPWM(0, 0, (walkl[0][i]*3.33));  
          pwm.setPWM(1, 0, (walkl[1][i]*3.33));  
          pwm.setPWM(2, 0, (walkl[2][i]*3.33));  
          pwm.setPWM(3, 0, (walkl[3][i]*3.33));  
          pwm.setPWM(4, 0, (walkl[4][i]*3.33));  
          pwm.setPWM(5, 0, (walkl[5][i]*3.33)); 
          pwm.setPWM(6, 0, (walkl[6][i]*3.33));  
          pwm.setPWM(7, 0, (walkl[7][i]*3.33)); 
          pwm.setPWM(8, 0, (walkl[8][i]*3.33));  
          pwm.setPWM(9, 0, (walkl[9][i]*3.33)); 
          delay(twait);
        }
        break;       
    }     
  }      
  delay(100);
}

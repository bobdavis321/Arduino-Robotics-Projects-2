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
#define SERVOMIN  250 // This is the minimum test 
#define SERVOCENTER 300 // 90 degrees, This is the center pulse length
#define SERVOMAX  350 // 600 // This is the maximum test
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
// servo number counter
uint8_t snum = 0;
int twait = 200;

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte walkf[8][8] = {
// 0    1    2    3    4    5    6    7
{ 85,  85,  85,  90,  95,  95,  95,  90}, // Left Ankle
{ 90,  90,  85,  85,  85,  95,  95,  95}, // Knee
{ 90,  90,  85,  85,  85,  95,  95,  95}, // Hip
{ 90,  90,  85,  90,  95,  95,  95,  90}, // Hip
{ 85,  85,  85,  90,  95,  95,  95,  90}, // Right Ankle
{ 90,  85,  85,  85,  85,  90,  95,  95}, // Knee
{ 90,  85,  85,  85,  85,  90,  95,  95}, // Hip
{ 85,  85,  85,  90,  90,  90,  95,  90}, // Hip
};

byte walkb[8][8] = {
// 0    1    2    3    4    5    6    7   
{ 85,  85,  85,  90,  95,  95,  95,  90}, // Left Ankle
{ 90,  90,  95,  95,  95,  85,  85,  85}, // Knee
{ 90,  90,  95,  95,  95,  85,  85,  85}, // Hip
{ 90,  90,  85,  90,  95,  95,  95,  90}, // Hip
{ 85,  85,  85,  90,  95,  95,  95,  90}, // Right Ankle
{ 90,  95,  95,  95,  95,  90,  85,  85}, // Knee
{ 90,  95,  95,  95,  95,  90,  85,  85}, // Hip
{ 85,  85,  85,  90,  90,  90,  95,  90}, // Hip
};

byte walkl[8][4] = {
// 0    1    2    3   
{ 85,  85,  85,  90, }, // Left Ankle
{ 90,  90,  95,  95, }, // Knee
{ 90,  90,  95,  95, }, // Hip
{ 90,  90,  85,  90, }, // Hip
{ 85,  85,  85,  90, }, // Right Ankle
{ 90,  95,  95,  95, }, // Knee
{ 90,  95,  95,  95, }, // Hip
{ 85,  85,  85,  90, }, // Hip
};

byte walkr[8][4] = {
// 0    1    2    3  
{ 85,  85,  85,  90, }, // Left Ankle
{ 90,  90,  85,  85, }, // Knee
{ 90,  90,  85,  85, }, // Hip
{ 90,  90,  85,  90, }, // Hip
{ 85,  85,  85,  90, }, // Right Ankle
{ 90,  85,  85,  85, }, // Knee
{ 90,  85,  85,  85, }, // Hip
{ 85,  85,  85,  90, }, // Hip
};

void setup() {
  Serial.begin(9600);
  Serial.println("Commands: Test Wave Clap Forward Back Right Left");
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
}

void loop() {
  // Center Servos
  for (snum=0; snum<16; snum++){
    pwm.setPWM(snum, 0, SERVOCENTER);
    delay(50);
  }
  if ( Serial.available()) {
    char sinch = Serial.read();
    // Test out the servos 2 at a time
    switch(sinch) {
      case 't': //Test servos
      // Drive each servo one at a time using setPWM()
      for (snum=0; snum<16; snum++){
        Serial.println(snum);
        for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
          pwm.setPWM(snum, 0, pulselen);    }
        delay(500);
        for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
          pwm.setPWM(snum, 0, pulselen);    }
        delay(500);
        pwm.setPWM(snum, 0, SERVOCENTER);   }
      break;
      case 'w': // wave hand
          pwm.setPWM(13, 0, 550);
          delay(200);
          pwm.setPWM(11, 0, 200);
          delay(500);
          pwm.setPWM(11, 0, 400);
          delay(500);
          pwm.setPWM(11, 0, 200);
          delay(500);
          pwm.setPWM(11, 0, 400);
          delay(500);
          pwm.setPWM(11, 0, 200);
          delay(500);
      break;
      case 'c': // clap
          pwm.setPWM(13, 0, 450);
          pwm.setPWM(10, 0, 150);
          pwm.setPWM(12, 0, 150);
          pwm.setPWM(9, 0, 450);
          delay(500);
          pwm.setPWM(11, 0, 420);
          pwm.setPWM(8, 0, 180);
          delay(500);
          pwm.setPWM(11, 0, 300);
          pwm.setPWM(8, 0, 300);
          delay(500);
          pwm.setPWM(11, 0, 420);
          pwm.setPWM(8, 0, 180);
          delay(500);
          pwm.setPWM(11, 0, 300);
          pwm.setPWM(8, 0, 300);
          delay(500);
          pwm.setPWM(11, 0, 420);
          pwm.setPWM(8, 0, 180);
          delay(500);
      break;

      case 'f': // forward key
        for (int i=0; i<8; i++){
          pwm.setPWM(0, 0, (walkf[0][i]*3.3));  
          pwm.setPWM(1, 0, (walkf[1][i]*3.3));  
          pwm.setPWM(2, 0, (walkf[2][i]*3.3));  
          pwm.setPWM(3, 0, (walkf[3][i]*3.3));  
          pwm.setPWM(4, 0, (walkf[4][i]*3.3));  
          pwm.setPWM(5, 0, (walkf[5][i]*3.3)); 
          pwm.setPWM(6, 0, (walkf[6][i]*3.3));  
          pwm.setPWM(7, 0, (walkf[7][i]*3.3)); 
          delay(twait);
        }
        break;  

      case 'b':  // back key
        for (int i=0; i<8; i++){
          pwm.setPWM(0, 0, (walkb[0][i]*3.3));  
          pwm.setPWM(1, 0, (walkb[1][i]*3.3));  
          pwm.setPWM(2, 0, (walkb[2][i]*3.3));  
          pwm.setPWM(3, 0, (walkb[3][i]*3.3));  
          pwm.setPWM(4, 0, (walkb[4][i]*3.3));  
          pwm.setPWM(5, 0, (walkb[5][i]*3.3)); 
          pwm.setPWM(6, 0, (walkb[6][i]*3.3));  
          pwm.setPWM(7, 0, (walkb[7][i]*3.3)); 
          delay(twait);
        }
        break;        
        
      case 'r':  // Right key
        for (int i=0; i<4; i++){
          pwm.setPWM(0, 0, (walkr[0][i]*3.3));  
          pwm.setPWM(1, 0, (walkr[1][i]*3.3));  
          pwm.setPWM(2, 0, (walkr[2][i]*3.3));  
          pwm.setPWM(3, 0, (walkr[3][i]*3.3));  
          pwm.setPWM(4, 0, (walkr[4][i]*3.3));  
          pwm.setPWM(5, 0, (walkr[5][i]*3.3)); 
          pwm.setPWM(6, 0, (walkr[6][i]*3.3));  
          pwm.setPWM(7, 0, (walkr[7][i]*3.3)); 
          delay(twait);
        }
        break;    

      case 'l':  // Right key
        for (int i=0; i<4; i++){
          pwm.setPWM(0, 0, (walkl[0][i]*3.3));  
          pwm.setPWM(1, 0, (walkl[1][i]*3.3));  
          pwm.setPWM(2, 0, (walkl[2][i]*3.3));  
          pwm.setPWM(3, 0, (walkl[3][i]*3.3));  
          pwm.setPWM(4, 0, (walkl[4][i]*3.3));  
          pwm.setPWM(5, 0, (walkl[5][i]*3.3)); 
          pwm.setPWM(6, 0, (walkl[6][i]*3.3));  
          pwm.setPWM(7, 0, (walkl[7][i]*3.3)); 
          delay(twait);
        }
        break;       
    }     
  }      
  delay(100);
}

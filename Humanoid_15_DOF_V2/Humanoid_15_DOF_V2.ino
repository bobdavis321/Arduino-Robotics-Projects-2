// Humanoid 17 DOF Serial Version 2
// Jan 2016 by Bob Davis
// Mapped as D2 is servo1 
// Mapped as D3 is servo2 
// Etc.
// f=forward, b=back
// r=right l=left
// w=wave s=sit
// c=clap 

//#define SERVOS_PER_TIMER 16
#include <Servo.h>

// Define our Servo's
Servo servo1; // Left Ankle
Servo servo2; // Left Knee
Servo servo3; // Left Hip F-B
Servo servo4; // Left Hip R-L
Servo servo5; // Right Ankle
Servo servo6; // Right Knee
Servo servo7; // Right Hip F-B
Servo servo8; // Right Hip R-L
Servo servo9; // Left Hand
Servo servo10; // Left Elbow
Servo servo11; // Left Shoulder
Servo servo12; // Right Hand
Servo servo13; // Right Elbow
Servo servo14; // Right Shoulder
Servo servo15; // Head
int twait=100; // Sets time delay between steps

byte walkf[8][10] = {
// 0    1    2    3    4    5    6    7    8    9
{ 95, 105, 105, 105, 105,  95,  90,  90,  85,  85}, // Left Ankle
{ 90,  90,  90,  85,  80,  75,  70,  70,  75,  80}, // Knee
{ 90,  90,  90,  85,  80,  75,  70,  70,  75,  80}, // Hip
{ 95, 100, 100, 100, 100,  95,  90,  90,  85,  90}, // Hip
{ 95, 105, 105, 105, 105,  95,  90,  90,  85,  90}, // Right Ankle
{ 90,  90,  90,  85,  80,  75,  70,  70,  75,  80}, // Knee
{ 90,  90,  90,  85,  80,  75,  70,  70,  75,  80}, // Hip
{ 95, 100, 100, 100, 100,  95,  90,  90,  85,  90}, // Hip
};

byte walkb[8][10] = {
// 0    1    2    3    4    5    6    7    8    9
{ 95, 105, 105, 105, 105,  95,  90,  90,  85,  85}, // Left Ankle
{ 90,  90,  90,  95, 100, 105, 110, 110, 105, 100}, // Knee
{ 90,  90,  90,  95, 100, 105, 110, 110, 105, 100}, // Hip
{ 95, 100, 100, 100, 100,  95,  90,  90,  85,  90}, // Hip
{ 95, 105, 105, 105, 105,  95,  90,  90,  85,  90}, // Right Ankle
{ 90,  90,  90,  95, 100, 105, 110, 110, 105, 100}, // Knee
{ 90,  90,  90,  95, 100, 105, 110, 110, 105, 100}, // Hip
{ 95, 100, 100, 100, 100,  95,  90,  90,  85,  90}, // Hip
};

// Turning is a bit tricky because he has to drag his feet
byte turnr[8][10] = {
// 0    1    2    3    4    5    6    7    8    9
{ 95, 100, 100, 100, 100,  95,  90,  90,  90,  90}, // Left Ankle
{ 90,  90,  90,  85,  80,  75,  70,  70,  75,  80}, // Knee
{ 90,  90,  90,  85,  80,  75,  70,  70,  75,  80}, // Hip
{ 95, 100, 100, 100, 100,  95,  90,  90,  90,  90}, // Hip
{ 95, 100, 100, 100, 100,  95,  90,  90,  90,  90}, // Right Ankle
{ 90,  90,  90,  85,  80,  75,  70,  75,  80,  85}, // Knee
{ 90,  90,  90,  85,  80,  75,  70,  75,  80,  85}, // Hip
{ 95, 100, 100, 100, 100,  95,  90,  90,  90,  90}, // Hip
};

byte turnl[8][10] = {
// 0    1    2    3    4    5    6    7    8    9
{ 85,  80,  80,  80,  80,  85,  90,  90,  90,  90}, // Left Ankle
{ 90,  90,  90,  95, 100, 105, 110, 110, 105, 100}, // Knee
{ 90,  90,  90,  95, 100, 105, 110, 110, 105, 100}, // Hip
{ 85,  80,  80,  80,  80,  85,  90,  90,  90,  90}, // Hip
{ 85,  80,  80,  80,  80,  85,  90,  90,  90,  90}, // Right Ankle
{ 90,  90,  90,  95, 100, 105, 110, 105, 100,  95}, // Knee
{ 90,  90,  90,  95, 100, 105, 110, 105, 100,  95}, // Hip
{ 85,  80,  80,  80,  80,  85,  90,  90,  90,  90}, // Hip
};

void setup(){
  servo1.attach(2); // servo on digital pin 2
  servo2.attach(3); // servo on digital pin 3
  servo3.attach(4); // servo on digital pin 4
  servo4.attach(5); // servo on digital pin 5
  servo5.attach(6); // servo on digital pin 6
  servo6.attach(7); // servo on digital pin 7
  servo7.attach(8); // servo on digital pin 8
  servo8.attach(9); // servo on digital pin 9
  servo9.attach(10); // servo on digital pin 10
  servo10.attach(11); // servo on digital pin 11
  servo11.attach(12); // servo on digital pin 12
  servo12.attach(13); // servo on digital pin 13
  servo13.attach(14); // servo on digital pin 14 A0
  servo14.attach(15); // servo on digital pin 15 A1
  servo15.attach(16); // servo on digital pin 16 A2

  Serial.begin(9600);
  Serial.print("Ready");

  delay(200);
}

void loop(){
  servo1.write(90); // Return to zero position
  servo2.write(90);  
  servo3.write(90); 
  servo4.write(90); 
  servo5.write(90); 
  servo6.write(90); 
  servo7.write(90); 
  servo8.write(90); 
  servo9.write(90);  
  servo10.write(90); 
  servo11.write(90);  
  servo12.write(90);// 160=Left Shoulder down 
  servo13.write(90); 
  servo14.write(90); 
  servo15.write(90); // Head

  if ( Serial.available()) {
    char sinch = Serial.read();
    // Test out the servos 2 at a time
    switch(sinch) {
      case '1':
        servo1.write(60); //1=Feet
        servo5.write(60); 
        delay(twait*2);
        servo1.write(120); 
        servo5.write(120); 
        delay(twait*2);
        break;

      case '2':
        servo2.write(60); //2=Knees
        servo6.write(60); 
        delay(twait*2);
        servo2.write(120); 
        servo6.write(120); 
        delay(twait*2);
        break;

      case '3':
        servo3.write(60); //3=Hips
        servo7.write(60); 
        delay(twait*2);
        servo3.write(120); 
        servo7.write(120); 
        delay(twait*2);
        break;

      case '4':
        servo4.write(60); //4=Hips
        servo8.write(60); 
        delay(twait*2);
        servo4.write(120); 
        servo8.write(120); 
        delay(twait*2);
        break;

      case '5':
        servo9.write(60); //5=hand
        servo12.write(60); 
        delay(twait*2);
        servo9.write(120); 
        servo12.write(120); 
        delay(twait*2);
        break;

      case '6':
        servo10.write(60); //6=wrist
        servo13.write(60); 
        delay(twait*2);
        servo10.write(120); 
        servo13.write(120); 
        delay(twait*2);
        break;

      case '7':
        servo11.write(60); //7=elbow    
        servo14.write(60);     
        delay(twait*2);
        servo11.write(120); 
        servo14.write(120); 
        delay(twait*2);
        break;

      case '8':  //Head
        servo15.write(60);  
        delay(twait*2);
        servo15.write(120);
        break;

      case 's': // squat/sit down
        servo2.write(160);
        servo3.write(160);
        servo6.write(20);
        servo7.write(20);
        delay(twait*20);
        break;

      case 'w': // wave hand
        servo11.write(10);  //shoulder
        servo9.write(100);
        delay(twait*5);
        servo9.write(160);
        delay(twait*5);
        servo9.write(100);
        delay(twait*5);
        servo9.write(160);
        delay(twait*5);
        servo9.write(100);
        delay(twait*5);
        break;
        
        
      case 'c': // Clap hands
        servo11.write(30); // move arms forward
        servo14.write(150); // move arms forward
        servo10.write(160);
        servo13.write(10);
        servo9.write(150);
        servo12.write(40);
        delay(twait*5);  
        servo9.write(40); //pinch hands
        servo12.write(150);
        delay(twait*5);
        servo9.write(150); //open hands
        servo12.write(40);
        delay(twait*5);
        servo9.write(40); //pinch hands
        servo12.write(150);
        delay(twait*5);
        servo9.write(150); //open hands
        servo12.write(40);
        delay(twait*5);
        break;        

      // Sequential operations 
      case 'r': // right key;
        for (int i=0; i<10; i++){
          servo1.write(turnr[0][i]);  
          servo2.write(turnr[1][i]);  
          servo3.write(turnr[2][i]);  
          servo4.write(turnr[3][i]);  
          servo5.write(turnr[4][i]);  
          servo6.write(turnr[5][i]); 
          servo7.write(turnr[6][i]);  
          servo8.write(turnr[7][i]); 
          delay(twait);
        }
        break;        
      case 'b':  // back key
        for (int i=0; i<10; i++){
          servo1.write(walkb[0][i]);  
          servo2.write(walkb[1][i]);  
          servo3.write(walkb[2][i]);  
          servo4.write(walkb[3][i]);  
          servo5.write(walkb[4][i]);  
          servo6.write(walkb[5][i]); 
          servo7.write(walkb[6][i]);  
          servo8.write(walkb[7][i]); 
          delay(twait);
        }
        break;        
      case 'l': // left key;
        for (int i=0; i<10; i++){
          servo1.write(turnl[0][i]);  
          servo2.write(turnl[1][i]);  
          servo3.write(turnl[2][i]);  
          servo4.write(turnl[3][i]);  
          servo5.write(turnl[4][i]);  
          servo6.write(turnl[5][i]); 
          servo7.write(turnl[6][i]);  
          servo8.write(turnl[7][i]); 
          delay(twait);
        }
        break;        
      case 'f': // forward key
        for (int i=0; i<10; i++){
          servo1.write(walkf[0][i]);  
          servo2.write(walkf[1][i]);  
          servo3.write(walkf[2][i]);  
          servo4.write(walkf[3][i]);  
          servo5.write(walkf[4][i]);  
          servo6.write(walkf[5][i]); 
          servo7.write(walkf[6][i]);  
          servo8.write(walkf[7][i]); 
          delay(twait);
        }
        break;        
    }
  }
}  // End of program

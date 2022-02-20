/*****************************************
Robotics-Ultrasonic Tank with Turret
Uses HC-SR04 ultrasonic range
Two L298 Motor Controllers
 
   The Circuit:
 * Tank Motors on 6, 7, 8, 9
 * Turret Motors on 2, 3, 4, 5
 * Headlights on 13
 * Fire Motor on 12
   Commands:
 * l,r Left Right
 * f,b Forward, Back
 * h headlignts: on, off
 * u,d Turret Up Down
 * e,k Turret Right, Left
 * o Fire Missile
 
Adapted from code written by Others by Bob Davis
****************************************/
#define echoPin 14 // Echo Pin
#define trigPin 15 // Trigger Pin
int headlight =13;
int lights =0;
int fire =12;
int duration;
//int distance; // used to calculate right distance
char INBYTE;
int motorT1A =2;
int motorT1B =3;
int motorT2A =4;
int motorT2B =5;
int motor1A =6;
int motor1B =7;
int motor2A =8;
int motor2B =9;

void setup() {
//  Serial.begin(115200); 
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motorT1A, OUTPUT);
  pinMode(motorT1B, OUTPUT);
  pinMode(motorT2A, OUTPUT);  
  pinMode(motorT2B, OUTPUT);
  pinMode(headlight, OUTPUT);
  pinMode(fire, OUTPUT);
}

void loop() {

  // read next available byte  
  if( Serial.available() > 0 ) { 
    INBYTE = Serial.read();        
  }
  
  // Motor control
  if (INBYTE == 'f'){
    // Run straight forward
    digitalWrite (motor1A, HIGH);
    digitalWrite (motor1B, LOW);
    digitalWrite (motor2A, HIGH);
    digitalWrite (motor2B, LOW);
    delay(500);
  }
  if (INBYTE == 'b'){
  // Back up 
    digitalWrite (motor1A, LOW);
    digitalWrite (motor1B, HIGH);
    digitalWrite (motor2A, LOW);
    digitalWrite (motor2B, HIGH);
    delay(500);
  }
  if (INBYTE == 'r'){
  // turn right
    digitalWrite (motor1A, LOW);
    digitalWrite (motor1B, HIGH);
    digitalWrite (motor2A, HIGH);
    digitalWrite (motor2B, LOW);
    delay(500);
  }
  if (INBYTE == 'l'){
  // turn left
    digitalWrite (motor1A, HIGH);
    digitalWrite (motor1B, LOW);
    digitalWrite (motor2A, LOW);
    digitalWrite (motor2B, HIGH);
    delay(500);
  }
  if (INBYTE == 'u'){
  // Up
    digitalWrite (motorT1A, HIGH);
    digitalWrite (motorT1B, LOW);
    delay(500);
  }
  if (INBYTE == 'd'){
  // Down 
    digitalWrite (motorT1A, LOW);
    digitalWrite (motorT1B, HIGH);
    delay(500);
  }
  if (INBYTE == 'k'){
  // Left
    digitalWrite (motorT2A, HIGH);
    digitalWrite (motorT2B, LOW);
    delay(500);
  }
  if (INBYTE == 'e'){
  // Right
    digitalWrite (motorT2A, LOW);
    digitalWrite (motorT2B, HIGH);
    delay(500);
  }
  if (INBYTE == 'o'){
  // Fire
    digitalWrite (fire, HIGH);
    delay(900);
  }
  if (INBYTE == 'h'){
    if (lights=="0") {
      digitalWrite (headlight, HIGH);
      lights="1";
    }
    else {
      digitalWrite (headlight, LOW);
      lights="0";
    }
  }
  if (INBYTE == 'o'){
    digitalWrite (fire, HIGH);
    delay(300);
  }

  
  // Stop and wait for next command
  INBYTE='n';
  digitalWrite (fire, LOW);
  digitalWrite (motor1A, LOW);
  digitalWrite (motor1B, LOW);
  digitalWrite (motor2A, LOW);
  digitalWrite (motor2B, LOW);
  digitalWrite (motorT1A, LOW);
  digitalWrite (motorT1B, LOW);
  digitalWrite (motorT2A, LOW);
  digitalWrite (motorT2B, LOW);
}

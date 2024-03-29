/* 
 Program to control six servos on D2 to D7
 Reads analog 0 to 5 and maps to servos
*/

#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int apin1 = A0;
int apin2 = A1;
int apin3 = A2;
int apin4 = A3;
int apin5 = A4;
int apin6 = A5;

void setup() {
 servo1.attach(2);
 servo2.attach(3);
 servo3.attach(4);
 servo4.attach(5);
 servo5.attach(6);
 servo6.attach(7);

 servo1.write(90); // Default positions
 servo2.write(90);
 servo3.write(90);
 servo4.write(90);
 servo5.write(90);
 servo6.write(90);
}

void loop() {
 int val1 = analogRead(apin1);
 int val2 = analogRead(apin2);
 int val3 = analogRead(apin3);
 int val4 = analogRead(apin4);
 int val5 = analogRead(apin5);
 int val6 = analogRead(apin6);

 int mval1 = map(val1, 10, 1024, 0, 180);
 int mval2 = map(val2, 10, 1024, 0, 180);
 int mval3 = map(val3, 10, 1024, 0, 180);
 int mval4 = map(val4, 10, 1024, 0, 180);
 int mval5 = map(val5, 10, 1024, 0, 180);
 int mval6 = map(val6, 10, 1024, 0, 180);

 servo1.write(mval1);
 servo2.write(mval2);
 servo3.write(mval3);
 servo4.write(mval4);
 servo5.write(mval5);
 servo6.write(mval6);

 delay(50);
}

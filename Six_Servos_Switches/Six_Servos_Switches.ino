/* 
 Program to control six servos on D2 to D7
 Reads analog 0 to 5 and maps to servos
*/

#include <Servo.h>
int pmillis=100;
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

int mval1 = 90;
int mval2 = 90;
int mval3 = 90;
int mval4 = 90;
int mval5 = 90;
int mval6 = 90;

void setup() {
 Serial.begin(9600); 
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
 if (val1 < 200) mval1--;
 if (val1 > 800) mval1++;
 int val2 = analogRead(apin2);
 if (val2 < 200) mval2--;
 if (val2 > 800) mval2++;
 int val3 = analogRead(apin3);
 if (val3 < 200) mval3--;
 if (val3 > 800) mval3++;
 int val4 = analogRead(apin4);
 if (val4 < 200) mval4--;
 if (val4 > 800) mval4++;
 int val5 = analogRead(apin5);
 if (val5 < 200) mval5--;
 if (val5 > 800) mval5++;
 int val6 = analogRead(apin6);
 if (val6 < 200) mval6--;
 if (val6 > 800) mval6++;

 servo1.write(mval1);
 servo2.write(mval2);
 servo3.write(mval3);
 servo4.write(mval4);
 servo5.write(mval5);
 servo6.write(mval6);

  Serial.print("Servo1:");
  Serial.print(mval1);
  Serial.print(" Servo2:");
  Serial.print(mval2);
  Serial.print(" Servo3:");
  Serial.print(mval3);
  Serial.print(" Servo4:");
  Serial.print(mval4);
  Serial.print(" Servo5:");
  Serial.print(mval5);
  Serial.print(" Servo6:");
  Serial.println(mval6);
 
 delay(100);
}

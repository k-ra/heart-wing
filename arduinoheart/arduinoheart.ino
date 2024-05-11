#include <Servo.h>

Servo servoleft;  // create servo object to control a servo
Servo servoright;  // create servo object to control a servo

// 16 servo objects can be created on the ESP32

int posl = 0;    // variable to store the servo position
int posr = 180;    // variable to store the servo position


int servoPinl = 13;
int servoPinr = 12;
const int numKeys = 6;
const int buttons[numKeys] = {A0, A1, A2, A3, A4, A5}; // The keys will be connected to these pins on the Arduino
const int notes[numKeys] = {19, 24, 35, 46, 56, 87};
int goal[numKeys] = {0, 18, 36, 54, 72, 90};
static bool lastState[numKeys] = {false}; 

void setup() {
  Serial.begin(9600);
	servoleft.attach(servoPinl, 1000, 2000); // attaches the servo on pin 18 to the servo object
	servoright.attach(servoPinr, 1000, 2000); // attaches the servo on pin 18 to the servo object
}

void loop() {
  for (int i = 0; i < numKeys; i++) {
    bool currentState = digitalRead(buttons[i]) == HIGH;
    if (currentState && !lastState[i]) { 
      Serial.write(i);
      shift(servoleft.read(), goal[i]);
    }
    lastState[i] = currentState; // Update last state
  }
}
//all positions are left 
// shift (servoleft.read(), goal[buttonPin])
void shift(int pos, int goal) {
  if (pos < goal) {
    for (int newpos = pos; newpos <= goal; newpos++) {
      servoleft.write(newpos);         
      servoright.write(90 - newpos);    // Move right wing to '90 - pos' degrees
      delay(4);                     // Wait 12ms for the servos to reach the position
    }
  }
  else if (pos > goal) {
    for (int newpos = pos; newpos >= goal; newpos--) {
    servoleft.write(newpos);          // Move left wing to 'pos' degrees
    servoright.write(90 - newpos);    // Move right wing to '90 - pos' degrees
    delay(4);                     // Wait 12ms for the servos to reach the position
   }
  }
}
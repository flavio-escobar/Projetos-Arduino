#include "TimerOne.h"

void setup(){
  pinMode(13, OUTPUT);
  Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}

void callback(){
  digitalWrite(13, digitalRead(13) ^ 1);
}

void loop() {
  delay(500);
}

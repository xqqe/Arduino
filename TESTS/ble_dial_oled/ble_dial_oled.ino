//remember to check that the board is not set to the 'sense' version



#include "variables.h"
#include "functions.h"



void setup() {

  u8g2.begin();
  pinMode(dial_butt, INPUT_PULLUP);
  pinMode (dialA, INPUT);
  pinMode (dialB, INPUT);
  pinALast = digitalRead(dialA);
  
  Serial.begin(115200);
  update_display();
  Keyboard.begin();

}

void loop() {
  updatetime();

  checkDial();

}



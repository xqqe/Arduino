#include "variables.h"
#include "functions.h"

void setup() {
  // put your setup code here, to run once:
  
  u8g2.begin();
  pinMode(pause_butt, INPUT_PULLUP);
  pinMode(dial_butt, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  pinMode (dialA, INPUT);
  pinMode (dialB, INPUT);
  pinALast = digitalRead(dialA);

  
  
  Serial.begin(9600);
  Serial.println("BEGIN");
  update_display();
}

void loop() {
  // put your main code here, to run repeatedly:
if (endGame == false)
{
  readpausebutt();

  updatetime();

  checkDial();
  
  loseState();
}
}

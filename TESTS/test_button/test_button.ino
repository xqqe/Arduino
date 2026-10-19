int button = 2;

unsigned long lasttime = 0;
int buttondelay = 400;
unsigned long lastbuttonpress = 0;
unsigned long pause_lastbuttonpress = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);

  Serial.println("begin");
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (digitalRead(button) == HIGH && millis() - pause_lastbuttonpress >= buttondelay) //HIGH is not pressed --> NOT COUNTING, PAUSED
//  {
//    
//  }

  if (digitalRead(button) == LOW && millis() - pause_lastbuttonpress >= buttondelay) //LOW is pressed --> COUNTING
  {
      Serial.println(""); //newline
      Serial.println("UNPAUSED");
    
  }
delay(3000);
Serial.println("go");

}

#include <RGBLed.h>

int pause_button = 35;
int joystick_push = 2;
int joystick_x = 16;
int joystick_y = 17;

int rgb_red = 8;
int rgb_blue = 9;
int rgb_green = 10;
int rgb_push = 7;

//debounce variables
unsigned long lasttime = 0;
unsigned long buttondelay = 400;
unsigned long lastbuttonpress = 0;
unsigned long rgb_lastbuttonpress = 0;
unsigned long pause_lastbuttonpress = 0;

RGBLed rgb_butt(rgb_red, rgb_green, rgb_blue, RGBLed::COMMON_ANODE);


int colorpicker = 0;
int* colors[7] = {RGBLed::RED, RGBLed::GREEN, RGBLed::BLUE, RGBLed::MAGENTA, RGBLed::CYAN, RGBLed::YELLOW, RGBLed::WHITE};


void setup() {
  //declaring all inputs/outputs
  pinMode(joystick_push, INPUT_PULLUP);
  pinMode(pause_button, INPUT_PULLUP);
  pinMode(rgb_push, INPUT_PULLUP);
  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  pinMode(rgb_green, OUTPUT);

  //turning all lights off
  digitalWrite(rgb_red, HIGH);
  digitalWrite(rgb_green, HIGH);
  digitalWrite(rgb_blue, HIGH);
  Serial.begin (9600);
  Serial.println("test");
}

void loop() {
  // put your main code here, to run repeatedly:

//
//if (digitalRead(rgb_push) == LOW && millis() - rgb_lastbuttonpress >= buttondelay)
//{
//  rgb_lastbuttonpress = millis();
//  
//  Serial.println("button pressed");
//  //delay(600);
//}



  if (digitalRead(pause_button) == HIGH && millis() - pause_lastbuttonpress >= buttondelay) //HIGH is not pressed --> NOT COUNTING, PAUSED
  {
    digitalWrite(rgb_red, HIGH);
    digitalWrite(rgb_green, HIGH);
    digitalWrite(rgb_blue, HIGH);
  }

  if (digitalRead(pause_button) == LOW && millis() - pause_lastbuttonpress >= buttondelay) //LOW is pressed --> COUNTING
  {

    //RGB BUTTON CONTROL
    if (digitalRead(rgb_push) == LOW && millis() - rgb_lastbuttonpress >= buttondelay)
    {
      if (colorpicker >= 6)
        colorpicker = -1;

      rgb_butt.setColor(colors[++colorpicker]);
      delay(500);
      Serial.println(colorpicker);
      delay(400);
    }
  }

      

    //JOYSTICK CONTROL
    //    int xVal, yVal, buttonVal;
    //
    //    xVal = analogRead (joystick_x);
    //    yVal = analogRead (joystick_y);
    //    buttonVal = digitalRead (joystick_push);
    //
    //
    //    if (xVal < 20) //left
    //    {
    //      if (colorpicker >= 6)
    //        colorpicker = -1;
    //
    //      rgb_butt.setColor(colors[++colorpicker]);
    //      Serial.println(colorpicker);
    //      delay(400);
    //    }
    //
    //    if (xVal > 1000) //right
    //    {
    //      if (colorpicker <= 0)
    //        colorpicker = 7;
    //
    //      rgb_butt.setColor(colors[--colorpicker]);
    //      Serial.println(colorpicker);
    //      delay(400);
    //    }
}

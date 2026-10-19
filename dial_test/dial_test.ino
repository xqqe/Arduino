#include <RGBLed.h>


int pause_button = 35;
int joystick_push = 2;
int joystick_x = 16;
int joystick_y = 17;

int rgb_red = 8;
int rgb_blue = 9;
int rgb_green = 10;
int rgb_push = 7;

int dialA = 3;
int dialB = 2;
int dial_butt = 4;

int encoderPosCount = 0;
int lastWhole;

int pinALast = 0;
int aVal = 0;
boolean bCW;

int diff = 0;

//debounce variables
unsigned long lasttime = 0;
unsigned long buttondelay = 400;
unsigned long lastbuttonpress = 0;
unsigned long rgb_lastbuttonpress = 0;
unsigned long pause_lastbuttonpress = 0;
unsigned long dial_lastbuttonpress = 0;
unsigned long dial_spin = 0;

RGBLed rgb_butt(rgb_red, rgb_green, rgb_blue, RGBLed::COMMON_ANODE);
int colorpicker = 0;
int* colors[7] = {RGBLed::RED, RGBLed::GREEN, RGBLed::BLUE, RGBLed::MAGENTA, RGBLed::CYAN, RGBLed::YELLOW, RGBLed::WHITE};

int life = 15;


void setup() {
  // put your setup code here, to run once:
  pinMode (dialA, INPUT);
  pinMode (dialB, INPUT);
  /* Read Pin A
    Whatever state it's in will reflect the last position
  */
  pinALast = digitalRead(dialA);

  pinMode(joystick_push, INPUT_PULLUP);
  pinMode(pause_button, INPUT_PULLUP);
  pinMode(dial_butt, INPUT_PULLUP);
  pinMode(rgb_push, INPUT_PULLUP);
  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  pinMode(rgb_green, OUTPUT);

  //turning all lights off
  digitalWrite(rgb_red, LOW);
  digitalWrite(rgb_green, LOW);
  digitalWrite(rgb_blue, LOW);


  Serial.begin (9600);

  Serial.println("START");
  Serial.println(pinALast);
  Serial.println(aVal);
}

void loop() {
  // put your main code here, to run repeatedly:
  aVal = digitalRead(dialA);
  if (aVal != pinALast)
  { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.

    if (digitalRead(dialB) != aVal) // Means pin A Changed first - We're Rotating Clockwise
    {
      encoderPosCount++;
      if (encoderPosCount % 2 != 0)
      {
        if (lastWhole != encoderPosCount)
        {
          life++;
          Serial.println(pinALast);
          Serial.println(aVal);
          Serial.print("Encoder Position: ");
          Serial.println(encoderPosCount);
          Serial.print("life: ");
          Serial.println(life);
        }
        lastWhole = encoderPosCount;
      }
    } 
    else // Otherwise B changed first and we're moving CCW
    {

      encoderPosCount--;

      if (encoderPosCount % 2 != 0)
      {
        if (lastWhole != encoderPosCount)
        {
          life--;
          Serial.println(pinALast);
          Serial.println(aVal);
          Serial.print("Encoder Position: ");
          Serial.println(encoderPosCount);
          Serial.print("life: ");
          Serial.println(life);
        }
        lastWhole = encoderPosCount;
      }
    }
  }
  pinALast = aVal;

  if (digitalRead(dial_butt) == LOW && millis() - dial_lastbuttonpress >= buttondelay)
  {
    dial_lastbuttonpress = millis();

    Serial.println("dial button pressed");
    //delay(600);
  }

  if (digitalRead(rgb_push) == LOW && millis() - rgb_lastbuttonpress >= buttondelay)
  {
    rgb_lastbuttonpress = millis();

    Serial.println("RGB button pressed");

  }

}

int button = 2;

unsigned long lasttime = 0;
int buttondelay = 400;
unsigned long lastbuttonpress = 0;
unsigned long pause_lastbuttonpress = 0;

#include <Arduino.h>
#include <U8g2lib.h>

#define DEFAULT_TIME 4500000

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  u8g2.begin();
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
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_human_1x_t); 
  u8g2.drawStr(120,10,"\x42\xcf");  //heart
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(100,10, "40"); //life
  
  u8g2.setFont(u8g2_font_cursor_tf);
  u8g2.drawStr(8,12,"\x78\xcf");  //bug
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(20,10,"0"); //infect

  u8g2.setFont(u8g2_font_lucasfont_alternate_tr); 
  u8g2.drawStr(55,10,"SARA");  //name
  u8g2.sendBuffer();
}

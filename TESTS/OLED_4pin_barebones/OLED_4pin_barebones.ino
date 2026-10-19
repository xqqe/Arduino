/*

  GraphicsTest.ino
  using OLED with only SCL/SDA pins

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
*/


#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


//called by draw function
void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void draw(void) {
  u8g2_prepare();
  u8g2.drawStr(0, 0, "Bitmap overlay");

}



void setup(void) {
  u8g2.begin();
}

void loop(void) {
  // picture loop  
  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();

  // deley between each page
  delay(100);

}

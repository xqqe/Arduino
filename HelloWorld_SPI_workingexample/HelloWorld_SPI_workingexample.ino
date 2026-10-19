

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_a(U8G2_R0, /* cs=*/ 49, /* dc=*/ 48, /* reset=*/42);
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_b(U8G2_R0, /* cs=*/ 45, /* dc=*/ 46, /* reset=*/ 47);
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_c(U8G2_R0, /* cs=*/ 39, /* dc=*/ 40, /* reset=*/ 41);
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_d(U8G2_R0, /* cs=*/ 29, /* dc=*/ 30, /* reset=*/ 31);
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_e(U8G2_R0, /* cs=*/ 23, /* dc=*/ 24, /* reset=*/ 25);


void setup(void) {
  u8g2_a.begin();
  u8g2_b.begin();
  u8g2_c.begin();
  u8g2_d.begin();
  u8g2_e.begin();
}

void loop(void) {
  u8g2_a.clearBuffer();					// clear the internal memory
  u8g2_a.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2_a.drawStr(0,10,"You");	// write something to the internal memory
  u8g2_a.sendBuffer();					// transfer internal memory to the display
  delay(1000);  

    u8g2_b.clearBuffer();          // clear the internal memory
  u8g2_b.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2_b.drawStr(0,10,"want"); // write something to the internal memory
  u8g2_b.sendBuffer();          // transfer internal memory to the display
  delay(1000); 

      u8g2_c.clearBuffer();          // clear the internal memory
  u8g2_c.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2_c.drawStr(0,10,"brownies"); // write something to the internal memory
  u8g2_c.sendBuffer();          // transfer internal memory to the display
  delay(1000); 

      u8g2_d.clearBuffer();          // clear the internal memory
  u8g2_d.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2_d.drawStr(0,10,"covered with"); // write something to the internal memory
  u8g2_d.sendBuffer();          // transfer internal memory to the display
  delay(1000); 

      u8g2_e.clearBuffer();          // clear the internal memory
  u8g2_e.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2_e.drawStr(0,10,"ice cream"); // write something to the internal memory
  u8g2_e.sendBuffer();          // transfer internal memory to the display
  delay(1000); 
}

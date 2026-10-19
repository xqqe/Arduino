#include <Arduino.h>
#include <U8g2lib.h>


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);




void setup() {
  // put your setup code here, to run once:
u8g2.begin();
u8g2.setI2CAddress(0x78);

}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_human_1x_t); 
  u8g2.drawStr(120,10,"\x42\xcf");  //heart
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(100,10,"40"); //life
  
  u8g2.setFont(u8g2_font_cursor_tf);
  u8g2.drawStr(8,12,"\x78\xcf");  //bug
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(20,10,"0"); //infect

  u8g2.setFont(u8g2_font_lucasfont_alternate_tr); 
  u8g2.drawStr(55,10,"SARA");  //name
  u8g2.sendBuffer();

//u8g2.firstPage();
//  do {
//  u8g2.setFont(u8g2_font_open_iconic_human_1x_t); 
//  u8g2.drawStr(120,10,"\x42\xcf");  //heart
//  u8g2.setFont(u8g2_font_artossans8_8n);
//  u8g2.drawStr(100,10,"40"); //life
//  
//  u8g2.setFont(u8g2_font_cursor_tf);
//  u8g2.drawStr(8,12,"\x78\xcf");  //bug
//  u8g2.setFont(u8g2_font_artossans8_8n);
//  u8g2.drawStr(20,10,"0"); //infect
//
//  u8g2.setFont(u8g2_font_lucasfont_alternate_tr); 
//  u8g2.drawStr(55,10,"SARA");  //name
//  } while ( u8g2.nextPage() );
 
}

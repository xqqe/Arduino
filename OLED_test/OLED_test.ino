

#include <Arduino.h>
#include <U8g2lib.h>

#define DEFAULT_TIME 4500000

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

char buff[30];
unsigned long totaltime = 0;
unsigned long playertime = 30000;
unsigned long lasttime = 0;

unsigned long p_sec = 0;
unsigned long p_min = 0;
unsigned long p_hour = 0;

unsigned long t_sec = 0;
unsigned long t_min = 0;
unsigned long t_hour = 0;

int life = 40;
int infect = 0;

void updateTotalTime(unsigned long ttime)
{
     t_sec = (ttime / 1000) % 60;
     t_min = (ttime / 60000) % 60;
     t_hour = ttime / 3600000;
}

void updatePlayerTime(unsigned long ptime)
{
     p_sec = (ptime / 1000) % 60;
     p_min = (ptime / 60000) % 60;
     p_hour = ptime / 3600000;
}

void updateTime () 
{
  if (millis() - lasttime >= 1000) //determines amount of time passed
    {
      lasttime = millis(); //restarts time countin
      if (playertime < 1000) 
        playertime = 0;
      else
        playertime -= 1000;
        
      totaltime += 1000;
      
      updateTotalTime(totaltime);
      updatePlayerTime(playertime);

      
    }
}

 void showPlayerData()
 {
  u8g2.setFont(u8g2_font_open_iconic_human_1x_t); 
  u8g2.drawStr(120,10,"\x42\xcf");  //heart
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(100,10, life); //life
  
  u8g2.setFont(u8g2_font_cursor_tf);
  u8g2.drawStr(8,12,"\x78\xcf");  //bug
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(20,10,"0"); //infect

  u8g2.setFont(u8g2_font_lucasfont_alternate_tr); 
  u8g2.drawStr(55,10,"SARA");  //name
 }

 void update_display ()
 {
  u8g2.clearBuffer();

    sprintf(buff, "%02ld:%02ld:%02ld", t_hour, t_min, t_sec);
    u8g2.setFont(u8g2_font_courB08_tf);  // choose a suitable font
    u8g2.drawStr(40,58,buff);  // write something to the internal memory

    sprintf(buff, "%02ld:%02ld:%02ld", p_hour, p_min, p_sec);
    u8g2.setFont(u8g2_font_courB18_tf);  // choose a suitable font
    u8g2.drawStr(5,40,buff);  // write something to the internal memory

  
  showPlayerData();
  u8g2.sendBuffer();
 }

void setup(void) {
  u8g2.begin();
  
}

void loop(void) 
{
  
  
  updateTime();
  update_display();
}

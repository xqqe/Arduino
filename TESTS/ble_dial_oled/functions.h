#include <Arduino.h>
#include <U8g2lib.h>
#include <BLE52_Mouse_and_Keyboard.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

 void showPlayerData()
 {
  u8g2.setFont(u8g2_font_open_iconic_human_1x_t); 
  u8g2.drawStr(120,10,"\x42\xcf");  //heart
  sprintf(buff, "%02d", life);
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(100,10,buff); //life
  //u8g2.drawStr(100,10,life); //life
  
  u8g2.setFont(u8g2_font_cursor_tf);
  u8g2.drawStr(8,12,"\x78\xcf");  //bug
  sprintf(buff, "%d", infect);
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(20,10,buff); //infect
  //u8g2.drawStr(20,10,infect); //infect

  u8g2.setFont(u8g2_font_lucasfont_alternate_tr); 
  u8g2.drawStr(55,10,p_name);  //name
 }

  void update_display ()
 {
  u8g2.clearBuffer();

    sprintf(buff, "%02ld:%02ld:%02ld", t_hour, t_min, t_sec);
    u8g2.setFont(u8g2_font_courB08_tf);  // choose a suitable font
    u8g2.drawStr(40,58,buff);  // write something to the internal memory

    sprintf(buff, "%02ld:%02ld:%02ld", hhour, mmin, sec);
    u8g2.setFont(u8g2_font_courB18_tf);  // choose a suitable font
    u8g2.drawStr(5,40,buff);  // write something to the internal memory

  
  showPlayerData();
  u8g2.sendBuffer();
 }


void updateplayertime()
{
  sec = (timems / 1000) % 60;
  mmin = (timems / 60000) % 60;
  hhour = timems / 3600000;

  sprintf(buff, "%s: %02ld:%02ld:%02ld", p_name, hhour, mmin, sec);
  //Serial.println(buff);
  update_display();
}

void updatetotaltime(unsigned long lasttime)
{
  t_sec = (lasttime / 1000) % 60;
  t_min = (lasttime / 60000) % 60;
  t_hour = lasttime / 3600000;

  //Serial.println("");
  sprintf(buff, "Total Time: %02ld:%02ld:%02ld", t_hour, t_min, t_sec);
  //Serial.println(buff);    //prints total time
  update_display();
}


void updatetime()
{
  if (pause_state == false)
  {
    if (millis() - lasttime - pause_time >= 1000) //determines amount of time passed
    {
      lasttime = millis() - pause_time; //restarts time counting

      //decreasing players time
      timems -= 1000;

      updatetotaltime(lasttime);
      updateplayertime(); //prints players time
    }
  }
}

void updatelife() //needs to be updated so each player can change their life at any time -- requires all the dials hooked up
{
  aVal = digitalRead(dialA);
  if (aVal != pinALast)
  { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    Serial.print(p_name);

    if (digitalRead(dialB) != aVal) // Means pin A Changed first - We're Rotating Clockwise
    {
      encoderPosCount++;
      if (encoderPosCount % 2 != 0)
      {
        if (lastWhole != encoderPosCount)
        {
          life--;
          Mouse.move(0, 0, -1);
          update_display();
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
          life++;
          Mouse.move(0, 0, 1);
          update_display();
        }
        lastWhole = encoderPosCount;
      }
    }
  }
  pinALast = aVal;
}

void checkDial()
{
  if (digitalRead(dial_butt) == LOW && millis() - dial_lastbuttonpress >= buttondelay)
  {
    dial_lastbuttonpress = millis();
    // Keyboard.press(KEY_LEFT_CTRL);    //do a control-x
    // Keyboard.write('a');              //press and release 'x' key
    // Keyboard.releaseAll();            //release the control
    // Keyboard.press(KEY_DELETE);    //do a control-x
    // Keyboard.releaseAll();

  }
  updatelife();
}

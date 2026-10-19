#include <RGBLed.h>
#include "thevariables.h"
#include "thefunctions.h"

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 49, /* dc=*/ 48, /* reset=*/42);

void setup()
{
  pinMode(pause_butt, INPUT_PULLUP);
  pinMode(rgb_butt, INPUT_PULLUP);
  pinMode(dial_butt, INPUT_PULLUP);

  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  pinMode(rgb_green, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode (dialA, INPUT);
  pinMode (dialB, INPUT);
  pinALast = digitalRead(dialA);

  //turning all lights ON
  digitalWrite(rgb_red, LOW);
  digitalWrite(rgb_green, LOW);
  digitalWrite(rgb_blue, LOW);
  u8g2.begin();
  Serial.begin(9600);
  Serial.println("BEGIN");

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_human_1x_t); 
  u8g2.drawStr(120,10,"\x42\xcf");  //heart
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(80,10, "BEGIN"); //life
  u8g2.sendBuffer();
  
  player_names();
  

    for (int i = 0; i < num_players; i++)
    {
      //players[i] = init_player(i + 1);
      //updateplayertime(players[i]);
      showPlayerData(players[i]);
    }
    Serial.println(" ");
    turnOrder();

    
}

void loop()
{
if (endGame == false)
{
  readpausebutt();

  updatetime();

  readRGBbutt();

  checkDial();
  skipPlayer();
  loseState();
}
  

}

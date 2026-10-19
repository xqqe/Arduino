#include <RGBLed.h>
#include "thevariables.h"
#include "thefunctions.h"



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

  Serial.begin(9600);
  Serial.println("BEGIN");
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

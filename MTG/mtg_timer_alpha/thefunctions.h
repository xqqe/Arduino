#include "names.h"

///////////////////////////////////////////////////FUNCTIONS

void player_names()
{
  int name_array_size = 13;
  randomSeed(analogRead(0));
  
  for (int i = 0; i < num_players; i++)
  {
    int randint = random(0,name_array_size);
    strcpy(players[i].p_name, NAMES[randint]);
    strcpy(NAMES[randint], NAMES[name_array_size]);
    name_array_size--;
  }
}


void pause_game()
{
  pause_state = true;
  pause_lastbuttonpress = millis();
  notpause_counter = 0;


  if (pause_counter < 1)
  {
    last_pausetime = millis();
    pause_counter++;
    Serial.println("");
    Serial.println("PAUSED");
  }
}

void victory_song()
{
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void loseState()
{
  for (int i = 0; i < num_players; i++)
  {
    if ((players[i].p_life <= 0 || players[i].p_infect >= 10 || players[i].p_timems <= 0) && players[i].p_winloss != -1)
    {
      Serial.print(players[i].p_name);
      Serial.println(" loses!");
      players[i].p_winloss = -1;
      c_num_players--;

      Serial.println("Moment of silence for our fallen comrade");
      loss_pause = true;
      pause_game();

      tone(buzzer, 150);
      delay(500);
      tone(buzzer, 100);
      delay(500);
      tone(buzzer, 50);
      delay(750);
      noTone(buzzer);
    }
    if (c_num_players == 1 && players[i].p_winloss != -1)
    {
      players[i].p_winloss = 1;
      Serial.print(players[i].p_name);
      Serial.println(" wins!");
      victory_song();

      endGame = true;
      Serial.print("GAME OVER");
    }
  }
}

void skipPlayer()
{
  while (players[player_num - 1].p_winloss == -1)
  {
    if (player_num < num_players)
      player_num += 1;
    else
      player_num = 1;
  }
}

void showPlayerData(player thisplayer)
{
  sprintf(buff, "%s, %i, %i, %i", thisplayer.p_name, thisplayer.p_life, thisplayer.p_infect, thisplayer.p_color);
  Serial.println(buff);
  Serial.println("---------------------------");
}

void updateplayertime(player thisplayer)
{
  unsigned long sec = (thisplayer.p_timems / 1000) % 60;
  unsigned long mmin = (thisplayer.p_timems / 60000) % 60;
  unsigned long hour = thisplayer.p_timems / 3600000;

  sprintf(buff, "%s: %02ld:%02ld:%02ld", thisplayer.p_name, hour, mmin, sec);
  Serial.println(buff);
}

void updatetotaltime(unsigned long lasttime)
{
  unsigned long t_sec = (lasttime / 1000) % 60;
  unsigned long t_min = (lasttime / 60000) % 60;
  unsigned long t_hour = lasttime / 3600000;

  Serial.println("");
  sprintf(buff, "Total Time: %02ld:%02ld:%02ld", t_hour, t_min, t_sec);
  Serial.println(buff);    //prints total time
}

void readpausebutt()
{
  if (digitalRead(pause_butt) == HIGH && millis() - pause_lastbuttonpress >= buttondelay) //HIGH is not pressed --> NOT COUNTING, PAUSED
  {
    pause_game();
    loss_pause = false;
  }

  if (digitalRead(pause_butt) == LOW && millis() - pause_lastbuttonpress >= buttondelay && loss_pause == false) //LOW is pressed --> COUNTING
  {
    pause_state = false;
    pause_lastbuttonpress = millis();
    pause_counter = 0;

    if (notpause_counter < 1)
    {
      pause_time += millis() - last_pausetime; //updating the total amount of time paused to subtract from total time later
      notpause_counter++; //increases so this loop only executes once
      Serial.println(""); //newline
      Serial.println("UNPAUSED");
    }
  }
}

void readRGBbutt()
{
  if (digitalRead(rgb_butt) == LOW && millis() - lastbuttonpress >= buttondelay) //need to amend for holding button
  {
    lastbuttonpress = millis(); //accounts for debouncing delay; keeps track of last real button press
    //who's turn is it?

    if (player_num < num_players)
      player_num += 1;
    else
      player_num = 1;

    skipPlayer();

    Serial.println(""); //newline
    Serial.print("it's ");
    Serial.print(players[player_num - 1].p_name);
    Serial.println("'s turn");

    tone(buzzer, 50);
    delay(750);
    noTone(buzzer);

    rgb_color.setColor(colors[players[player_num - 1].p_color]);

    showPlayerData(players[player_num - 1]);


  }
}

void updatetime()
{
  if (pause_state == false)
  {
    if (millis() - lasttime - pause_time >= 1000) //determines amount of time passed
    {
      lasttime = millis() - pause_time; //restarts time counting

      //decreasing players time
      players[player_num - 1].p_timems -= 1000;

      updatetotaltime(lasttime);
      updateplayertime(players[player_num - 1]); //prints players time
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

    if (digitalRead(dialB) != aVal) // Means pin A Changed first - We're Rotating Clockwise
    {
      encoderPosCount++;
      if (encoderPosCount % 2 != 0)
      {
        if (lastWhole != encoderPosCount)
        {
          players[player_num - 1].p_life--;
          Serial.print(players[player_num - 1].p_name);
          Serial.print("'s life: ");
          Serial.println(players[player_num - 1].p_life);
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
          players[player_num - 1].p_life++;
          Serial.print(players[player_num - 1].p_name);
          Serial.print("'s life: ");
          Serial.println(players[player_num - 1].p_life);
        }
        lastWhole = encoderPosCount;
      }
    }
  }
  pinALast = aVal;
}


void updateinfect()
{
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
          players[player_num - 1].p_infect--;
          Serial.print(players[player_num - 1].p_name);
          Serial.print("'s infect: ");
          Serial.println(players[player_num - 1].p_infect);;
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

          players[player_num - 1].p_infect++;
          Serial.print(players[player_num - 1].p_name);
          Serial.print("'s infect: ");
          Serial.println(players[player_num - 1].p_infect);
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

    if (dialState == 1)
    {
      dialState = 0;
      //Serial.println("infect");
    }
    else if (dialState == 0)
    {
      dialState = 1;
      //Serial.println("life");
    }
  }

  if (dialState == 1)
  {
    updatelife();
  }
  if (dialState == 0)
  {
    updateinfect();
  }
}

void turnOrder()
{
  player_num = random(1, num_players);
  //Serial.println(player_num);
  Serial.print(players[player_num - 1].p_name);
  Serial.println(" goes first!");
}

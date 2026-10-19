///////////////////////////////////////////////////FUNCTIONS

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

  if (digitalRead(pause_butt) == LOW && millis() - pause_lastbuttonpress >= buttondelay) //LOW is pressed --> COUNTING
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

    if (player_num < max_players)
      player_num += 1;
    else
      player_num = 1;

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
          life++;
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
          Serial.print("life: ");
          Serial.println(life);
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
          infect++;
          Serial.print("infect: ");
          Serial.println(infect);
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
          infect--;
          Serial.print("infect: ");
          Serial.println(infect);
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
      Serial.println("infect");
    }
    else if (dialState == 0)
    {
      dialState = 1;
      Serial.println("life");
    }
    Serial.print("dial state: ");
    Serial.println(dialState);
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

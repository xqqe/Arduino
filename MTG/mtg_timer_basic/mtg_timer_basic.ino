#include <RGBLed.h>

#define DEFAULT_TIME 4500000



char buff[80];

//DEBOUNCE
unsigned long lasttime = 0;
int buttondelay = 400;
unsigned long lastbuttonpress = 0;
unsigned long pause_lastbuttonpress = 0;
unsigned long rgb_lastbuttonpress = 0;
unsigned long dial_lastbuttonpress = 0;

unsigned long pause_time = 0;
unsigned long last_pausetime = 0;
bool pause_state = false;
int pause_counter = 1;
int notpause_counter = 0;

//BUTTON PIN ASSIGNMENTS
int rgb_butt = 7;
int pause_butt = 4;
int dial_butt = 13;
int joystick_butt = 2;
int joystick_x = 16;
int joystick_y = 17;
int rgb_red = 9;
int rgb_blue = 10;
int rgb_green = 11;
int dialA = 5;
int dialB = 3;

//RGB setup
RGBLed rgb_color(rgb_red, rgb_green, rgb_blue, RGBLed::COMMON_ANODE);
int colorpicker = 0;
int* colors[7] = {RGBLed::RED, RGBLed::GREEN, RGBLed::BLUE, RGBLed::MAGENTA, RGBLed::CYAN, RGBLed::YELLOW, RGBLed::WHITE};

//PLAYER DATA
int player_num = 1;
int max_players = 5;
unsigned long playertotaltime = 0;

struct player {
  char p_name[10];
  int p_num;
  unsigned long p_timems;
  int p_life;
  unsigned int p_infect;
  unsigned int p_color;
} players[] = {
  { "Player 1", 1, DEFAULT_TIME, 40, 0, 2 },
  { "Player 2", 2, DEFAULT_TIME, 40, 0, 3 },
  { "Player 3", 3, DEFAULT_TIME, 40, 0, 4 },
  { "Player 4", 4, DEFAULT_TIME, 40, 0, 5 },
  { "Player 5", 5, DEFAULT_TIME, 40, 0, 6 }
};

player init_player(unsigned int player_num)
{
  player newplayer;
  sprintf(newplayer.p_name, "Player %i", player_num) ;
  newplayer.p_timems = DEFAULT_TIME;
  newplayer.p_life = 40;
  newplayer.p_infect = 0;
  newplayer.p_color = 0;
  return newplayer;
}

///////////////////////////////////////////////////FUNCTIONS

void updateplayertime(player thisplayer)
{
  unsigned long sec = (thisplayer.p_timems / 1000) % 60;
  unsigned long mmin = (thisplayer.p_timems / 60000) % 60;
  unsigned long hour = thisplayer.p_timems / 3600000;

  //sprintf(buff, "%s, %02ld:%02ld:%02ld, %i, %d, %d", thisplayer.p_name, hour, mmin, sec, thisplayer.p_life, thisplayer.p_infect, thisplayer.p_commanderd);
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
    Serial.println(""); //newline
    Serial.print("it's ");
    Serial.print(players[player_num].p_name);
    Serial.println("'s turn");
    if (player_num < max_players)
      player_num += 1;
    else
      player_num = 1;
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

void setup()
{
  pinMode(joystick_butt, INPUT_PULLUP);
  pinMode(pause_butt, INPUT_PULLUP);
  pinMode(rgb_butt, INPUT_PULLUP);
  pinMode(dial_butt, INPUT_PULLUP);

  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  pinMode(rgb_green, OUTPUT);

  pinMode (dialA, INPUT);
  pinMode (dialB, INPUT);

  //turning all lights ON
  digitalWrite(rgb_red, LOW);
  digitalWrite(rgb_green, LOW);
  digitalWrite(rgb_blue, LOW);
  Serial.begin(9600);

  for (int i = 0; i < max_players; i++)
  {
    players[i] = init_player(i + 1);
    updateplayertime(players[i]);

  }
}

void loop()
{

  readpausebutt();

  updatetime();

  readRGBbutt();

}


//RGB library
#include <RGBLed.h>

#define DEFAULT_TIME 4500000

//defining button pins
#define pause_butt 4
#define joystick_center 2 
#define joystick_x 16 //range = 20-1000
#define joystick_y 17
#define rgb_red 9
#define rgb_blue 10
#define rgb_green 11
#define rgb_push 1

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RGB setup
RGBLed rgb_butt(rgb_red, rgb_green, rgb_blue, RGBLed::COMMON_ANODE);
int colorpicker = 0;
int* colors[7] = {RGBLed::RED, RGBLed::GREEN, RGBLed::BLUE, RGBLed::MAGENTA, RGBLed::CYAN, RGBLed::YELLOW, RGBLed::WHITE};
int xVal = analogRead (joystick_x);
int yVal = analogRead (joystick_y);
int buttonVal = digitalRead (joystick_center);

//debounce variables
unsigned long lasttime = 0;
int buttondelay = 400;
unsigned long lastbuttonpress = 0;
unsigned long pause_lastbuttonpress = 0;

//pausing variables
unsigned long pause_time = 0;
unsigned long last_pausetime = 0;
bool pause_state = false;
int pause_counter = 1;
int notpause_counter = 0;

char buff[80];

//player setup
int player_num = 1;
int max_players = 5;
unsigned long playertotaltime = 0;

//making the player profiles
struct player {
  char p_name[10];
  int p_num;
  unsigned long p_timems;
  int p_life;
  unsigned int p_infect;
  unsigned int p_commanderd;
} players[] = {
  { "Player 1", 1, DEFAULT_TIME, 40, 0, 0 },
  { "Player 2", 2, DEFAULT_TIME, 40, 0, 0 },
  { "Player 3", 3, DEFAULT_TIME, 40, 0, 0 },
  { "Player 4", 4, DEFAULT_TIME, 40, 0, 0 },
  { "Player 5", 5, DEFAULT_TIME, 40, 0, 0 }
};

//initalizing players
player init_player(unsigned int player_num)
{
  player newplayer;
  sprintf(newplayer.p_name, "Player %i", player_num) ;
  newplayer.p_timems = DEFAULT_TIME;
  newplayer.p_life = 40;
  newplayer.p_infect = 0;
  newplayer.p_commanderd = 0;
  return newplayer;
} 

void updatePlayerTime(player thisplayer) 
{
     unsigned long p_sec = (thisplayer.p_timems / 1000) % 60;
     unsigned long p_min = (thisplayer.p_timems / 60000) % 60;
     unsigned long p_hour = thisplayer.p_timems / 3600000;

    sprintf(buff, "%02ld:%02ld:%02ld", p_hour, p_min, p_sec);
    Serial.println(buff);
}

void updateTotalTime(unsigned long lasttime)
{
     unsigned long t_sec = (lasttime / 1000) % 60;
     unsigned long t_min = (lasttime / 60000) % 60;
     unsigned long t_hour = lasttime / 3600000;

    Serial.println(""); 
    sprintf(buff, "Total Time: %02ld:%02ld:%02ld", t_hour, t_min, t_sec);
    Serial.println(buff);    //prints total time
}

void readPauseButt() 
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

 void readNextPlayer()
 {
    if (digitalRead(rgb_push) == LOW && millis() - lastbuttonpress >= buttondelay) //need to amend for holding button
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

 void updateTime()
 {
    if (pause_state == false) 
  {
    if (millis() - lasttime - pause_time >= 1000) //determines amount of time passed
    {
      lasttime = millis() - pause_time; //restarts time counting

      //decreasing players time
      players[player_num - 1].p_timems -= 1000;
      
      updateTotalTime(lasttime);
      updatePlayerTime(players[player_num - 1]); //prints players time
    }
  }
 }

 void showPlayerData()
 {
//need to make for SPI OLEDs
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  
  pinMode(joystick_center, INPUT_PULLUP);
  pinMode(pause_butt, INPUT_PULLUP);
  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  pinMode(rgb_green, OUTPUT);
  
  //turning all lights off
  digitalWrite(rgb_red, HIGH);
  digitalWrite(rgb_green, HIGH);
  digitalWrite(rgb_blue, HIGH);
  
  Serial.begin(9600);

  for (int i = 0; i < max_players; i++)
  { 
    players[i] = init_player(i+1);
    updatePlayerTime(players[i]);

  }
}

void loop()
{

  //showPlayerData();
  readPauseButt();
  updateTime();
  readNextPlayer();

}

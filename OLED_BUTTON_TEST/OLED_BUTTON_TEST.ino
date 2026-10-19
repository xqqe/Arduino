

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
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

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

char buff[30];
unsigned long totaltime = 0;
unsigned long playertime = 30000;
unsigned int ADDRESS1 = 0x78;

//player setup
int player_num = 1;
int max_players = 5;
unsigned long playertotaltime = 0;

unsigned long p_sec = 0;
unsigned long p_min = 0;
unsigned long p_hour = 0;

unsigned long t_sec = 0;
unsigned long t_min = 0;
unsigned long t_hour = 0;

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
   if (pause_state == false) 
   {
    if (millis() - lasttime >= 1000) //determines amount of time passed
      {
        lasttime = millis(); //restarts time countin
        if (players[player_num - 1].p_timems < 1000) 
          players[player_num - 1].p_timems = 0;
        else
          players[player_num - 1].p_timems -= 1000;
          
        totaltime += 1000;
        
        updateTotalTime(totaltime);
        updatePlayerTime(players[player_num - 1].p_timems); 
      }
   }
}

 void showPlayerData()
 {
  u8g2.setFont(u8g2_font_open_iconic_human_1x_t); 
  u8g2.drawStr(120,10,"\x42\xcf");  //heart
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(100,10,players[player_num].p_life); //life
  
  u8g2.setFont(u8g2_font_cursor_tf);
  u8g2.drawStr(8,12,"\x78\xcf");  //bug
  u8g2.setFont(u8g2_font_artossans8_8n);
  u8g2.drawStr(20,10,players[player_num].p_infect); //infect

  u8g2.setFont(u8g2_font_lucasfont_alternate_tr); 
  u8g2.drawStr(55,10,players[player_num].p_name);  //name
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
  
}

void loop(void) 
{
  readPauseButt();
  readNextPlayer();
  updateTime();
  update_display();
}

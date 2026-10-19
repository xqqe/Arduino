#include "pitches.h"
#define DEFAULT_TIME 60000



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
bool loss_pause = false;
int pause_counter = 1;
int notpause_counter = 0;

//BUTTON PIN ASSIGNMENTS
int rgb_butt = 7;
int pause_butt = 35;
int dial_butt = 4;
int rgb_red = 8;
int rgb_blue = 9;
int rgb_green = 10;
int dialA = 3;
int dialB = 2;
int buzzer = 6;

//dial setup
int pinALast = 0;
int aVal = 0;
int lastWhole;
int encoderPosCount = 0;
int dialState = 1; //1 is life, 0 is infect


//RGB setup
RGBLed rgb_color(rgb_red, rgb_green, rgb_blue, RGBLed::COMMON_ANODE);
int colorpicker = 0;
int* colors[7] = {RGBLed::RED, RGBLed::GREEN, RGBLed::BLUE, RGBLed::MAGENTA, RGBLed::CYAN, RGBLed::YELLOW, RGBLed::WHITE};

//PLAYER DATA
int player_num = 1;
int max_players = 5;
int num_players = 5;
int c_num_players = num_players;
bool endGame = false;



//U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_1(U8G2_R0, /* cs=*/ 49, /* dc=*/ 48, /* reset=*/42);
//U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_2(U8G2_R0, /* cs=*/ 45, /* dc=*/ 46, /* reset=*/ 47);
//U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_3(U8G2_R0, /* cs=*/ 39, /* dc=*/ 40, /* reset=*/ 41);
//U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_4(U8G2_R0, /* cs=*/ 29, /* dc=*/ 30, /* reset=*/ 31);
//U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2_5(U8G2_R0, /* cs=*/ 23, /* dc=*/ 24, /* reset=*/ 25);


struct player {
  char p_name[16];
  int p_num;
  unsigned long p_timems;
  int p_life;
  int p_infect;
  int p_color;
  int p_winloss; //0 is und, 1 won, -1 loss
  int cs;
  int dc;
  int reset;
} players[] = {
  {"PATRICK", 1, DEFAULT_TIME, 40, 0, 2, 0, /* cs=*/ 49, /* dc=*/ 48, /* reset=*/42},
  {"AMYTHYST", 2, DEFAULT_TIME, 40, 0, 3, 0, /* cs=*/ 45, /* dc=*/ 46, /* reset=*/ 47},
  {"NILES", 3, DEFAULT_TIME, 40, 0, 4, 0, /* cs=*/ 39, /* dc=*/ 40, /* reset=*/ 41},
  {"NUMBER 1", 4, DEFAULT_TIME, 40, 0, 5, 0, /* cs=*/ 29, /* dc=*/ 30, /* reset=*/ 31},
  {"JERRY", 5, DEFAULT_TIME, 40, 0, 6, 0, /* cs=*/ 23, /* dc=*/ 24, /* reset=*/ 25}
};



//song data
int tempo = 80;
int melody[] = {
  NOTE_D4, -8, NOTE_G4, 16, NOTE_C5, -4, 
  NOTE_B4, 8, NOTE_G4, -16, NOTE_E4, -16, NOTE_A4, -16,
  NOTE_D5, 2,
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

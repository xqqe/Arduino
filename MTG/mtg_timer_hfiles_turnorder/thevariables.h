
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
int buzzer = 8;

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


struct player {
  char p_name[10];
  int p_num;
  unsigned long p_timems;
  int p_life;
  int p_infect;
  int p_color;
  int p_winloss; //0 is und, 1 won, -1 loss
} players[] = {
  {"PATRICK", 1, DEFAULT_TIME, 40, 0, 2, 0},
  {"AMYTHYST", 2, DEFAULT_TIME, 40, 0, 3, 0},
  {"NILES", 3, DEFAULT_TIME, 40, 0, 4, 0},
  {"NUMBER 1", 4, DEFAULT_TIME, 40, 0, 5, 0},
  {"JERRY", 5, DEFAULT_TIME, 40, 0, 6, 0}
};

//player init_player(unsigned int player_num)
//{
//  player newplayer;
//  sprintf(newplayer.p_name, "Player %i", player_num) ;
//  newplayer.p_timems = DEFAULT_TIME;
//  newplayer.p_life = 40;
//  newplayer.p_infect = 0;
//  return newplayer;
//}

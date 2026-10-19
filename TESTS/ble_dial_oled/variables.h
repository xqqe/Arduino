
#define DEFAULT_TIME 600000
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
bool endGame = false;

//BUTTON PIN ASSIGNMENTS
int dial_butt = 0;
int dialA = 1;
int dialB = 2;


//dial setup
int pinALast = 0;
int aVal = 0;
int lastWhole;
int encoderPosCount = 0;
int dialState = 1; //1 is life, 0 is infect


//player data
char p_name[10] = "SARA";
unsigned long timems = 6000000;
int life = 40;
int infect = 0;
int color = 0;
bool loss = 0;

//time
unsigned long sec = (timems / 1000) % 60;
unsigned long mmin = (timems / 60000) % 60;
unsigned long hhour = timems / 3600000;

unsigned long t_sec = (lasttime / 1000) % 60;
unsigned long t_min = (lasttime / 60000) % 60;
unsigned long t_hour = lasttime / 3600000;

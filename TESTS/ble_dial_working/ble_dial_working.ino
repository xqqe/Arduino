//remember to check that the board is not set to the 'sense' version


#include <BLE52_Mouse_and_Keyboard.h>

// Rotary Encoder Inputs
#define CLK 8
#define DT 9
#define SW 10

#include <Keypad.h>
#include <bluefruit.h>

const byte ROWS = 3; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};
byte rowPins[ROWS] = {3, 2, 1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6}; //connect to the column pinouts of the keypad

byte ledPin = LED_BUILTIN; 

boolean blink = false;
boolean ledPin_state;


//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0; 

void setup() {
  // Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
  digitalWrite(ledPin, HIGH);           // Turn the LED on.
  ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  
  Serial.begin(115200);
  
  // Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);

  Keyboard.begin();
  Mouse.begin(); 

  Serial.print("Attempting to connect");
  delay(1000);//just in case
  Serial.println("\nConnection successful");
  }

void loop() {
  // Read the current state of CLK
	currentStateCLK = digitalRead(CLK);
  char customKey = keypad.getKey();
	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
			currentDir ="CCW";
      Mouse.move(0,0,3);delay(100);
		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";
      Mouse.move(0,0,-3);delay(100);
		}
	}
	// Remember last CLK state
	lastStateCLK = currentStateCLK;
	// Read the button state
	int btnState = digitalRead(SW);
	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial.println("Button pressed!");
        Keyboard.press(KEY_LEFT_CTRL);    //do a control-x
        Keyboard.write('a');              //press and release 'x' key
        Keyboard.releaseAll();            //release the control
        Keyboard.press(KEY_DELETE);    //do a control-x
        Keyboard.releaseAll();            //release the control
		}
		// Remember last button press event
		lastButtonPress = millis();
	}
	// Put in a slight delay to help debounce the reading
	delay(1);
}

void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
      switch(key) {
        case '1':
          Keyboard.press(KEY_LEFT_CTRL);    
          Keyboard.write('a');              
          Keyboard.releaseAll();            
          break;
        case '2':
          Keyboard.press(KEY_DELETE);    
          Keyboard.releaseAll();            
          break;
        case '3':
          Keyboard.press(KEY_LEFT_CTRL);    
          Keyboard.write('c');              
          Keyboard.releaseAll(); 
          break;

        case '4':
          Keyboard.press(KEY_LEFT_CTRL);    
          Keyboard.write('v');              
          Keyboard.releaseAll(); 
          break;
        case '5':
          Keyboard.press(KEY_LEFT_CTRL);    
          Keyboard.write('x');              
          Keyboard.releaseAll(); 
          break;
        case '6':
          //Keyboard.println("fun!");
          
          Keyboard.press(HID_KEY_VOLUME_UP);
          Keyboard.releaseAll(); 
          break;

        case '7':
          Keyboard.println("sassy!");
          break;
        case '8':
          Keyboard.println("win!");
          break;
        case '9':
          digitalWrite(ledPin,!digitalRead(ledPin));
              ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
          break;
        default:
          Serial.print('broke');
          break;
      }
      break;

    case RELEASED:
    switch(key) {
        case '1':          
          break;
        case '2':
          break;
        case '3':
          break;

        case '4':
          break;
        case '5':
          break;
        case '6':
          break;

        case '7':
          break;
        case '8':
          break;
        case '9':
          break;

        default:
          Serial.print('broke');
          break;
      }
        
        break;

    case HOLD:
        switch(key) {
        case '1':
          Keyboard.println("great!");
          break;
        case '2':
          Keyboard.println("yum!");
          break;
        case '3':
          Keyboard.println("boo!");
          break;

        case '4':
          Keyboard.println("reeeee!");
          break;
        case '5':
          Keyboard.println("queen!");
          break;
        case '6':
          Keyboard.println("fun!");
          break;

        case '7':
          Keyboard.println("sassy!");
          break;
        case '8':
          Keyboard.println("win!");
          break;
        case '9':
          digitalWrite(ledPin,!digitalRead(ledPin));
              ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
          break;
        default:
          Serial.print('broke');
          break;
      }
        break;
    }
}


/*
   MIDI controller v.0.1
   reads the state of 7 buttons and
   sends MIDI signals to be read by 
   An compatible MIDI receptor.
   Created by Rene Robles 2020
*/

/*CONSTANTS FOR OUTPUT LEDS*/
const int LED1 = 13;

/*CONSTANTS FOR INPUT BUTTONS*/
const int BUTTON1 = 2;
const int BUTTON2 = 3;
const int BUTTON3 = 4;
const int BUTTON4 = 5;
const int BUTTON5 = 6;
const int BUTTON6 = 7;
const int BUTTON7 = 8;

const int JOYUP = 9;
const int JOYDOWN = 10;
const int JOYLEFT = 11;
const int JOYRIGHT = 12;

/*MIDI COMMAND CONSTANTS*/
const int PLAY = 0x90;
const int MED_VEL = 0x45;
const int SILENCE = 0x00;

/*MIDI notes*/
const int KEY_NOTE = 0x2E; //F#_5
int CURRENT_BASE_NOTE = KEY_NOTE;
//MAJOR 1, MINOR = 2 DIMINISHED = 3
int currentScaleType = 1;

/*MUSIC THEORY*/
/*SCALES
   an increment of 2 represents a whole tone
   an increment of 1 represents a half tone
   I= key II= scale[0] III= scale[1] IV= scale[2]
   V = scale[3] VI = scale[4] VII = scale[6]
*/
const int MAJOR[] = {0, 2, 4, 5, 7, 9, 11};
const int MINOR[] = {0, 2, 3, 5, 7, 8, 10};
const int DIMINISHED[] = {0, 2, 3, 5, 6, 8, 9, 11};

/*
   contains the index to its corresponding scale
*/
const int majorTriadIndex[] = {0, 2, 4};
const int minorTriadIndex[] = {0, 2, 4};

/*Ionian*/
/*Since we will be using joystick to control the position in the progression
  I added 12th and 14th offset*/
const int IONIAN_PROGRESSION_OFFSET[] = {0, 2, 4, 5, 7, 9, 11, 12, 14};

/*Progressions
   M major
   m minor
   d dim
*/
const char IONIAN_PROGRESSION_TYPE[] = "MmmMMmd";


/*VARIABLES FOR STORING STATE OF THE BUTTONS*/
int buttonState1 = LOW;
int buttonState2 = LOW;
int buttonState3 = LOW;
int buttonState4 = LOW;
int buttonState5 = LOW;
int buttonState6 = LOW;
int buttonState7 = LOW;

int buttonPrevState1 = LOW;
int buttonPrevState2 = LOW;
int buttonPrevState3 = LOW;
int buttonPrevState4 = LOW;
int buttonPrevState5 = LOW;
int buttonPrevState6 = LOW;
int buttonPrevState7 = LOW;

/*VARIABLES FOR STORING STATE OF THE JOYSTICK*/
int joyUpPrevState = LOW;
int joyDownPrevState = LOW;
int joyRightPrevState = LOW;
int joyLeftPrevState = LOW;

int joyUpState = LOW;
int joyDownState = LOW;
int joyRightState = LOW;
int joyLeftState = LOW;


void setup() {
  //Serial.begin(9600);
  Serial.begin(31250);

  pinMode(LED1, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
  pinMode(BUTTON6, INPUT_PULLUP);
  pinMode(BUTTON7, INPUT_PULLUP);

  pinMode(JOYUP, INPUT_PULLUP);
  pinMode(JOYDOWN, INPUT_PULLUP);
  pinMode(JOYRIGHT, INPUT_PULLUP);
  pinMode(JOYLEFT, INPUT_PULLUP);

}

void loop() {
  //loop to read al button states
  buttonState1 = digitalRead(BUTTON1);
  buttonState2 = digitalRead(BUTTON2);
  buttonState3 = digitalRead(BUTTON3);
  buttonState4 = digitalRead(BUTTON4);
  buttonState5 = digitalRead(BUTTON5);
  buttonState6 = digitalRead(BUTTON6);
  buttonState7 = digitalRead(BUTTON7);

  joyUpState = digitalRead(JOYUP);
  joyDownState = digitalRead(JOYDOWN);
  joyLeftState = digitalRead(JOYLEFT);
  joyRightState = digitalRead(JOYRIGHT);


  if (buttonState1 != buttonPrevState1) {
    button1Handler();
  }
  if (buttonState2 != buttonPrevState2){
    button2Handler();
  }
  if (buttonState3 != buttonPrevState3){
    button3Handler();
  }
  if (buttonState4 != buttonPrevState4){
    button4Handler();
  }
  if (buttonState5 != buttonPrevState5){
    button5Handler();
  }
  if (buttonState6 != buttonPrevState6){
    button6Handler();
  }
  if (buttonState7 != buttonPrevState7){
    button7Handler();
  }
  
  if (joyUpState != joyUpPrevState ||
      joyDownState != joyDownPrevState ||
      joyLeftState != joyLeftPrevState ||
      joyRightState != joyRightPrevState)
    joyStickHandler();
  delay(1);
}

void joyStickHandler() {
  //when state has changed and joystick has returned to middle, do nothing.
  if(joyUpState == joyDownState == joyRightState == joyLeftState == LOW){
    return;
    }
    //need to traspose playng notes.
    //first should silence current,
    //then update base key
    //finally re-trigger play note
    silencePlayingNotes();
  switch( getJoyStickPosition()){
    //UP
    case 1 : CURRENT_BASE_NOTE= KEY_NOTE+1;
    break;
    case 2 : CURRENT_BASE_NOTE = KEY_NOTE+2;
    break;
    case 3 : CURRENT_BASE_NOTE = KEY_NOTE+3;
    break;
    case 4 : CURRENT_BASE_NOTE = KEY_NOTE+4;
    }
    resumePlayingNotes();    
    joyUpPrevState = joyUpState;
    joyDownPrevState = joyDownState;
    joyRightPrevState = joyRightState;
    joyLeftPrevState = joyLeftState;
}

//will play the key note
void button1Handler() {
  buttonPrevState1 = buttonState1;
  digitalWrite(LED1, buttonState1);
  if (buttonState1 == HIGH) {
    //Serial.println("Button 1 is pressed");
    noteOn(PLAY, CURRENT_BASE_NOTE , MED_VEL);
  } else {
    noteOn(PLAY, CURRENT_BASE_NOTE , SILENCE);
  }
}

void button2Handler() {
  buttonPrevState2 = buttonState2;
  digitalWrite(LED1, buttonState2);
  //Calculate offset to play note
  int note = getNoteForButton(2);
  if (buttonState2 == HIGH) {
    //Serial.println("Button 1 is pressed");
    noteOn(PLAY, note , MED_VEL);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}

void button3Handler() {
  buttonPrevState3 = buttonState3;
  digitalWrite(LED1, buttonState3);
  //Calculate offset to play note
  int note = getNoteForButton(3);
  if (buttonState3 == HIGH) {
    //Serial.println("Button 3 is pressed");
    noteOn(PLAY, note , MED_VEL);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}

void button4Handler() {
  buttonPrevState4 = buttonState4;
  digitalWrite(LED1, buttonState4);
  //Calculate offset to play note
  int note = getNoteForButton(4);
  if (buttonState4 == HIGH) {
    noteOn(PLAY, note, MED_VEL);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}

void button5Handler() {
  buttonPrevState5 = buttonState5;
  digitalWrite(LED1, buttonState5);
  //Calculate offset to play note
  int note = getNoteForButton(5);
  if (buttonState5 == HIGH) {
    noteOn(PLAY, note, MED_VEL);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}

void button6Handler() {
  buttonPrevState6 = buttonState6;
  digitalWrite(LED1, buttonState6);
  //Calculate offset to play note
  int note = getNoteForButton(6);
  if (buttonState6 == HIGH) {
    noteOn(PLAY, note, MED_VEL);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}

void button7Handler() {
  buttonPrevState7 = buttonState7;
  digitalWrite(LED1, buttonState7);
  //Calculate offset to play note
  int note = getNoteForButton(7);
  if (buttonState7 == HIGH) {
    noteOn(PLAY, note, MED_VEL);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

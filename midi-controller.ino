
/*
   MIDI controller v.0.1
   reads the state of 4 buttons and
   send a signal switch LED state.
   Created by Rene Robles 2020
*/

/*CONSTANTS FOR OUTPUT LEDS*/
const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 11;
const int LED4 = 10;

/*CONSTANTS FOR INPUT BUTTONS*/
const int BUTTON1 = 4;
const int BUTTON2 = 7;
const int BUTTON3 = 2;
const int BUTTON4 = 3;
const int BUTTON5 = 5;

/*MIDI COMMAND CONSTANTS*/
const int PLAY = 0x90;
const int MED_VEL = 0x45;
const int SILENCE = 0x00;

/*MIDI notes*/
const int KEY_NOTE = 0x1E; //F#_5

/*MUSIC THEORY*/
/*SCALES
 * an increment of 2 represents a hole tone
 * an increment of 1 represents a half tone
 * I= key II= scale[0] III= scale[1] IV= scale[2]
 * V = scale[3] VI = scale[4] VII = scale[6]
*/
const int majorScale[] = {2,4,5,7,9,11,12};
const int minorScale[] = {2,3,5,7,8,10,12};

/*Ionian*/
const int IONIAN_PROGRESSION[] = {2,4,5,7,9,11,12};

/*Progressions
 * M major
 * m minor
 * d dim
*/
const char majorProgression[] = "MmmMMmd";


/*VARIABLES FOR STORING STATE OF THE BUTTONS*/
int buttonState1 = LOW;
int buttonState2 = LOW;
int buttonState3 = LOW;
int buttonState4 = LOW;
int buttonState5 = LOW;
int buttonPrevState1 = LOW;
int buttonPrevState2 = LOW;
int buttonPrevState3 = LOW;
int buttonPrevState4 = LOW;
int buttonPrevState5 = LOW;

int option;

void setup() {
  //Serial.begin(9600);
  Serial.begin(31250);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);

}

void loop() {

  if (Serial.available() > 0) {
    // read the incoming byte:
    option = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(option, BIN);
  }
  //loop to read al button states
  buttonState1 = digitalRead(BUTTON1);
  buttonState2 = digitalRead(BUTTON2);
  buttonState3 = digitalRead(BUTTON3);
  buttonState4 = digitalRead(BUTTON4);
  if (buttonState1 != buttonPrevState1) {
    button1Handler();
  }
  if (buttonState2 != buttonPrevState2)
    button2Handler();
  if (buttonState3 != buttonPrevState3)
    button3Handler();
  if (buttonState4 != buttonPrevState4)
    button4Handler();
  if (buttonState5 != buttonPrevState5)
    button5Handler();
  delay(1);
}

//will play the key note
void button1Handler() { 
  digitalWrite(LED1, buttonState1);
  buttonPrevState1 = buttonState1;
  if (buttonState1 == HIGH) {
    //Serial.println("Button 1 is pressed");
    noteOn(PLAY, KEY_NOTE, MED_VEL);
    delay(500);
    noteOn(PLAY, KEY_NOTE , SILENCE);
    noteOn(PLAY, KEY_NOTE+ majorScale[1], MED_VEL);
    delay(500);
    noteOn(PLAY, KEY_NOTE+ majorScale[1], SILENCE);
    noteOn(PLAY, KEY_NOTE+ majorScale[3], MED_VEL);
    delay(500);
    noteOn(PLAY, KEY_NOTE+ majorScale[3], SILENCE);
  } else {
    noteOn(PLAY, KEY_NOTE , SILENCE);
  }
}
void button2Handler() {
  digitalWrite(LED2, buttonState2);
  buttonPrevState2 = buttonState2;
  //Calculate offset to play note
  int note = KEY_NOTE+ IONIAN_PROGRESSION[3];
  if (buttonState2 == HIGH) {
    //Serial.println("Button 1 is pressed");
    noteOn(PLAY, note, MED_VEL);
    delay(500);
    noteOn(PLAY, note , SILENCE);
    noteOn(PLAY, note+ majorScale[1], MED_VEL);
    delay(500);
    noteOn(PLAY, note+ majorScale[1], SILENCE);
    noteOn(PLAY, note+ majorScale[3], MED_VEL);
    delay(500);
    noteOn(PLAY, note+ majorScale[3], SILENCE);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}
void button3Handler() {
  digitalWrite(LED3, buttonState3);
  buttonPrevState3 = buttonState3;
  //Calculate offset to play note
  int note = KEY_NOTE+ IONIAN_PROGRESSION[4];
  if (buttonState3 == HIGH) {
    //Serial.println("Button 1 is pressed");
    noteOn(PLAY, note, MED_VEL);
    delay(500);
    noteOn(PLAY, note , SILENCE);
    noteOn(PLAY, note+ minorScale[1], MED_VEL);
    delay(500);
    noteOn(PLAY, note+ minorScale[1], SILENCE);
    noteOn(PLAY, note+ minorScale[3], MED_VEL);
    delay(500);
    noteOn(PLAY, note+ minorScale[3], SILENCE);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}
void button4Handler() {
  digitalWrite(LED4, buttonState4);
  buttonPrevState4 = buttonState4;
  //Calculate offset to play note
  int note = KEY_NOTE+ IONIAN_PROGRESSION[2];
  
  if (buttonState4 == HIGH) {
    //Serial.println("Button 1 is pressed");
    noteOn(PLAY, note, MED_VEL);
    delay(500);
    noteOn(PLAY, note , SILENCE);
    noteOn(PLAY, note+ majorScale[1], MED_VEL);
    delay(500);
    noteOn(PLAY, note+ majorScale[1], SILENCE);
    noteOn(PLAY, note+ majorScale[3], MED_VEL);
    delay(500);
    noteOn(PLAY, note+ majorScale[3], SILENCE);
  } else {
    noteOn(PLAY, note , SILENCE);
  }
}
void button5Handler() {
 //TODO move chords
}
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

/*
   All of the calcultaions will e done here
*/

/*
   All of the calcultaions will e done here
*/

int getNextNote(char type, int keyNote , int currentNoteIndex) {
  int offsetIndex;
  int offset;
  return 0;
}

int getNoteForButton (int buttonNumber) {
  switch (currentScaleType) {
    case 1: return CURRENT_BASE_NOTE + MAJOR[buttonNumber - 1];
    case 2: return CURRENT_BASE_NOTE + MINOR[buttonNumber - 1];
    case 3: return CURRENT_BASE_NOTE + DIMINISHED[buttonNumber - 1];
  }
}

int getJoyStickPosition () {
  //up
  if (joyUpState == HIGH && joyDownState == joyLeftState == joyRightState) return 1;
  //down
  if (joyDownState == HIGH && joyUpState == joyLeftState == joyRightState) return 2;
  //left
  if (joyLeftState == HIGH && joyDownState == joyUpState == joyRightState) return 3;
  //right
  if (joyRightState == HIGH && joyDownState == joyLeftState == joyUpState ) return 4;
  //default
  return 1;
}

void silencePlayingNotes () {
  for ( int i = 1; i <= 7 ; i++)
    noteOn(PLAY, getNoteForButton(i) , SILENCE);
}
void resumePlayingNotes () {
  if (buttonState1 == HIGH )
    button1Handler();
  if (buttonState2 == HIGH )
    button2Handler();
  if (buttonState3 == HIGH )
    button3Handler();
  if (buttonState4 == HIGH )
    button4Handler();
  if (buttonState5 == HIGH )
    button5Handler();
  if (buttonState6 == HIGH )
    button6Handler();
  if (buttonState7 == HIGH )
    button7Handler();

}

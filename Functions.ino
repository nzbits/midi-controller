/*
   All of the calcultaions will e done here
*/

int getNoteForButton (int buttonNumber) {
  switch (currentScaleType) {
    case 1: return currentBaseNote + MAJOR[buttonNumber - 1];
    case 2: return currentBaseNote + MINOR[buttonNumber - 1];
    case 3: return currentBaseNote + DIMINISHED[buttonNumber - 1];
  }
}

int getJoyStickPosition () {
  //up
  if (joyUpState == HIGH && joyDownState == LOW && joyLeftState == LOW && joyRightState == LOW) return 1;
  //up/right
  if (joyUpState == HIGH && joyDownState == LOW && joyLeftState == LOW && joyRightState == HIGH) return 2;
  //right
  if (joyRightState == HIGH && joyDownState == LOW && joyLeftState == LOW && joyUpState == LOW) return 3;
  //right/down
  if (joyRightState == HIGH && joyDownState == HIGH && joyLeftState == LOW && joyUpState == LOW) return 4;  
  //down
  if (joyDownState == HIGH && joyUpState == LOW && joyLeftState == LOW && joyRightState == LOW ) return 5;
  //down/left
  if (joyRightState == LOW && joyDownState == HIGH && joyLeftState == HIGH && joyUpState == LOW) return 6;
  //left
  if (joyLeftState == HIGH && joyDownState == LOW && joyUpState == LOW && joyRightState ==  LOW ) return 7;
  //left/up
  if (joyRightState == LOW && joyDownState == LOW && joyLeftState == HIGH && joyUpState == HIGH) return 8;
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

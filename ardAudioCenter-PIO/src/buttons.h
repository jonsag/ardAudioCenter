#include "buttonActions.h" // makes buttons do something

void readButtons()
{
  rotate1 = rotary1.rotate();
  push1 = rotary1.push();

  rotate2 = rotary2.rotate();
  push2 = rotary2.push();

  /*******************************
    Rotary encoder 1
  *******************************/
  if (rotate1 != 0 || push1 != 0) // button was manipulated
  {
    button1Millis = millis();

    debugMess("--- Rotary encoder 1: ");

    if (push1) // left button pressed
    {
      debugMessln("Button pressed");

      button1Action();
    }
    else
    {
      switch (rotate1) // left knob
      {
      case 1: // clockwise rotation
        debugMessln("CW");

        switch (functionNo)
        {
        case 0: // volume up
          increaseVolume();
          break;

        case 1: // source up
          sourceUp();
          break;

        default: // case 2: // balance right
          balanceRight();
          break;
        }

        break;

      default: // case 2: // counter clockwise rotation
        debugMessln("CCW");

        switch (functionNo)
        {
        case 0: // volume down
          decreaseVolume();
          break;
        case 1: // source down
          sourceDown();
          break;
        default: // case 2: // balance left
          balanceLeft();
          break;
        }

        break;
      }
    }
  }

  /*******************************
    Rotary encoder 2
  *******************************/
  if (rotate2 != 0 || push2 != 0) // button was manipulated
  {
    button2Millis = millis();

    debugMess("--- Rotary encoder 2: ");

    if (push2) // right button pressed
    {

      debugMessln("Button pressed");

      button2Action();
    }
    else
    {
      switch (rotate2) // right knob
      {
      case 1: // clockwise rotation
        debugMessln("CW");

        switch (sourceNo)
        {
        case 0:              // FM radio
          if (!presetScreen) // frequency up
          {
            increaseFreq();
          }
          else
          {
            presetUp();
          }
          break;
#if DFPLAYER
        case 3: // DFPlayer
          increaseTrack();
          break;
#endif
        default:
          break;
        }

        break;

      default: // case 2: // counter clockwise rotation
        debugMessln("CCW");

        switch (sourceNo)
        {
        case 0:              // FM radio
          if (!presetScreen) // frequency down
          {
            decreaseFreq();
          }
          else
          {
            presetDown();
          }
          break;
#if DFPLAYER
        case 3: // DFPlayer
          decreaseTrack();
          break;
#endif
        default:
          break;
        }

        break;
      }
    }
  }
}

/*
  byte i = rotary.pushLong(1000); // Check to see if button is pressed for 1 second.
  if ( i == 1 ) {
    debugMessln("1 Sec Long Pushed");
  }
*/

/*
  i = rotary.pushTime(); // If button is pressed for more then 2 seconds, then reset the amount of time it was pressed. This can be used to build a function that will repeat every 2 seconds.
  if ( i > 2000 ) {
  rotary.resetPush();
  }
*/

/*
  i = rotary.pushTime(); // How to get amount of time the button was pressed.
  debugMessln(i);
*/

/*
  i = rotary.pushType(1000); // Number of milliseconds button has to be pushed for it to be considered a long push. 0 = not pushed, 1 = pushed, 2 = long pushed

  if ( i == 1 ) {
    debugMessln("Pushed");
  }

  if ( i == 2 ) {
    debugMessln("Long Pushed");
  }
*/

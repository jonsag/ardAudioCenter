#include "buttonActions.h" // makes buttons do something

void readButtons() {
  byte rotate1 = rotary1.rotate();
  byte push1 = rotary1.push();

  //byte rotate2 = rotary2.rotate();
  //byte push2 = rotary2.push();

  /*******************************
    Rotary encoder 1
  *******************************/
  if (rotate1 != 0 || push1 != 0) {  // button was rotated
    buttonMillis = millis();

    if (debug) {
      Serial.println();
      Serial.print("Rotary encoder 1: ");
    }

    if ( rotate1 == 1) { // clockwise rotation
      if (debug) {
        Serial.println("CW");
      }

      if (functionNo == 0) { // volume up
        increaseVolume();
      } else if ( functionNo == 1) { // source up
        sourceUp();
      } else if ( functionNo == 2) { //balance right
        balanceRight();
      }

    } else if (rotate1 == 2) { // counter clockwise rotation
      if (debug) {
        Serial.println("CCW");
      }

      if (functionNo == 0) { // volume down
        decreaseVolume();
      } else if ( functionNo == 1) { // source down
        sourceDown();
      } else if ( functionNo == 2) { // balance left
        balanceLeft();
      }
    }

    if (push1) {  // button pressed
      buttonMillis = millis();

      if (debug) {
        Serial.println(" Pushed");
      }

      button1Action();
    }
  }


  /*******************************
    Rotary encoder 2
  *******************************/
  /*
  if (rotate2 != 0 || push2 != 0) {  // button was rotated
    if (debug) {
      Serial.println();
      Serial.print("Rotary encoder 2: ");
    }

    if ( rotate2 == 1) { // clockwise rotation
      if (debug) {
        Serial.println("CW");
      }
    } else if (rotate2 == 2) { // counter clockwise rotation
      if (debug) {
        Serial.println("CCW");
      }
    }
  }

  if (push2) {  // button pressed
      buttonMillis = millis();

      if (debug) {
        Serial.println(" Pushed");
      }

      button2Action();
    }
    */
}


/*
  byte i = rotary.pushLong(1000); // Check to see if button is pressed for 1 second.
  if ( i == 1 ) {
    Serial.println("1 Sec Long Pushed");
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
  Serial.println(i);
*/

/*
  i = rotary.pushType(1000); // Number of milliseconds button has to be pushed for it to be considered a long push. 0 = not pushed, 1 = pushed, 2 = long pushed

  if ( i == 1 ) {
    Serial.println("Pushed");
  }

  if ( i == 2 ) {
    Serial.println("Long Pushed");
  }
*/

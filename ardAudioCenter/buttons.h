#include "buttonActions.h" // makes buttons do something

void readButtons() {
  byte rotate1 = rotary1.rotate();
  byte push1 = rotary1.push();

  /*******************************
    Rotary encoder 1
  *******************************/
  if (rotate1 != 0 || push1 != 0) {
    Serial.println();
    Serial.print("Rotary encoder 1: ");

    if ( rotate1 == 1 ) {
      Serial.println("CW");
    }

    if ( rotate1 == 2 ) {
      Serial.println("CCW");
    }

    if (push1) {
      Serial.println(" Pushed");
      button1Action();
    }
  }
}

void onPinActivated(int pinNr) {
  /*
    Serial.println();
    Serial.print("Pin activated: ");
    Serial.println(pinNr);
  */
}

void onPinDeactivated(int pinNr) {
  /*Serial.println();
    Serial.print("Pin deactivated: ");
    Serial.println(pinNr);
  */

  switch (pinNr) {
    case 4:
      button1Action();
      break;
  }

  Serial.println();
  Serial.print("Function selected: ");
  Serial.println(functionNo);
  Serial.println(functions[functionNo]);

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

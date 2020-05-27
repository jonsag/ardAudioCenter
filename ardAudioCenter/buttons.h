#include "buttonActions.h" // makes buttons do something

void onPinActivated(int pinNr){
  /*
  Serial.println();
  Serial.print("Pin activated: ");
  Serial.println(pinNr);
  */
}

void onPinDeactivated(int pinNr){
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

#include "configuration.h" // sets all variables
#include "buttons.h" // handle button presses
#include "lcd.h" // manages all info on LCD

void setup() {
  /*******************************
    Start LCD
  *******************************/
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0); // print name of this program and boot message to the LCD
  lcd.print(programName);
  lcd.setCursor(0, 1);
  lcd.print("Booting ...");

  /*******************************
    Start serial
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Starting serial ...");

  Serial.begin(9600);

  Serial.println(programName); // print information
  Serial.println(date);
  Serial.print("by ");
  Serial.println(author);
  Serial.println(email);
  Serial.println();

  Serial.print("Number of sources: ");
  Serial.println(sizeof(sources) / sizeof(sources[0]));
  Serial.println();

  Serial.print("Function selected: ");
  Serial.println(functionNo);
  Serial.println(functions[functionNo]);

  /*******************************
    Setup rotary encoders
  *******************************/
  //rotary1.setTrigger(HIGH); // Set the trigger to be either a HIGH or LOW pin (Default: HIGH). Note this sets all three pins to use the same state.
  //rotary1.setDebounceDelay(debounceDelay); // Set the debounce delay in ms  (Default: 2)
  //rotary1.setErrorDelay(errorDelay); // Set the error correction delay in ms  (Default: 200)

  printSource();

  printFunction();

}

void loop() {

  readButtons();

  if (functionNo != oldFunctionNo) {
    printFunction();
    oldFunctionNo = functionNo;
  }

  if (volume != oldVolume) {
    printVolume();
    oldVolume = volume;
  }

  if (sourceNo != oldSourceNo) {
    printSource();
    if (functionNo == 1) {
      printSourceSelect();
    }
    oldSourceNo = sourceNo;
  }

}

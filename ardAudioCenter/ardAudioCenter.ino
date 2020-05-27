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

  /*******************************
    Setup FTDebouncer pins
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Start debouncer ...");
  
  pinDebouncer.addPin(4, LOW); // pin has external pull-down resistor
  pinDebouncer.begin();

  Serial.print("Function selected: ");
  Serial.println(functionNo);
  Serial.println(functions[functionNo]);

  printSource();
  
  printFunction();

}

void loop() { 
  
  pinDebouncer.update(); // reads and handles all buttons

  if (sourceNo != oldSourceNo) {
    printSource();
  }

  if (functionNo != oldFunctionNo) {
    printFunction();
  }

  if (volume != oldVolume) {
    printVolume();
  }

}

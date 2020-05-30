#include "configuration.h" // sets all variables
#include "lcd.h" // manages all info on LCD
#include "buttons.h" // handle button presses
#include "sources.h" // sets source
#include "volume.h" // sets volume


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
  if (debug) {
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

    Serial.print("Source selected: ");
    Serial.println(sourceNo);
    Serial.println(sources[sourceNo]);
    Serial.println();

    Serial.print("Function selected: ");
    Serial.println(functionNo);
    Serial.println(functions[functionNo]);
    Serial.println();

    Serial.print("Volume: ");
    Serial.print(volume);
    Serial.println("%");
    Serial.print("Balance: ");
    Serial.println(balance);
    Serial.println();
  }

  /*******************************
    Define pins
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Defining pins ...");

  if (debug) {
    Serial.println("Defining pins ...");
    Serial.println();
  }

  for (int i = 0; i < 2; i++) { // define multiplexer pins
    pinMode(muxPins[i], OUTPUT);
    digitalWrite(muxPins[i], LOW);
  }

  pinMode (csPL, OUTPUT); // chip select for left channel potentiometer
  pinMode (csPR, OUTPUT); // chip select for right channel potentiometer

  digitalWrite(csPL, HIGH);
  digitalWrite(csPR, HIGH);
  
  /*******************************
    Starting SPI interface
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Starting SPI ...");

  if (debug) {
    Serial.println("Starting SPI ...");
    Serial.println();
  }

  SPI.begin();

  /*******************************
    Setup rotary encoders
  *******************************/
  //rotary1.setTrigger(HIGH); // Set the trigger to be either a HIGH or LOW pin (Default: HIGH). Note this sets all three pins to use the same state.
  //rotary1.setDebounceDelay(debounceDelay); // Set the debounce delay in ms  (Default: 2)
  //rotary1.setErrorDelay(errorDelay); // Set the error correction delay in ms  (Default: 200)

  printSource();

  printFunction();

  setVolume();

}

void loop() {

  readButtons();

  if (millis() - buttonMillis >= screenWait) { // return to home screen after wait time
    functionNo = 0;

    sourceNo = selectSourceNo; // source might have been changed

  }

  if (functionNo != oldFunctionNo) {
    printFunction();
    oldFunctionNo = functionNo;
  }

  if (volume != oldVolume) {
    printVolume();

    setVolume();

    oldVolume = volume;
  }

  if (balance != oldBalance) {
    printBalance();

    setVolume();

    oldBalance = balance;
  }

  if (sourceNo != oldSourceNo) {
    printSource();

    setMux();

    if (functionNo == 1) {
      printSourceSelect();
    }
    oldSourceNo = sourceNo;
  }

}

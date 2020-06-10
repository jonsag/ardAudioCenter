#include "configuration.h" // sets all variables
#include "radio.h" // control the FM radio module
//#include "sdCard.h" // control the DFPlayer Mini SD Card module
#include "lcd.h" // manages all info on LCD
#include "buttons.h" // handle button presses
#include "sources.h" // sets source
#include "volume.h" // sets volume

void setup() {
  /*******************************
    Start wire, I2C
  *******************************/
  //Wire.begin(D2, D1); // SDA -> D2, SCL -> D1 // wire is not needed

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

    Serial.begin(serialSpeed);

    /*******************************
      Print start information
    *******************************/
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

    Serial.print("FM radio frequency: ");
    Serial.println(frequency);
    Serial.print("FM radio volume: ");
    /* commented out beacause TEA5767 doesn't seem to have this optio
      Serial.println(radioVolume);
      Serial.println();
    */
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

  pinMode(btMute, OUTPUT); // mute output on bluetooth module

  digitalWrite(btMute, HIGH);

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
    Build custom characters
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Building chars ...");

  if (debug) {
    Serial.println("Building custom characters ...");
    Serial.println();
  }

  lcd.createChar(1, bar1);
  lcd.createChar(2, bar2);
  lcd.createChar(3, bar3);
  lcd.createChar(4, bar4);
  lcd.createChar(5, bar5);

  /*
    lcd.createChar(1, fill1);
    lcd.createChar(2, fill2);
    lcd.createChar(3, fill3);
    lcd.createChar(4, fill4);
    lcd.createChar(5, fill5);
  */

  /*******************************
    Set up rotary encoders
  *******************************/
  /* all commented out because the default settings are fine
    lcd.setCursor(0, 1);
    lcd.print("Setting up encoders ...");

    if (debug) {
      Serial.println("Setting up rotary encoders  ...");
      Serial.println();
    }

    rotary1.setTrigger(HIGH); // Set the trigger to be either a HIGH or LOW pin (Default: HIGH). Note this sets all three pins to use the same state.
    rotary1.setDebounceDelay(debounceDelay); // Set the debounce delay in ms  (Default: 2)
    rotary1.setErrorDelay(errorDelay); // Set the error correction delay in ms  (Default: 200)
  */

  /*******************************
    Start FM radio receiver
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Starting receiver ...");

  if (debug) {
    Serial.println("Starting FM radio recevier  ...");
    Serial.println();
  }

  radio.init(); // initialize radio

  if (debug) {
    radio.debugEnable(); // enable information to the serial port
  }

  setReceiver(); // tune the radio receiver

  if (debug) {
    printRadioDebugInfo();
  }

  /*******************************
    Start DFPlayer Mini
  *******************************/
  /*
    lcd.setCursor(0, 1);
    lcd.print("Starting sw serial ...");

    if (debug) {
      Serial.println("Start software serial  ...");
      Serial.println();
    }

    mySoftwareSerial.begin(9600);

    lcd.setCursor(0, 1);
    lcd.print("Starting DFPlayer Mini ...");

    if (debug) {
      Serial.println();
      Serial.println("DFRobot DFPlayer Mini");
      Serial.println("Inicializando modulo DFPlayer... (3~5 segundos)");
    }

    if (!myDFPlayer.begin(mySoftwareSerial)) {
      Serial.println("Could not initialize DFPlayer mini: ");
      Serial.println("1. Check DFPlayer connections");
      Serial.println("2. Insert SD card");
      while (true);
    }
    if (debug) {
      Serial.println();
      Serial.println("Modulo DFPlayer Mini inicializado!");
    }

    myDFPlayer.setTimeOut(mySoftwareSerialTimeOut); // timeout serial 500ms
    myDFPlayer.volume(sdVolume); // volume 10, between 0 and 30
    myDFPlayer.EQ(0); // equalizer set to normal

    maxSDSongs = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD); // count number of tracks on sd card
    if (debug) {
      Serial.println();
      Serial.print("Number of tracks on SD card: ");
      Serial.println(maxSDSongs);
    }

    menu_opcoes(); // mostra o menu de comandos
  */

  /*******************************
    Fill LCD
  *******************************/
  printSource();
  printFunction();

  setVolume();

}

void loop() {

  readButtons();

  if (millis() - button1Millis >= screenWait) { // return to home screen after wait time
    functionNo = 0;
    sourceNo = selectSourceNo; // source might have been changed
  }

  if (millis() - button2Millis >= screenWait && sourceNo == 0 && presetScreen) { // return to home screen after wait time
    presetScreen = false;
    printFM();
  }

  if (sourceNo == 0 && frequency != oldFrequency) { // tune in to new radio frequency
    setReceiver();
    oldFrequency = frequency;
  }

  if (functionNo != oldFunctionNo) { // new function for second row on LCD has been selected
    printFunction();
    oldFunctionNo = functionNo;
  }

  if (volume != oldVolume) { // volume has been changed
    printVolume();
    setVolume();
    oldVolume = volume;
  }

  if (balance != oldBalance) { // balance has been changed
    printBalance();
    setVolume();
    oldBalance = balance;
  }

  if (sourceNo != oldSourceNo) { // new source has been selected
    printSource();
    setMux(); // select source via multiplexer

    if (sourceNo == 0) { // FM radio is selected
      radio.setMute(false); // unmute the radio
      setReceiver(); // set frequency on receiver
    } else {
      radio.setMute(true); // mute the radio

      if (debug) {
        Serial.println();
        Serial.println("Radio muted");
      }

    }

    if (sourceNo == 1) { // unmute bluetooth if selected
      digitalWrite(btMute, LOW);
    } else {
      digitalWrite(btMute, HIGH);
    }

    if (functionNo == 1) {
      printSourceSelect();
    }

    oldSourceNo = sourceNo;
  }
}

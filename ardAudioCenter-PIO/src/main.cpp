#include "Arduino.h"

#include "configuration.h" // sets all variables

#include "radioTEA5767.h" // control the FM radio module
//#include "sdCard.h" // control the DFPlayer Mini SD Card module
#include "lcd.h"     // manages all info on LCD
#include "buttons.h" // handle button presses
#include "sources.h" // sets source
#include "volume.h"  // sets volume

void setup()
{
  /*******************************
    Start wire, I2C
  *******************************/
  // Wire.begin(SDApin, SCLpin);

  /*******************************
    Start LCD
  *******************************/
  lcd.begin(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0); // print name of this program and boot message to the LCD
  lcd.print(programName);
  lcd.setCursor(0, 1);
  lcd.print("Booting ...     ");

  delay(bootDelay); // delay to be able to see message on LCD

  /*******************************
    Start serial
  *******************************/
#if DEBUG
  lcd.setCursor(0, 1);
  lcd.print("Starting serial ...");

  Serial.begin(serialSpeed);

  delay(bootDelay); // delay to be able to see message on LCD
#endif

  /*******************************
    Print start information
  *******************************/
  debugMessln(programName);
  debugMessln(date);
  debugMessln("by ");
  debugMessln(author);
  debugMessln(email);

  debugMess("Number of sources: ");
  debugMessln(sizeof(sources) / sizeof(sources[0]));
  debugMessln();

  debugMess("Source selected: ");
  debugMessln(sourceNo);
  debugMessln(sources[sourceNo]);
  debugMessln();

  debugMess("Function selected: ");
  debugMessln(functionNo);
  debugMessln(functions[functionNo]);
  debugMessln();

  debugMess("Volume: ");
  debugMess(volume);
  debugMessln("%");
  debugMess("Balance: ");
  debugMessln(balance);
  debugMessln();

  debugMess("FM radio frequency: ");
  debugMessln(frequency);
  /* commented out because TEA5767 doesn't seem to have this option
    debugMess("FM radio volume: ");
    debugMess(radioVolume);
  */
  debugMessln();

  /*******************************
    Define pins
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Defining pins ...");

  debugMessln("Defining pins ...");
  debugMessln();

  pinMode(muxPin0, OUTPUT);
  pinMode(muxPin1, OUTPUT);
  digitalWrite(muxPin0, LOW);
  digitalWrite(muxPin1, LOW);

  pinMode(csPL, OUTPUT); // chip select for left channel potentiometer
  pinMode(csPR, OUTPUT); // chip select for right channel potentiometer
  digitalWrite(csPL, HIGH);
  digitalWrite(csPR, HIGH);

  pinMode(btMute, OUTPUT); // mute output on bluetooth module
  digitalWrite(btMute, HIGH);

  delay(bootDelay); // delay to be able to see message on LCD

  /*******************************
    Starting SPI interface
  *******************************/
  /* seems there's no need for this
  lcd.setCursor(0, 1);
  lcd.print("Starting SPI ...");

  debugMessln("Starting SPI ...");
  debugMessln();

  SPI.begin;

  delay(bootDelay); // delay to be able to see message on LCD
  */

  /*******************************
    Build custom characters
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Building chars ...");

  debugMessln("Building custom characters ...");
  debugMessln();

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

  delay(bootDelay); // delay to be able to see message on LCD

  /*******************************
    Set up rotary encoders
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Setting up encoders ...");

#if DEBUG
  debugMessln("Setting up rotary encoders  ...");
  debugMessln();
#endif

  rotary1.setTrigger(HIGH); // set the trigger to be either a HIGH or LOW pin (Default: HIGH), note this sets all three pins to use the same state
  rotary1.setDebounceDelay(debounceDelay);
  rotary1.setErrorDelay(errorDelay);

  rotary2.setTrigger(HIGH);
  rotary2.setDebounceDelay(debounceDelay);
  rotary2.setErrorDelay(errorDelay);

  delay(bootDelay); // delay to be able to see message on LCD

  /*******************************
    Start FM radio receiver
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Starting receiver ...");

  debugMessln("Starting FM radio receiver  ...");
  debugMessln();

  radio.init(); // initialize radio

#if DEBUG
  radio.debugEnable(); // enable information to the serial port
#endif

  setReceiver(); // tune the radio receiver

#if DEBUG
  printRadioDebugInfo();
#endif

  delay(bootDelay); // delay to be able to see message on LCD

  /*******************************
    Start DFPlayer Mini
  *******************************/
  /*
    lcd.setCursor(0, 1);
    lcd.print("Starting sw serial ...");

    debugMessln("Start software serial  ...");
    debugMessln()

    mySoftwareSerial.begin(9600);

    lcd.setCursor(0, 1);
    lcd.print("Starting DFPlayer Mini ...");

    delay(bootDelay); // delay to be able to see message on LCD

    debugMessln("DFRobot DFPlayer Mini");
    debugMessln("Starting DFPlayer Mini ...");
    debugMessln();

    if (!myDFPlayer.begin(mySoftwareSerial)) {
      debugMessln("Could not initialize DFPlayer mini: ");
      debugMessln("1. Check DFPlayer connections");
      debugMessln("2. Insert SD card");
      while (true);
    }
    debugMessln("DFPlayer Mini ready");
    debugMessln()

    myDFPlayer.setTimeOut(mySoftwareSerialTimeOut); // timeout serial 500ms
    myDFPlayer.volume(sdVolume); // volume 10, between 0 and 30
    myDFPlayer.EQ(0); // equalizer set to normal

    maxSDSongs = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD); // count number of tracks on sd card
    debugMess("Number of tracks on SD card: ");
    debugMessln(maxSDSongs);
    debugMessln()

    menu_opcoes(); // mostra o menu de comandos

    delay(bootDelay); // delay to be able to see message on LCD
  */

  /*******************************
    Fill LCD
  *******************************/
  printSource();
  printFunction();

  setVolume();

  debugMessln("Setup finished, entering main loop ...");
}

void loop()
{

  readButtons();

  if (millis() - button1Millis >= screenWait)
  { // return to home screen after wait time
    functionNo = 0;
    sourceNo = selectSourceNo; // source might have been changed
  }

  if (millis() - button2Millis >= screenWait && sourceNo == 0 && presetScreen)
  { // return to home screen after wait time
    presetScreen = false;
    printFM();
  }

  if (sourceNo == 0 && frequency != oldFrequency)
  { // tune in to new radio frequency
    setReceiver();
    oldFrequency = frequency;
  }

  if (functionNo != oldFunctionNo)
  { // new function for second row on LCD has been selected
    printFunction();
    oldFunctionNo = functionNo;
  }

  if (volume != oldVolume)
  { // volume has been changed
    printVolume();
    setVolume();
    oldVolume = volume;
  }

  if (balance != oldBalance)
  { // balance has been changed
    printBalance();
    setVolume();
    oldBalance = balance;
  }

  if (sourceNo != oldSourceNo)
  { // new source has been selected
    printSource();
    setMux(); // select source via multiplexer

    if (sourceNo == 0)
    {                       // FM radio is selected
      radio.setMute(false); // unmute the radio
      setReceiver();        // set frequency on receiver
    }
    else
    {
      radio.setMute(true); // mute the radio

      debugMessln("Radio muted");
      debugMessln();
    }

    if (sourceNo == 1)
    { // unmute bluetooth if selected
      digitalWrite(btMute, LOW);
    }
    else
    {
      digitalWrite(btMute, HIGH);

      debugMessln("Bluetooth muted");
      debugMessln();
    }

    if (functionNo == 1)
    {
      printSourceSelect();
    }

    oldSourceNo = sourceNo;
  }
}

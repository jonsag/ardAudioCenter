
#include "Arduino.h"

#include "configuration.h" // sets all variables

#include "lcd.h"          // manages all info on LCD
#include "radioTEA5767.h" // control the FM radio module

#if DFPLAYER
#include "sdCard.h" // control the DFPlayer Mini SD Card module
#endif

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
#if DEBUG || INFO
  lcd.setCursor(0, 1);
  lcd.print("Starting serial ...");

  Serial.begin(serialSpeed);

  delay(bootDelay); // delay to be able to see message on LCD
#endif

  /*******************************
    Print start information
  *******************************/
  infoMessln(programName);
  infoMessln(date);
  infoMessln("by ");
  infoMessln(author);
  infoMessln(email);

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
  pinMode(btOn, OUTPUT); // mute output on bluetooth module
  digitalWrite(btMute, HIGH);
  digitalWrite(btOn, LOW);

  delay(bootDelay); // delay to be able to see message on LCD

  /*******************************
    Starting SPI interface
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Starting SPI ...");

  debugMessln("Starting SPI ...");
  debugMessln();

  SPI.begin();

  delay(bootDelay); // delay to be able to see message on LCD

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
#if DFPLAYER
  lcd.setCursor(0, 1);
  lcd.print("Starting sw serial ...");

  debugMessln("Starting software serial  ...");
  debugMessln();

  mySoftwareSerial.begin(9600);

  delay(bootDelay); // delay to be able to see message on LCD
#endif

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

  // ******************** handle buttons *******************
  readButtons();

  if (millis() - button1Millis >= screenWait) // return to home screen after wait time
  {
    functionNo = 0;
    sourceNo = selectSourceNo; // source might have been changed
  }

  if (millis() - button2Millis >= screenWait && sourceNo == 0 && presetScreen) // return to home screen after wait time
  {
    presetScreen = false;
    printFM();
  }

  // ******************* act on changes *******************
  /**********
   * radio frequency has changed
   **********/
  if (sourceNo == 0 && frequency != oldFrequency) // tune in to new radio frequency
  {
    setReceiver();
    oldFrequency = frequency;
  }

  /**********
   * function (Vol, Src, Bal) has changed
   **********/
  if (functionNo != oldFunctionNo) // new function for second row on LCD has been selected
  {
    printFunction();
    oldFunctionNo = functionNo;
  }

  /**********
   * volume has changed
   **********/
  if (volume != oldVolume && functionNo == 0) // volume has been changed
  {
    printVolume();
    setVolume();
    oldVolume = volume;
  }

  /**********
   * balance has changed
   **********/
  if (balance != oldBalance) // balance has been changed
  {
    printBalance();
    setVolume();
    oldBalance = balance;
  }

/**********
 * DFPlayer track number has changed
 **********/
#if DFPLAYER
  if (sourceNo == 3 && trackNo != oldTrackNo) // balance has been changed
  {
    printTrackNo();
    playTrackNo();
    oldTrackNo = trackNo;
  }
#endif

  /**********
   * source has changed
   **********/
  if (sourceNo != oldSourceNo) // new source has been selected
  {
    printSource();
    setMux(); // select source via multiplexer

    if (sourceNo == 0) // FM radio is selected
    {
      radio.setMute(false); // unmute the radio
      setReceiver();        // set frequency on receiver
    }
    else
    {
      radio.setMute(true); // mute the radio

      debugMessln("Radio muted");
      debugMessln();
    }

    if (sourceNo == 1) // bluetooth selected
    {
      digitalWrite(btMute, LOW); // unmute bluetooth
      digitalWrite(btOn, HIGH); // power on the bluetooth module
    }
    else
    {
      digitalWrite(btMute, HIGH); // mute bluetooth
      digitalWritwe(btOn, LOW); // power off the bluetooth module

      debugMessln("Bluetooth muted and off");
      debugMessln();
    }

#if DFPLAYER
    if (sourceNo == 3) // DFPlayer selected
    {
      startDFPlayer(); // initiate DFPlayer
    }
    else
    {
      myDFPlayer.pause(); // pause the mp3

      debugMessln("DFPlayer paused");
      debugMessln();
    }
#endif

    if (functionNo == 1)
    {
      printSourceSelect();
    }

    oldSourceNo = sourceNo;
  }
}

#include "Arduino.h"

#include "configuration.h" // sets all variables
#include "radioTEA5767.h"  // control the FM radio module
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
  lcd.print("Booting ...");

  delay(bootDelay); // delay to be able to see message on LCD

  /*******************************
    Start serial
  *******************************/
#ifdef __DEBUG__
  lcd.setCursor(0, 1);
  lcd.print("Starting serial ...");

  delay(bootDelay); // delay to be able to see message on LCD

  Serial.begin(serialSpeed);
#endif

  /*******************************
    Print start information
  *******************************/
  DEBUG(programName);
  DEBUG("\n");
  DEBUG(date);
  DEBUG("\n");
  DEBUG("by ");
  DEBUG("\n");
  DEBUG(author);
  DEBUG("\n");
  DEBUG(email);
  DEBUG("\n\n");

  DEBUG("Number of sources: ");
  DEBUG(sizeof(sources) / sizeof(sources[0]));
  DEBUG("\n\n");

  DEBUG("Source selected: ");
  DEBUG(sourceNo);
  DEBUG("\n");
  DEBUG(sources[sourceNo]);
  DEBUG("\n\n");

  DEBUG("Function selected: ");
  DEBUG(functionNo);
  DEBUG("\n");
  DEBUG(functions[functionNo]);
  DEBUG("\n\n");

  DEBUG("Volume: ");
  DEBUG(volume);
  DEBUG("%");
  DEBUG("\n");
  DEBUG("Balance: ");
  DEBUG(balance);
  DEBUG("\n\n");

  DEBUG("FM radio frequency: ");
  DEBUG(frequency);
  DEBUG("\n");
  /* commented out beacause TEA5767 doesn't seem to have this option
    DEBUG("FM radio volume: ");
    DEBUG(radioVolume);
  */
  DEBUG("\n\n");

  /*******************************
    Define pins
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Defining pins ...");

  delay(bootDelay); // delay to be able to see message on LCD

  DEBUG("Defining pins ...");
  DEBUG("\n\n");

  for (int i = 0; i < 2; i++)
  { // define multiplexer pins
    pinMode(muxPins[i], OUTPUT);
    digitalWrite(muxPins[i], LOW);
  }

  pinMode(csPL, OUTPUT); // chip select for left channel potentiometer
  pinMode(csPR, OUTPUT); // chip select for right channel potentiometer
  digitalWrite(csPL, HIGH);
  digitalWrite(csPR, HIGH);

  pinMode(btMute, OUTPUT); // mute output on bluetooth module
  digitalWrite(btMute, HIGH);

  /*******************************
    Starting SPI interface
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Starting SPI ...");

  delay(bootDelay); // delay to be able to see message on LCD

  DEBUG("Starting SPI ...");
  DEBUG("\n\n");

  SPI.begin;

  /*******************************
    Build custom characters
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Building chars ...");

  delay(bootDelay); // delay to be able to see message on LCD

  DEBUG("Building custom characters ...");
  DEBUG("\n\n");

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

delay(bootDelay); // delay to be able to see message on LCD

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

  delay(bootDelay); // delay to be able to see message on LCD

  DEBUG("Starting FM radio receiver  ...");
  DEBUG("\n\n");

  radio.init(); // initialize radio

#ifdef __DEBUG__
  radio.debugEnable(); // enable information to the serial port
#endif

  setReceiver(); // tune the radio receiver

#ifdef __DEBUG__
  printRadioDebugInfo();
#endif

  /*******************************
    Start DFPlayer Mini
  *******************************/
  /*
    lcd.setCursor(0, 1);
    lcd.print("Starting sw serial ...");

    delay(bootDelay); // delay to be able to see message on LCD

    DEBUG("Start software serial  ...");
    DEBUG("\n\n")

    mySoftwareSerial.begin(9600);

    lcd.setCursor(0, 1);
    lcd.print("Starting DFPlayer Mini ...");

    delay(bootDelay); // delay to be able to see message on LCD

    DEBUG("DFRobot DFPlayer Mini");
    DEBUG("\n")
      DEBUG("Starting DFPlayer Mini ...");
    DEBUG("\n\n");

    if (!myDFPlayer.begin(mySoftwareSerial)) {
      DEBUG("Could not initialize DFPlayer mini: ");
      DEBUG("\n");
      DEBUG("1. Check DFPlayer connections");
      DEBUG("\n")
      DEBUG("2. Insert SD card");
      DEBUG("\n");
      while (true);
    }
    DEBUG("DFPlayer Mini ready");
    DEBUG("\n\n")

    myDFPlayer.setTimeOut(mySoftwareSerialTimeOut); // timeout serial 500ms
    myDFPlayer.volume(sdVolume); // volume 10, between 0 and 30
    myDFPlayer.EQ(0); // equalizer set to normal

    maxSDSongs = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD); // count number of tracks on sd card
    DEBUG("Number of tracks on SD card: ");
      DEBUG(maxSDSongs);
    DEBUG("\n\n")

    menu_opcoes(); // mostra o menu de comandos
  */

  /*******************************
    Fill LCD
  *******************************/
  printSource();
  printFunction();

  setVolume();
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

      DEBUG("Radio muted");
      DEBUG("\n\n");
    }

    if (sourceNo == 1)
    { // unmute bluetooth if selected
      digitalWrite(btMute, LOW);
    }
    else
    {
      digitalWrite(btMute, HIGH);

      DEBUG("Bluetooth muted");
      DEBUG("\n\n");
    }

    if (functionNo == 1)
    {
      printSourceSelect();
    }

    oldSourceNo = sourceNo;
  }
}

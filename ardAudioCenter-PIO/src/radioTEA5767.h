
TEA5767 radio; // create an instance of class for Si4703 chip, pinout SDA and SCL, arduino uno pins A4 and A5

#if useRDS
RDSParser rds; /// get a RDS parser
#endif

enum RADIO_STATE // state definition for this radio implementation
{
  STATE_PARSECOMMAND, ///< waiting for a new command character.

  STATE_PARSEINT, ///< waiting for digits for the parameter.
  STATE_EXEC      ///< executing the command.
};

RADIO_STATE state; // the state variable is used for parsing input characters

#if useRDS
void DisplayServiceName(char *name) /// update the service name text on the LCD display
{
  debugMess("RDS:");
  debugMessln(name);
}

void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4)
{
  rds.processData(block1, block2, block3, block4);
}
#endif

void printRadioDebugInfo()
{
#if DEBUG
  char s[12];
  radio.formatFrequency(s, sizeof(s));

  debugMess("Station:");
  debugMessln(s);

  debugMess("Radio:");
  radio.debugRadioInfo();

  debugMess("Audio:");
  radio.debugAudioInfo();

  debugMessln();
#endif
}

void setReceiver()
{
  radio.setBandFrequency(radioBand, frequency + 1); // set band and station
  // radio.setFrequency(frequency); // on power on, go to preset frequency

  // radio.setVolume(radioVolume); // commented out because TEA5767 doesn't seem to have this option
  radio.setMono(false);

  printRadioDebugInfo();
}

////////// anything below this line is directly from the web page mentioned up top, and is not used in this sketch
/*
  enum RADIO_STATE { /// State definition for this radio implementation.
  STATE_NONE = 0,
  STATE_PARSECOMMAND, ///< waiting for a new command character.
  STATE_PARSEINT,     ///< waiting for digits for the parameter.
  STATE_EXEC,          ///< executing the command.

  STATE_FREQ,
  STATE_VOL,
  STATE_MONO,
  STATE_SMUTE

  };

  RADIO_STATE state; ///< The state variable is used for parsing input characters.
  RADIO_STATE rot_state;

  .void DisplayFrequency(RADIO_FREQ f) { /// Update the Frequency on the LCD display
  char s[12];
  radio.formatFrequency(s, sizeof(s));
  debugMess("FREQ:");
  debugMessln(s);
  lcd.setCursor(0, 0);
  lcd.print(s);
  }

  void DisplayServiceName(char *name) { /// Update the ServiceName text on the LCD display when in RDS mode.
  debugMess("RDS:");
  debugMessln(name);
  if (rot_state == STATE_FREQ) {
    lcd.setCursor(0, 1);
    lcd.print(name);
  }
  }

  void DisplayTime(uint8_t hour, uint8_t minute) {  // Display time
  debugMess("RDS-Time:");
  if (hour < 10) debugMess('0');
  debugMess(hour);
  debugMess(':');
  if (minute < 10) debugMess('0');
  debugMess(minute);
  }

  void DisplayVolume(uint8_t v) { /// Display the current volume.
  debugMess("VOL: "); debugMessln(v);

  lcd.setCursor(0, 1);
  lcd.print("VOL: "); lcd.print(v);
  } // DisplayVolume()

  void DisplayMono(uint8_t v) { /// Display the current mono switch.
  debugMess("MONO: ");
  debugMessln(v);
  lcd.setCursor(0, 1);
  lcd.print("MONO: ");
  lcd.print(v);
  } // DisplayMono()

  void DisplaySoftMute(uint8_t v) { /// Display the current soft mute switch.
  debugMess("SMUTE: ");
  debugMessln(v);
  lcd.setCursor(0, 1);
  lcd.print("SMUTE: ");
  lcd.print(v);
  } // DisplaySoftMute()

  void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4) {
  rds.processData(block1, block2, block3, block4);
  }
*/

// An example of how to implement the TEA5767 arduino module can be found at https://github.com/mathertel/Radio/blob/master/examples/LCDRadio/LCDRadio.ino

void setReceiver() {
  radio.setBandFrequency(radioBand, frequency); // set band and station
  //radio.setFrequency(frequency); // on power on go to preset frequency (SR P4 Gotland)

  //radio.setVolume(radioVolume); // commented out beacause TEA5767 doesn't seem to have this option
  radio.setMono(false);
}

void printRadioDebugInfo() {
  char s[12];
  radio.formatFrequency(s, sizeof(s));
  Serial.print("Station:"); 
  Serial.println(s);
  
  Serial.print("Radio:"); 
  radio.debugRadioInfo();
  
  Serial.print("Audio:"); 
  radio.debugAudioInfo();

  Serial.println();
}


////////// anything below this line is directly from the web page mentione up top, and is not used in this sketch
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
  Serial.print("FREQ:"); Serial.println(s);
  lcd.setCursor(0, 0);
  lcd.print(s);
}

void DisplayServiceName(char *name) { /// Update the ServiceName text on the LCD display when in RDS mode.
  Serial.print("RDS:"); Serial.println(name);
  if (rot_state == STATE_FREQ) {
    lcd.setCursor(0, 1);
    lcd.print(name);
  }
}

void DisplayTime(uint8_t hour, uint8_t minute) {  // Display time
  Serial.print("RDS-Time:");
  if (hour < 10) Serial.print('0');
  Serial.print(hour);
  Serial.print(':');
  if (minute < 10) Serial.print('0');
  Serial.print(minute);
}

void DisplayVolume(uint8_t v) { /// Display the current volume.
  Serial.print("VOL: "); Serial.println(v);

  lcd.setCursor(0, 1);
  lcd.print("VOL: "); lcd.print(v);
} // DisplayVolume()

void DisplayMono(uint8_t v) { /// Display the current mono switch.
  Serial.print("MONO: "); Serial.println(v);
  lcd.setCursor(0, 1);
  lcd.print("MONO: "); lcd.print(v);
} // DisplayMono()

void DisplaySoftMute(uint8_t v) { /// Display the current soft mute switch.
  Serial.print("SMUTE: "); Serial.println(v);
  lcd.setCursor(0, 1);
  lcd.print("SMUTE: "); lcd.print(v);
} // DisplaySoftMute()

void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4) {
  rds.processData(block1, block2, block3, block4);
}
*/

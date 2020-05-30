void writeVolumes() {
  if (debug) {
    Serial.println();
    Serial.print("Volume left: ");
    Serial.println(volL);
    Serial.print("Volume right: ");
    Serial.println(volR);
  }

  digitalWrite(csPL, LOW); // set volume for left channel
  SPI.transfer(B00010001); // tell the chip to set the pot
  SPI.transfer(volL);     // set pot position
  digitalWrite(csPL, HIGH);

  digitalWrite(csPR, LOW); // set volume for right channel
  SPI.transfer(B00010001); // tell the chip to set the pot
  SPI.transfer(volR);     // set pot position
  digitalWrite(csPR, HIGH);

}

void setVolume() {
  volumeVal = 255 * volume / 100;

  if (debug) {
    Serial.println();
    Serial.print("Volume value: ");
    Serial.println(volumeVal);
  }

  if (balance < 10) { // shift sound center to the left
    volR = volumeVal * balance / 10;
  } else {
    volR = volumeVal;
  }

  if (balance > 10) { // shift sound center to the right
    volL = volumeVal * (20 - balance) / 10;
  } else {
    volL = volumeVal;
  }

  writeVolumes();
}

void writeVolumes()
{
  DEBUG("Volume left: ");
  DEBUG(volL);
  DEBUG("\n");
  DEBUG("Volume right: ");
  DEBUG("\n");

  digitalWrite(csPL, LOW); // set volume for left channel
  SPI.transfer(B00010001); // tell the chip to set the pot
  SPI.transfer(volL);      // set pot position
  digitalWrite(csPL, HIGH);

  digitalWrite(csPR, LOW); // set volume for right channel
  SPI.transfer(B00010001); // tell the chip to set the pot
  SPI.transfer(volR);      // set pot position
  digitalWrite(csPR, HIGH);
}

void setVolume()
{
  volumeVal = 255 * volume / 100;

  DEBUG("Volume value: ");
  DEBUG(volumeVal);
  DEBUG("\n");

  if (balance < 10)
  { // shift sound center to the left
    volR = volumeVal * balance / 10;
  }
  else
  {
    volR = volumeVal;
  }

  if (balance > 10)
  { // shift sound center to the right
    volL = volumeVal * (20 - balance) / 10;
  }
  else
  {
    volL = volumeVal;
  }

  writeVolumes();
}

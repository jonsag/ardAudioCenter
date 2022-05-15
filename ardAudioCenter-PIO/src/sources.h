void setMux()
{
  if (sourceNo == 1) // bluetooth
  {
    digitalWrite(muxPins[0], HIGH); // A0, D14 -> A, least significant bit
    digitalWrite(muxPins[1], LOW);  // A1, D15 -> B
  }
  else if (sourceNo == 2) // line in
  {
    digitalWrite(muxPins[0], LOW);
    digitalWrite(muxPins[1], HIGH);
  }
  else if (sourceNo == 3) // SD card
  {
    digitalWrite(muxPins[0], HIGH);
    digitalWrite(muxPins[1], HIGH);
  }
  else // FM radio
  {
    digitalWrite(muxPins[0], LOW);
    digitalWrite(muxPins[1], LOW);
  }
}

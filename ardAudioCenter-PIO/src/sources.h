void setMux()
{
  if (sourceNo == 1) // bluetooth
  {
    digitalWrite(muxPin0, HIGH); // A0, D14 -> A, least significant bit
    digitalWrite(muxPin1, LOW);  // A1, D15 -> B, most significant bit
  }
  else if (sourceNo == 2) // line in
  {
    digitalWrite(muxPin0, LOW);
    digitalWrite(muxPin1, HIGH);
  }
  else if (sourceNo == 3) // SD card
  {
    digitalWrite(muxPin0, HIGH);
    digitalWrite(muxPin1, HIGH);
  }
  else // FM radio
  {
    digitalWrite(muxPin0, LOW);
    digitalWrite(muxPin1, LOW);
  }
}

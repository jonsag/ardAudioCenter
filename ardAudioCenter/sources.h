void setMux() {
  if (sourceNo == 1) {
    digitalWrite(muxPins[0], HIGH);
    digitalWrite(muxPins[1], LOW);
  } else if (sourceNo == 2) {
    digitalWrite(muxPins[0], LOW);
    digitalWrite(muxPins[1], HIGH);
  } else if (sourceNo == 3) {
    digitalWrite(muxPins[0], HIGH);
    digitalWrite(muxPins[1], HIGH);
  } else {
    digitalWrite(muxPins[0], LOW);
    digitalWrite(muxPins[1], LOW);
  }
}

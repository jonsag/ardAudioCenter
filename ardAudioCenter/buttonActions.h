/*******************************
  encoder1
*******************************/

void button1Action() {

  Serial.println("Button on rotary encoder 1 pressed");

  functionNo++;
  if (functionNo > 2) {
    functionNo = 0;
  }

  Serial.print("Function no: ");
  Serial.println(functionNo);

}

void increaseVolume() {
  volume += 5;
  if (volume > 100) {
    volume = 100;
  }
  Serial.print("Volume: ");
  Serial.println(volume);
}

void decreaseVolume() {
  volume -= 5;
  if (volume < 0 || volume > 100) {
    volume = 0;
  }
  Serial.print("Volume: ");
  Serial.println(volume);
}

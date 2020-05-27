/*******************************
  encoder1
*******************************/
void button1Action() {

  Serial.println("Button on rotary encoder 1 pressed");

  functionNo += 1;
  if (functionNo > 2) {
    functionNo = 0;
  }

}

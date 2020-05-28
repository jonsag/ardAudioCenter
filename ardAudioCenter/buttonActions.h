/*******************************
  encoder1
*******************************/

void button1Action() {

  Serial.println("Button on rotary encoder 1 pressed");

  functionNo++;
  if (functionNo > sizeof(functions) / sizeof(functions[0]) - 1) {
    functionNo = 0;
  }

  Serial.print("Function no: ");
  Serial.println(functionNo);
  Serial.println(functions[functionNo]); 
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

void sourceUp() {
  sourceNo += 1;
  if (sourceNo > sizeof(sources) / sizeof(sources[0]) - 1) {
    sourceNo = 0;
  }
  Serial.print("Source no: ");
  Serial.println(sourceNo);
  Serial.print(sources[sourceNo]);
}

void sourceDown() {
  sourceNo -= 1;
  if (sourceNo < 0 || sourceNo > sizeof(sources) / sizeof(sources[0]) - 1) {
    sourceNo = sizeof(sources) / sizeof(sources[0]) - 1;
  }
  Serial.print("Source no: ");
  Serial.println(sourceNo);
  Serial.print(sources[sourceNo]);
}

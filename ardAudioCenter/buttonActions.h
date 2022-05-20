/*******************************
  Rotary encoder 1
*******************************/

void button1Action() {

  functionNo++;
  if (functionNo > sizeof(functions) / sizeof(functions[0]) - 1) {
    functionNo = 0;
  }

  if (functionNo == 1) {
    selectSourceNo = sourceNo;
  }

  if (debug) {
    Serial.print("Function no: ");
    Serial.println(functionNo);
    Serial.println(functions[functionNo]);
  }
}

void increaseVolume() {
  volume += 5;
  if (volume > 100) {
    volume = 100;
  }

  if (debug) {
    Serial.print("Volume: ");
    Serial.println(volume);
  }
}

void decreaseVolume() {
  volume -= 5;
  if (volume < 0 || volume > 100) {
    volume = 0;
  }

  if (debug) {
    Serial.print("Volume: ");
    Serial.println(volume);
  }
}

void sourceUp() {
  selectSourceNo += 1;

  if (selectSourceNo > sizeof(sources) / sizeof(sources[0]) - 1) {
    selectSourceNo = 0;
  }

  printSourceSelect();

  if (debug) {
    Serial.print("Select source no: ");
    Serial.println(selectSourceNo);
    Serial.println(sources[selectSourceNo]);
  }
}

void sourceDown() {
  selectSourceNo -= 1;

  if (selectSourceNo < 0 || selectSourceNo > sizeof(sources) / sizeof(sources[0]) - 1) {
    selectSourceNo = sizeof(sources) / sizeof(sources[0]) - 1;
  }

  printSourceSelect();

  if (debug) {
    Serial.print("Select source no: ");
    Serial.println(selectSourceNo);
    Serial.println(sources[selectSourceNo]);
  }
}

void balanceRight() {
  balance += 1;

  if (balance > 20) {
    balance = 20;
  }

  printBalance();

  if (debug) {
    Serial.print("Balance: ");
    Serial.println(balance);
  }
}

void balanceLeft() {
  balance -= 1;

  if (balance < 0 || balance > 20) {
    balance = 0;
  }

  printBalance();

  if (debug) {
    Serial.print("Balance: ");
    Serial.println(balance);
  }
}

/*******************************
  Rotary encoder 2
*******************************/
void increaseFreq() {
  frequency += frequencyStep;

  if (frequency > maxFrequency) {
    frequency = maxFrequency;
  }

  if (debug) {
    Serial.print("Frequency: ");
    Serial.println(frequency);
  }

  printFM();

}

void decreaseFreq() {
  frequency -= frequencyStep;

  if (frequency < minFrequency) {
    frequency = minFrequency;
  }

  if (debug) {
    Serial.print("Frequency: ");
    Serial.println(frequency);
  }
  
  printFM();

}

void button2Action() {
  presetScreen = true;

  printFMPreset();
}

void presetUp() {
  presetNo++;
  if (presetNo > sizeof(preset) / sizeof(preset[0]) - 1) {
    presetNo = 0;
  }

  frequency = preset[presetNo];

  if (debug) {
    Serial.print("Preset: ");
    Serial.print(presetNo);
    Serial.print(": ");
    Serial.println(frequency);
  }

  printFMPreset();
}

void presetDown() {
  presetNo--;
  if (presetNo < 0 || presetNo > sizeof(preset) / sizeof(preset[0]) - 1) {
    presetNo = sizeof(preset) / sizeof(preset[0]) - 1;
  }

  frequency = preset[presetNo];

  if (debug) {
    Serial.print("Preset: ");
    Serial.print(presetNo);
    Serial.print(": ");
    Serial.println(frequency);
  }

  printFMPreset();
}

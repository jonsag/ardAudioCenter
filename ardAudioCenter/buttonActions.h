/*******************************
  encoder1
*******************************/

void button1Action() {
  if (debug) {
    Serial.println("Button on rotary encoder 1 pressed");
  }

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

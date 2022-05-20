/*******************************
  Rotary encoder 1
*******************************/

void button1Action()
{
  functionNo++;
  if (functionNo > sizeof(functions) / sizeof(functions[0]) - 1)
  {
    functionNo = 0;
  }

  if (functionNo == 1)
  {
    selectSourceNo = sourceNo;
  }

  debugMess("Function no: ");
  debugMessln(functionNo);
  debugMessln(functions[functionNo]);
  debugMessln();
}

void increaseVolume()
{
  volume += volumeStep;
  if (volume > 100)
  {
    volume = 100;
  }

  debugMess("Volume: ");
  debugMessln(volume);
  debugMessln();
}

void decreaseVolume()
{
  volume -= volumeStep;
  if (volume < 0 || volume > 100)
  {
    volume = 0;
  }

  debugMess("Volume: ");
  debugMessln(volume);
  debugMessln();
}

void sourceUp()
{
  selectSourceNo += 1;

  if (selectSourceNo > sizeof(sources) / sizeof(sources[0]) - 1)
  {
    selectSourceNo = 0;
  }

  printSourceSelect();

  debugMess("Select source no: ");
  debugMessln(selectSourceNo);
  debugMessln(sources[selectSourceNo]);
  debugMessln();
}

void sourceDown()
{
  selectSourceNo -= 1;

  if (selectSourceNo < 0 || selectSourceNo > sizeof(sources) / sizeof(sources[0]) - 1)
  {
    selectSourceNo = sizeof(sources) / sizeof(sources[0]) - 1;
  }

  printSourceSelect();

  debugMess("Select source no: ");
  debugMessln(selectSourceNo);
  debugMess(sources[selectSourceNo]);
  debugMessln();
}

void balanceRight()
{
  balance += balanceStep;

  if (balance > 20)
  {
    balance = 20;
  }

  printBalance();

  debugMess("Balance: ");
  debugMessln(balance);
  debugMessln();
}

void balanceLeft()
{
  balance -= balanceStep;

  if (balance < 0 || balance > 20)
  {
    balance = 0;
  }

  printBalance();

  debugMess("Balance: ");
  debugMessln(balance);
  debugMessln();
}

/*******************************
  Rotary encoder 2
*******************************/
void increaseFreq()
{
  frequency += frequencyStep;

  if (frequency > maxFrequency)
  {
    frequency = maxFrequency;
  }

  debugMess("Frequency: ");
  debugMessln(frequency);
  debugMessln();

  printFM();
}

void decreaseFreq()
{
  frequency -= frequencyStep;

  if (frequency < minFrequency)
  {
    frequency = minFrequency;
  }

  debugMess("Frequency: ");
  debugMessln(frequency);
  debugMessln();

  printFM();
}

void button2Action()
{
  presetScreen = true;

  printFMPreset();
}

void presetUp()
{
  presetNo++;

  if (presetNo > sizeof(preset) / sizeof(preset[0]) - 1)
  {
    presetNo = 0;
  }

  frequency = preset[presetNo];

  debugMess("Preset: ");
  debugMess(presetNo);
  debugMess(": ");
  debugMessln(frequency);
  debugMessln();

  printFMPreset();
}

void presetDown()
{
  presetNo--;
  
  if (presetNo < 0 || presetNo > sizeof(preset) / sizeof(preset[0]) - 1)
  {
    presetNo = sizeof(preset) / sizeof(preset[0]) - 1;
  }

  frequency = preset[presetNo];

  debugMess("Preset: ");
  debugMess(presetNo);
  debugMess(": ");
  debugMessln(frequency);
  debugMessln();

  printFMPreset();
}

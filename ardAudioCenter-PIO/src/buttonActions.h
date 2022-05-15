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

  DEBUG("Function no: ");
  DEBUG(functionNo);
  DEBUG("\n");
  DEBUG(functions[functionNo]);
  DEBUG("\n\n");
}

void increaseVolume()
{
  volume += 5;
  if (volume > 100)
  {
    volume = 100;
  }

  DEBUG("Volume: ");
  DEBUG(volume);
  DEBUG("\n\n");
}

void decreaseVolume()
{
  volume -= 5;
  if (volume < 0 || volume > 100)
  {
    volume = 0;
  }

  DEBUG("Volume: ");
  DEBUG(volume);
  DEBUG("\n\n");
}

void sourceUp()
{
  selectSourceNo += 1;

  if (selectSourceNo > sizeof(sources) / sizeof(sources[0]) - 1)
  {
    selectSourceNo = 0;
  }

  printSourceSelect();

  DEBUG("Select source no: ");
  DEBUG(selectSourceNo);
  DEBUG("\n");
  DEBUG(sources[selectSourceNo]);
  DEBUG("\n\n");
}

void sourceDown()
{
  selectSourceNo -= 1;

  if (selectSourceNo < 0 || selectSourceNo > sizeof(sources) / sizeof(sources[0]) - 1)
  {
    selectSourceNo = sizeof(sources) / sizeof(sources[0]) - 1;
  }

  printSourceSelect();

  DEBUG("Select source no: ");
  DEBUG(selectSourceNo);
  DEBUG("\n");
  DEBUG(sources[selectSourceNo]);
  DEBUG("\n\n");
}

void balanceRight()
{
  balance += 1;

  if (balance > 20)
  {
    balance = 20;
  }

  printBalance();

  DEBUG("Balance: ");
  DEBUG(balance);
  DEBUG("\n\n");
}

void balanceLeft()
{
  balance -= 1;

  if (balance < 0 || balance > 20)
  {
    balance = 0;
  }

  printBalance();

  DEBUG("Balance: ");
  DEBUG(balance);
  DEBUG("\n\n");
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

  DEBUG("Frequency: ");
  DEBUG(frequency);
  DEBUG("\n\n");

  printFM();
}

void decreaseFreq()
{
  frequency -= frequencyStep;

  if (frequency < minFrequency)
  {
    frequency = minFrequency;
  }

  DEBUG("Frequency: ");
  DEBUG(frequency);
  DEBUG("\n\n");

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

  DEBUG("Preset: ");
  DEBUG(presetNo);
  DEBUG(": ");
  DEBUG(frequency);
  DEBUG("\n\n");

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

  DEBUG("Preset: ");
  DEBUG(presetNo);
  DEBUG(": ");
  DEBUG(frequency);
  DEBUG("\n\n");

  printFMPreset();
}

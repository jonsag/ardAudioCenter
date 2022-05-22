
void printDetail(uint8_t type, int value)
{
  switch (type)
  {
  case TimeOut:
    Serial.println("Time Out!");
    break;
  case WrongStack:
    Serial.println("Stack Wrong!");
    break;
  case DFPlayerCardInserted:
    Serial.println("Card Inserted!");
    break;
  case DFPlayerCardRemoved:
    Serial.println("Card Removed!");
    break;
  case DFPlayerCardOnline:
    Serial.println("Card Online!");
    break;
  case DFPlayerUSBInserted:
    Serial.println("USB Inserted!");
    break;
  case DFPlayerUSBRemoved:
    Serial.println("USB Removed!");
    break;
  case DFPlayerPlayFinished:
    Serial.print("Number:");
    Serial.print(value);
    Serial.println(" Play Finished!");
    break;
  case DFPlayerError:
    Serial.print("DFPlayerError:");

    switch (value)
    {
    case Busy:
      Serial.println("Card not found");
      break;
    case Sleeping:
      Serial.println("Sleeping");
      break;
    case SerialWrongStack:
      Serial.println("Get Wrong Stack");
      break;
    case CheckSumNotMatch:
      Serial.println("Check Sum Not Match");
      break;
    case FileIndexOut:
      Serial.println("File Index Out of Bound");
      break;
    case FileMismatch:
      Serial.println("Cannot Find File");
      break;
    case Advertise:
      Serial.println("In Advertise");
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void initDFPlayer()
{
  Serial.println("Starting DFPlayer Mini ...(May take 3~5 seconds)");
  Serial.println();

  if (!myDFPlayer.begin(mySoftwareSerial)) // use softwareSerial to communicate with mp3
  {
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while (true)
      ;
  }
  Serial.println("DFPlayer Mini online!");

  myDFPlayer.setTimeOut(DFPlayerSerialTimeOut);
  myDFPlayer.volume(DFPlayerVolume);
  myDFPlayer.EQ(DFPlayerEQ);
  myDFPlayer.outputDevice(DFPlayerDevice);

  if (myDFPlayer.available()) // print the detail message from DFPlayer to handle different errors and states
  {
#if DEBUG
    printDetail(myDFPlayer.readType(), myDFPlayer.read());
#endif
  }
}

void startDFPlayer()
{
  initDFPlayer();
}

void pause_playDFPlayer()
{
  if (DFPlayerPause)
  {
    myDFPlayer.start(); // start the mp3 from the pause
  }
  else
  {
    myDFPlayer.pause(); // pause the mp3
  }
  printPlayPause();

  DFPlayerPause = !DFPlayerPause;
}

void playTrackNo() {
  myDFPlayer.play(trackNo);  // play track
}
/*
void options_menu()
{
  Serial.println();
  Serial.println("Commands: ");
  Serial.print(" [1-");
  Serial.print(maxSDSongs);
  Serial.println("] Select the MP3 file");
  Serial.println(" [s] stop playback");
  Serial.println(" [p] pause/continue music");
  Serial.println(" [e] select equalization");
  Serial.println(" [+ or -] increase or decrease the volume");
  Serial.println();
}

void playSDCard()
{
  while (Serial.available() > 0) // waits for serial data input
  {
    sdBuf = Serial.readStringUntil('\n'); // retrieve input data

    if ((sdBuf.toInt() >= 1) && (sdBuf.toInt() <= maxSDSongs)) // playback (song index)
    {
      Serial.print("Playing music: ");
      Serial.println(sdBuf.toInt();
      myDFPlayer.play(sdBuf.toInt(); // play the music
      options_menu();
    }

    if (sdBuf == "p") // pause/continue music
    {
      if (sdPause)
      {
        Serial.println("Continue music ...");
        myDFPlayer.start();
      }
      else
      {
        Serial.println("Music paused ...");
        myDFPlayer.pause();
      }
      sdPause = !sdPause;

      options_menu();
    }

    if (sdBuf == "s") // stop
    {
      myDFPlayer.stop();

      Serial.println("Music stopped!");
      options_menu();
    }

    if (sdBuf == "e") // select equalization
    {
      sdEqualizer++;
      if (sdEqualizer == 6)
      {
        sdEqualizer = 0;
      }
      myDFPlayer.EQ(sdEqualizer);

      Serial.print("Equalization: ");
      Serial.print(sdEqualizer);
      Serial.println(" (0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass)");
      options_menu();
    }

    if (sdBuf == "+") // increase volume
    {
      myDFPlayer.volumeUp();
      Serial.print("Current volume: ");
      Serial.println(myDFPlayer.readVolume();
      options_menu();
    }

    if (sdBuf == "-") // decrease volume
    {
      myDFPlayer.volumeDown();
      Serial.print("Current volume: ");
      Serial.println(myDFPlayer.readVolume();
      options_menu();
    }
  } // while
} // loop
*/
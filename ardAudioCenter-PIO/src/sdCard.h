// the recommended library for the DFPlayer Mini is at https://github.com/Arduinolibrary/DFRobot_Mini_Player
// but I use the one at https://github.com/DFRobot/DFRobotDFPlayerMini

// Code on this page originates from https://www.instructables.com/id/MP3-Player-With-Arduino/

void options_menu()
{
  debugMessln();
  debugMessln("Commands: ");
  debugMess(" [1-");
  debugMess(maxSDSongs);
  debugMessln("] Select the MP3 file");
  debugMessln(" [s] stop playback");
  debugMessln(" [p] pause/continue music");
  debugMessln(" [e] select equalization");
  debugMessln(" [+ or -] increase or decrease the volume");
  debugMessln();
}

void playSDCard()
{
  while (Serial.available() > 0) // waits for serial data input
  {
    sdBuf = Serial.readStringUntil('\n'); // retrieve input data

    if ((sdBuf.toInt() >= 1) && (sdBuf.toInt() <= maxSDSongs)) // playback (song index)
    {
      debugMess("Playing music: ");
      debugMessln(sdBuf.toInt());
      myDFPlayer.play(sdBuf.toInt()); // play the music
      menu_opcoes();
    }

    if (sdBuf == "p") // pause/continue music
    {
      if (sdPause)
      {
        debugMessln("Continue music ...");
        myDFPlayer.start();
      }
      else
      {
        debugMessln("Music paused ...");
        myDFPlayer.pause();
      }
      sdPause = !sdPause;

      options_menu();
    }

    if (sdBuf == "s") // stop
    {
      myDFPlayer.stop();
      debugMessln("Music stopped!");
      options_menu()();
    }

    if (sdBuf == "e") // select equalization
    {
      sdEqualizer++;
      if (sdEqualizer == 6)
      {
        sdEqualizer = 0;
      }
      myDFPlayer.EQ(sdEqualizer);
      debugMess("Equalization: ");
      debugMess(sdEqualizer);
      debugMessln(" (0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass)");
      options_menu();
    }

    if (sdBuf == "+")
      / increase volume
      {
        myDFPlayer.volumeUp();
        debugMess("Current volume: ");
        debugMessln(myDFPlayer.readVolume());
        options_menu();
      }

    if (sdBuf == "-") // decrease volume
    {
      myDFPlayer.volumeDown();
      debugMess("Current volume: ");
      debugMessln(myDFPlayer.readVolume());
      options_menu();
    }
  } // while
} // loop

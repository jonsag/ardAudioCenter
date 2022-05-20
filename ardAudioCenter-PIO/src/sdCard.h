// the recommended library for the DFPlayer Mini is at https://github.com/Arduinolibrary/DFRobot_Mini_Player
// but I use the one at https://github.com/DFRobot/DFRobotDFPlayerMini

// Code on this page originates from https://www.instructables.com/id/MP3-Player-With-Arduino/

void menu_opcoes()
{
  debugMessln();
  debugMessln("Comandos:");
  debugMess(" [1-");
  debugMess(maxSDSongs);
  debugMessln("] Para selecionar o arquivo MP3");
  debugMessln(" [s] parar reproducao");
  debugMessln(" [p] pausa/continua a musica");
  debugMessln(" [e] seleciona equalizacao");
  debugMessln(" [+ or -] aumenta ou diminui o volume");
  debugMessln();
}

void playSDCard()
{
  // Aguarda a entrada de dados pela serial
  while (Serial.available() > 0)
  {
    // recupera os dados de entrada
    sdBuf = Serial.readStringUntil('\n');
    // Reproducao (índice da música)
    if ((sdBuf.toInt() >= 1) && (sdBuf.toInt() <= maxSDSongs))
    {
      debugMess("Reproduzindo musica: ");
      debugMessln(sdBuf.toInt());
      myDFPlayer.play(sdBuf.toInt()); // dá play na música
      menu_opcoes();
    }
    // Pausa/Continua a musica
    if (sdBuf == "p")
    {
      if (sdPause)
      {
        debugMessln("Continua musica...");
        myDFPlayer.start();
      }
      else
      {
        debugMessln("Musica pausada...");
        myDFPlayer.pause();
      }
      sdPause = !sdPause;

      menu_opcoes();
    }

    // Parada
    if (sdBuf == "s")
    {
      myDFPlayer.stop();
      debugMessln("Musica parada!");
      menu_opcoes();
    }

    // Seleciona equalizacao
    if (sdBuf == "e")
    {
      sdEqualizer++;
      if (sdEqualizer == 6)
      {
        sdEqualizer = 0;
      }
      myDFPlayer.EQ(sdEqualizer);
      debugMess("Equalizacao: ");
      debugMess(sdEqualizer);
      debugMessln(" (0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass)");
      menu_opcoes();
    }

    // Aumenta volume
    if (sdBuf == "+")
    {
      myDFPlayer.volumeUp();
      debugMess("Volume atual:");
      debugMessln(myDFPlayer.readVolume());
      menu_opcoes();
    }
    // Diminui volume
    if (sdBuf == "-")
    {
      myDFPlayer.volumeDown();
      debugMess("Volume atual:");
      debugMessln(myDFPlayer.readVolume());
      menu_opcoes();
    }
  } // while
} // loop

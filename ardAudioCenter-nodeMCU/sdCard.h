// the recommended library for the DFPlayer Mini is at https://github.com/Arduinolibrary/DFRobot_Mini_Player
// but I use the one at https://github.com/DFRobot/DFRobotDFPlayerMini

// Code on this page originates from https://www.instructables.com/id/MP3-Player-With-Arduino/

void menu_opcoes() {
  Serial.println();
  Serial.println("Comandos:");
  Serial.print(" [1-");
  Serial.print(maxSDSongs);
  Serial.println("] Para selecionar o arquivo MP3");
  Serial.println(" [s] parar reproducao");
  Serial.println(" [p] pausa/continua a musica");
  Serial.println(" [e] seleciona equalizacao");
  Serial.println(" [+ or -] aumenta ou diminui o volume");
  Serial.println();
}

void playSDCard() {
  //Aguarda a entrada de dados pela serial
  while (Serial.available() > 0)
  {
    //recupera os dados de entrada
    sdBuf = Serial.readStringUntil('\n');
    //Reproducao (índice da música)
    if ((sdBuf.toInt() >= 1) && (sdBuf.toInt() <= maxSDSongs))
    {
      Serial.print("Reproduzindo musica: ");
      Serial.println(sdBuf.toInt());
      myDFPlayer.play(sdBuf.toInt()); // dá play na música
      menu_opcoes();
    }
    //Pausa/Continua a musica
    if (sdBuf == "p")
    {
      if (sdPause)
      {
        Serial.println("Continua musica...");
        myDFPlayer.start();
      }
      else
      {
        Serial.println("Musica pausada...");
        myDFPlayer.pause();
      }
      sdPause = !sdPause;

      menu_opcoes();
    }

    //Parada
    if (sdBuf == "s")
    {
      myDFPlayer.stop();
      Serial.println("Musica parada!");
      menu_opcoes();
    }

    //Seleciona equalizacao
    if (sdBuf == "e")
    {
      sdEqualizer++;
      if (sdEqualizer == 6)
      {
        sdEqualizer = 0;
      }
      myDFPlayer.EQ(sdEqualizer);
      Serial.print("Equalizacao: ");
      Serial.print(sdEqualizer);
      Serial.println(" (0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass)");
      menu_opcoes();
    }

    //Aumenta volume
    if (sdBuf == "+")
    {
      myDFPlayer.volumeUp();
      Serial.print("Volume atual:");
      Serial.println(myDFPlayer.readVolume());
      menu_opcoes();
    }
    //Diminui volume
    if (sdBuf == "-")
    {
      myDFPlayer.volumeDown();
      Serial.print("Volume atual:");
      Serial.println(myDFPlayer.readVolume());
      menu_opcoes();
    }
  } //while
} //loop

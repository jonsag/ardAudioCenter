/*******************************
  Prints selected source on top line
*******************************/
void printSource() {
  lcd.setCursor(0, 0);
  lcd.print(sources[sourceNo]);
  for (int i = 0; i <= lcdColumns - 1 - sources[sourceNo].length(); i++) { // fill up line whith spaces
    lcd.setCursor(sources[sourceNo].length() + i, 0);
    lcd.print(" ");
  }
}

/*******************************
  Prints volume level on the second line
*******************************/
void printVolume() {
  lcd.setCursor(4, 1);
  lcd.print(volume);

  if (volume < 10) { // volume has one character
    lcd.setCursor(5, 1);
    lcd.print("%");
    for (int i = 6; i <= lcdColumns - 8; i++) { // fill up line whith spaces
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  } else if (volume < 100) { // volume has three characters
    lcd.setCursor(6, 1);
    lcd.print("%");
    for (int i = 7; i <= lcdColumns - 8; i++) { // fill up line whith spaces
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  } else { // volume has two characters
    lcd.setCursor(7, 1);
    lcd.print("%");
    for (int i = 8; i <= lcdColumns - 8; i++) { // fill up line whith spaces
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  }

  for (int i = 0; i <= 6; i++) { // draw volume bar
    lcd.setCursor(i + 9, 1);

    if (volume * 35 / 100 >= i * 5 + 1 && volume * 35 / 100 <= (i + 1) * 5) { // volume is somewhere in this char

      switch (volume * 35 / 100 - i * 5) { // which segment should be drawn
        case 1:
          lcd.write(byte(1)); //print our custom char
          break;
        case 2:
          lcd.write(byte(2)); //print our custom char
          break;
        case 3:
          lcd.write(byte(3)); //print our custom char
          break;
        case 4:
          lcd.write(byte(4)); //print our custom char
          break;
        case 5:
          lcd.write(byte(5)); //print our custom char
          break;
      }
    } else {
      lcd.print("-");
    }
  }
}

/*******************************
  Prints the selection choice on the second line
*******************************/
void printSourceSelect() {
  lcd.setCursor(4, 1);
  lcd.print(selectSourceNo);

  lcd.setCursor(5, 1);
  lcd.print(" ");

  lcd.setCursor(6, 1);
  lcd.print(sources[selectSourceNo]);

  for (int i = 6 + sources[selectSourceNo].length(); i <= lcdColumns - 1; i++) { // fill up line whith spaces
    lcd.setCursor(i, 1);
    lcd.print(" ");
  }
}

/*******************************
  Prints balance value on the second line
*******************************/
void printBalance() {
  lcd.setCursor(4, 1);
  if (balance - 10 < 0) {
    lcd.print(balance - 10);
  } else if (balance - 10 > 0) {
    lcd.print("+");
    lcd.setCursor(5, 1);
    lcd.print(balance - 10);
  } else {
    lcd.print(balance - 10);
    lcd.setCursor(5, 1);
    lcd.print("  ");
  }

  if (balance != 0 && balance != 20) {
    lcd.setCursor(6, 1);
    lcd.print(" ");
  }

  for (int i = 7; i <= lcdColumns - 1; i++) { // fill up line whith spaces
    lcd.setCursor(i, 1);
    lcd.print(" ");
  }
}

/*******************************
  Prints the function ('Vol', 'Src', 'Bal' etc) on the second line
*******************************/
void printFunction() {
  lcd.setCursor(0, 1);
  lcd.print(functions[functionNo]);
  /*
    if (functionNo == 0) {
    lcd.print("Vol");
    } else if (functionNo == 1) {
    lcd.print("Src");
    } else if (functionNo == 2) {
    lcd.print("Bal");
    } else {
    lcd.print("Err");
    }
  */

  lcd.setCursor(3, 1); // print space
  lcd.print(" ");

  if (functionNo == 0) { // volume
    printVolume();
  } else if (functionNo == 1) { // function
    printSourceSelect();
  } else if (functionNo == 2) { // balance
    printBalance();
  }
}

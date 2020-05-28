void printSource() {
  lcd.setCursor(0, 0);
  lcd.print(sources[sourceNo]);
  for (int i = 0; i <= lcdColumns - 1 - sources[sourceNo].length(); i++) {
    lcd.setCursor(sources[sourceNo].length() + i, 0);
    lcd.print(" ");
  }
}

void printVolume() {
  lcd.setCursor(4, 1);
  lcd.print(volume);
  if (volume < 10) {
    lcd.setCursor(5, 1);
    lcd.print("%");
    for (int i = 6; i <= lcdColumns - 1; i++) {
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  } else if (volume < 100) {
    lcd.setCursor(6, 1);
    lcd.print("%");
    for (int i = 7; i <= lcdColumns - 1; i++) {
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  } else {
    lcd.setCursor(7, 1);
    lcd.print("%");
    for (int i = 8; i <= lcdColumns - 1; i++) {
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  }
}

void printSourceSelect() {
  lcd.setCursor(4, 1);
  lcd.print(sourceNo);

  lcd.setCursor(5, 1);
  lcd.print(" ");

  lcd.setCursor(6, 1);
  lcd.print(sources[sourceNo]);
}

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

  lcd.setCursor(3, 1);
  lcd.print(" ");

  if (functionNo == 0) {
    printVolume();
  } else if (functionNo == 1) {
    printSourceSelect();
  }
}

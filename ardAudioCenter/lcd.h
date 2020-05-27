void printSource() {
  lcd.setCursor(0, 0);
  lcd.print(sources[sourceNo]);
  for (int i = 0; i <= lcdColumns - 1 - sources[sourceNo].length(); i++) {
    lcd.setCursor(sources[sourceNo].length() + i, 0);
    lcd.print(" ");
  }

  oldSourceNo = sourceNo;
}

void printVolume() {
  lcd.setCursor(4, 1);
  lcd.print(volume);
  lcd.setCursor(6, 1);
  lcd.print("%");
  if (volume < 10) {
    for (int i = 6; i <= lcdColumns - 1; i++) {
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  } else if (volume < 100) {
    for (int i = 7; i <= lcdColumns - 1; i++) {
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  } else {
    for (int i = 8; i <= lcdColumns - 1; i++) {
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }
  }
}

void printFunction() {
  lcd.setCursor(0, 1);
  lcd.print(functions[functionNo]);
  lcd.setCursor(3, 1);
  lcd.print(" ");
  
  if (functions[functionNo] == "Vol") {
    printVolume();
  } else {
    lcd.setCursor(0, 1);
    lcd.print(functions[functionNo]);
  }

  oldFunctionNo = functionNo;
}

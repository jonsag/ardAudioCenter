String programName = "ardAudioCenter";
String date = "20200526";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/*******************************
  LCD setup
*******************************/
const byte lcdColumns = 16;
const byte lcdRows = 2;

//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); // set the LCD address to 0x27 for a 16 chars and 2 line display

/*******************************
  FTDebouncer setup
*******************************/
const byte debounceTime = 15;

#if !defined(nullptr)
#define nullptr NULL
#endif

#include "FTDebouncer.h" // load library for debouncing buttons
FTDebouncer pinDebouncer(debounceTime);

/*******************************
  Sources
*******************************/
byte sourceNo = 0;
String sources[] = {"FM Radio", "Bluetooth", "Aux"};

byte oldSourceNo = sourceNo;

/*******************************
  Functions
*******************************/
byte functionNo = 0;
String functions[] = {"Vol", "Src", "Bal"};

byte oldFunctionNo = functionNo;

/*******************************
  Volume
*******************************/
byte volume = 25;
byte oldVolume = volume;

/*******************************
  Misc
*******************************/
//byte i;
//byte j;

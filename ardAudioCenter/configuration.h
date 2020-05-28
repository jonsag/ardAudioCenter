String programName = "ardAudioCenter";
String date = "20200526";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/*******************************
  LCD setup
*******************************/
//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte lcdColumns = 16;
const byte lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); // set the LCD address to 0x27 for a 16 chars and 2 line display

/*******************************
  Rotary encoders
*******************************/
#include <SimpleRotary.h>

SimpleRotary rotary1(2, 3, 4); // CLK, DT, SW (pin A, pin B, button pin)

//const byte debounceDelay = 5; // Set the debounce delay in ms  (Default: 2)
//const byte errorDelay = 250; // Set the error correction delay in ms  (Default: 200)

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

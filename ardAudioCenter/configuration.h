String programName = "ardAudioCenter";
String date = "20200526";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/*******************************
  Debug from serial
*******************************/
const boolean debug = HIGH;

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
String sources[] = {"FM Radio", "Bluetooth", "SD Card", "Line In"};

byte oldSourceNo = sourceNo;
byte selectSourceNo;

/*******************************
  Functions
*******************************/
byte functionNo = 0;
String functions[] = {"Vol", "Src", "Bal"};

byte oldFunctionNo = functionNo;

/*******************************
  Sound settings
*******************************/
byte volume = 25;
byte oldVolume = volume;

byte balance = 0;
byte oldBalance = balance;

/*******************************
  Times
*******************************/
unsigned long buttonMillis; // when was a button pressed/rotated

int screenWait = 2000; // how long to wait before returning to home screen

/*******************************
  Multiplexer
*******************************/
const int muxPins[2] = {14, 15}; // analog pins A0 and A1

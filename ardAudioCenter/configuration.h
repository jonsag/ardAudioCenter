String programName = "ardAudioCenter";
String date = "20200526";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/*******************************
  Debug from serial
*******************************/
const boolean debug = true;

/*******************************
  LCD setup
*******************************/
//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte lcdColumns = 16;
const byte lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); // set the LCD address to 0x27 for a 16 chars and 2 line display

#include "chars.h" // load custom characters

/*******************************
  Rotary encoders
*******************************/
#include <SimpleRotary.h>

SimpleRotary rotary1(2, 3, 4); // multi function button, CLK, DT, SW (pin A, pin B, button pin)
SimpleRotary rotary2(5, 6, 7); // radio button

//const byte debounceDelay = 5; // Set the debounce delay in ms  (Default: 2)
//const byte errorDelay = 250; // Set the error correction delay in ms  (Default: 200)

/*******************************
  Digital potentiometers, MCP41010
*******************************/
#include <SPI.h> // loads the SPI library

const int csPL = 16; // CS (chip select for MCP41010, digital potentiometer), left channel volume, 16 => A2
const int csPR = 17; // CS, right channel volume, 17 => A3

byte volL; // volume on left channel
byte volR; // volume on right channel

/*******************************
  FM radio module, TEA5767
*******************************/
#include <TEA5767.h>
//#include <Wire.h>

#define radioBand RADIO_BAND_FM // the band that will be tuned is FM

TEA5767 radio; // create an instance of class for Si4703 chip, pinout SDA and SCL, arduino uno pins A4 and A5

double frequency = 10030; // start frequency
double oldFrequency;

//const byte radioVolume = 2; // volume output from the module, commented out beacause TEA5767 doesn't seem to have this option

const int radioDebugInterval = 3000; // how often to print radio debug messages

int search_mode = 0;
int search_direction;

unsigned long last_pressed;
unsigned char buf[5];

int stereo;
int signal_level;

double currentFrequency;

unsigned long currentMillis = millis();

int inByte;
int flag=0;

RADIO_FREQ preset[] = { // some radio presets
  9000, // SR P1
  9870, // SR P3
  10230, // SR P4 Sörmland
  10030 // SR P4 Gotland
};

/*******************************
  SD card module, DFPlayer Mini
*******************************/
#include <SoftwareSerial.h> // this library adds RX and TX to other pins than 0 and 1
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 9); // RX, TX, on the DFPlayer 10 connnects to TX and 9 to RX

DFRobotDFPlayerMini myDFPlayer; // define player

String sdBuf; // takes the characters sent over serial

boolean sdPause = false;
byte sdEqualizer = 0; // (0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass)
byte maxSDSongs = 0;

byte mySoftwareSerialTimeOut = 500;

const byte sdVolume = 10;

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
byte volumeVal;

byte balance = 10;
byte oldBalance = balance;

/*******************************
  Times
*******************************/
unsigned long buttonMillis; // when was a button pressed/rotated

const int screenWait = 2000; // how long to wait before returning to home screen

/*******************************
  Multiplexer
*******************************/
const int muxPins[2] = {14, 15}; // analog pins A0 and A1

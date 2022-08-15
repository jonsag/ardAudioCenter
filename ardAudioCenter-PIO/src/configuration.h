#define programName "ardAudioCenter"
#define date "20220815"
#define author "Jon Sagebrand"
#define email "jonsagebrand@gmail.com"

/*******************************
  Enable DFPlayer
*******************************/
#define DFPLAYER 0 // set to 1 to enable DFPlayer

/*******************************
  Serial
*******************************/
#define serialSpeed 9600

#define bootDelay 100 // delay after each boot message

/*******************************
  Debugging
*******************************/
#define DEBUG 0 // debugMess is off when 0
#define INFO 1

#if DEBUG
#define debugMess(x) Serial.print(x)
#define debugMessln(x) Serial.println(x)
#else
#define debugMess(x)
#define debugMessln(x)
#endif

#if INFO || DEBUG
#define infoMess(x) Serial.print(x)
#define infoMessln(x) Serial.println(x)
#else
#define infoMess(x)
#define infoMessln(x)
#endif

/*******************************
  Wire I2C setup
*******************************/
#include <Wire.h>

// arduino: SDA -> A4, SCL -> A5
// nodemcu: SDA -> D2, SCL -> D1
//#define SDApin A4
//#define SCLpin A5

/*******************************
  FM radio module, TEA5767
*******************************/
#define useRDS 0

#include <radio.h>
#include <TEA5767.h>

#if useRDS
#include <RDSParser.h>
#endif

#define radioBand RADIO_BAND_FM // the band that will be tuned is FM

RADIO_FREQ preset[] = {
    // some radio presets
    9000,  // SR P1, Sörmland
    9480,  // SR P4 Östergötland
    9740,  // RIX FM, Nyköping
    9870,  // SR P3, Sörmland
    10020, // SR P4 Gotland
    10230, // SR P4 Sörmland
    10030, // SR P4 Gotland
    10300, // Star FM, Nyköping
    10330  // SR P4 Stockholm
};

#define FIX_BAND RADIO_BAND_FM

byte presetNo = 5;

double frequency = preset[presetNo]; // start frequency
double oldFrequency = frequency;

#define minFrequency 8750
#define maxFrequency 10800

#define frequencyStep 10

boolean presetScreen = false;
boolean presetActive = false;

// const byte radioVolume = 15; // volume output from the module, commented out because TEA5767 doesn't seem to have this option

// int search_mode = 0;
// int search_direction;

// unsigned long last_pressed;
// unsigned char buf[5];

// int stereo;
// int signal_level;

// int inByte;
// int flag = 0;

/*******************************
  LCD setup
*******************************/
#include <LiquidCrystal_I2C.h>

#define lcdColumns 16
#define lcdRows 2

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); // set the LCD address to 0x27 for a 16 chars and 2 line display

#include "chars.h" // load custom characters

/*******************************
  Rotary encoders
*******************************/
#include <SimpleRotary.h>

SimpleRotary rotary1(2, 3, 4); // multi function button, CLK, DT, SW (pin A, pin B, button pin)
SimpleRotary rotary2(5, 6, 7); // radio button

#define debounceDelay 2 // set the debounce delay in ms, default 2
#define errorDelay 200  // set the error correction delay in ms, default 200

byte rotate1;
byte push1;

byte rotate2;
byte push2;

/*******************************
  Digital potentiometers, MCP41010
*******************************/
#include <SPI.h> // loads the SPI library

#define csPL 16 // CS (chip select for MCP41010, digital potentiometer), left channel volume, 16 => A2
#define csPR 17 // CS, right channel volume, 17 => A3

byte volL; // volume on left channel
byte volR; // volume on right channel

/*******************************
  Bluetooth module, JDY-62
*******************************/
#define btMute 8 // pin connected to mute input on JDY-62, muted when HIGH
#define btOn 12  // pin connected to MOSFET, powering the module when HIGH

/*******************************
  SD card module, DFPlayer Mini
*******************************/
#if DFPLAYER
#include <SoftwareSerial.h> // this library adds RX and TX to other pins than 0 and 1
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 9); // RX, TX, on the DFPlayer 10 connects to TX and 9 to RX

DFRobotDFPlayerMini myDFPlayer; // define player

#define DFPlayerSerialTimeOut 500
#define DFPlayerVolume 10 // volume value (0~30)

#define DFPlayerEQ DFPLAYER_EQ_NORMAL // set different EQ
/*
DFPLAYER_EQ_NORMAL
DFPLAYER_EQ_POP
DFPLAYER_EQ_ROCK
DFPLAYER_EQ_JAZZ
DFPLAYER_EQ_CLASSIC
DFPLAYER_EQ_BASS
*/

#define DFPlayerDevice DFPLAYER_DEVICE_SD // set device we use SD as default
/*
DFPLAYER_DEVICE_U_DISK
DFPLAYER_DEVICE_SD
DFPLAYER_DEVICE_AUX
DFPLAYER_DEVICE_SLEEP
DFPLAYER_DEVICE_FLASH
*/

boolean DFPlayerPause = false; // DFPlayer is paused

int trackNo; // track number selected
int oldTrackNo;

/*
String sdBuf; // takes the characters sent over serial
boolean sdPause = false;
byte sdEqualizer = 0; // (0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass)
byte maxSDSongs = 0;
*/
#endif

/*******************************
  Sources
*******************************/
byte sourceNo = 0;

#if DFPLAYER
const String sources[] = {"FM Radio", "Bluetooth", "Line In", "SD Card"};
const String sourcesShort[] = {"FM", "Bt", "Li", "SD"};
#else
const String sources[] = {"FM Radio", "Bluetooth", "Line In"};
const String sourcesShort[] = {"FM", "Bt", "Li"};
#endif

byte oldSourceNo = sourceNo;
byte selectSourceNo = 0;

/*******************************
  Functions
*******************************/
byte functionNo = 0;
String functions[] = {"Vol", "Src", "Bal"};

byte oldFunctionNo = functionNo;

/*******************************
  Sound settings
*******************************/
#define volumeStep 1
#define balanceStep 1

byte volume = 10; // start volume

byte oldVolume = volume;
byte volumeVal;

byte balance = 10;
byte oldBalance = balance;

/*******************************
  Times
*******************************/
unsigned long currentMillis = millis();

unsigned long button1Millis; // when was a button pressed/rotated
unsigned long button2Millis; // when was a button pressed/rotated

#define screenWait 2000 // how long to wait before returning to home screen

/*******************************
  Multiplexer
*******************************/
#define muxPin0 14 // analog pin 14 => A0
#define muxPin1 15 // analog pin 15 => A1

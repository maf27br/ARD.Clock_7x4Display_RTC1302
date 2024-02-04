#include <SevSeg.h>
#include <virtuabotixRTC.h>

SevSeg sevseg;
//pinagen RTC
#define ENA 16
#define CLK 14
#define DAT 15
//inicializa DS1302
virtuabotixRTC myRTC(CLK, DAT, ENA);

void setup() {
  //inicia serial
  Serial.begin(9600);
  //Configura display
  byte numDigits = 4;
  byte digitPins[] = { 10, 12, 11, 4 };
  byte segmentPins[] = { 8, 13, 3, 6, 7, 9, 2, 5 };
  bool resistorsOnSegments = false;
  bool updateWithDelaysIn = false;
  byte hardwareConfig = COMMON_CATHODE;
  bool leadingZeros = true;  // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelaysIn, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
}

void loop() {
  myRTC.updateTime();
  sevseg.setNumber((myRTC.hours*100)+myRTC.minutes, myRTC.seconds%2-1);
  sevseg.refreshDisplay();
}
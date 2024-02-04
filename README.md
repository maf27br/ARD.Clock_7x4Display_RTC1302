# Projeto Relógio Digital
Projeto que usa display de 7 segmentos e 4 digitos em conjunto com RTC 1302.
Utilizando a biblioteca SevSeg.

Dica: o ponto marcando a passagem dos segundos foi um truque usando em conjunto com a função SetNumber, o ponto de marcação decimal, alternando de acordo com "seconds % 2".

Diagrama:

![image](https://github.com/maf27br/ARD.Clock_7x4Display_RTC1302/assets/68168344/8ca0349a-f887-416a-9c01-73ebbd9f47c1)

Foi adicionado o RTC 1302 nos pinos 14(A0), 15(A1) e 16(A2), juntamente com GND e VCC(5v).

Montagem:

![20240204_103500](https://github.com/maf27br/ARD.Clock_7x4Display_RTC1302/assets/68168344/60a7b30d-63c7-4dfd-bd66-dfac06839a4c)

Código:

```
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
```

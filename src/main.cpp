#include <Arduino.h>
/*
  Würfel mit 5 Augen
  mit Zufall und Statistik
  Lösung der Übungsaufgabe

  Version 1.0
  Der Hobbyelektroniker
  Der Code ist Public Domain und kann ohne Einschränkungen frei verwendet werden
*/

// Anordnung der LED's
/*
 * 1     2
 *    0
 * 4     3
 */

// void blink(int, int, int, bool);
const int anzahl_augen = 5;
const int ledPin[anzahl_augen] = {2, 3, 4, 5, 6};
const int tasterPin = 7;
const int ledInterval = 1000;
const int blinkTime = 100;
unsigned long curtime = 0;
int resettimer = 0;

void blink(int led, int blTime, int durTime, bool ledReset) {
  static int ledTime[anzahl_augen] = {0};
  static unsigned long startzeit[anzahl_augen] = {0};
  static unsigned long startDurzeit[anzahl_augen] = {0};
  ledTime[led] = durTime;
  if (ledReset) {
    digitalWrite(ledPin[led], 0);
    ledTime[led] = 0;
    startzeit[led] = 0;
    startDurzeit[led] = 0;
  } else if (startDurzeit[led] == 0) {
    startDurzeit[led] = curtime;
  } else if (curtime - startDurzeit[led] > ledTime[led] && ledTime[led] > 0) {
    digitalWrite(ledPin[led], HIGH);
  } else if ((curtime - startzeit[led]) > blTime) {
    digitalWrite(ledPin[led], !digitalRead(ledPin[led]));
    startzeit[led] = curtime;
  }
}

void taster() {
  if (!digitalRead(tasterPin)) {
    resettimer = 1;
    delay(100);
  }
}

void start() {
  static unsigned long starttimer = curtime;
  int i = 0;
  blink(0, 500, 0, 0);
  for (i = 0; i < anzahl_augen; i++) {
    if (curtime - starttimer > ledInterval * i)
      blink(i + 1, blinkTime, ledInterval, 0);
  }
  if (curtime - starttimer > ledInterval * (anzahl_augen - 1) || resettimer) {
    resettimer = 0;
    starttimer = curtime;
    for (int j = 0; j < anzahl_augen; j++) {
      blink(j, 0, 0, 1);
    }
  }
}

void setup() {
  Serial.begin(57600);
  for (int i = 0; i < anzahl_augen; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(tasterPin, INPUT_PULLUP);
}

void loop() {
  curtime = millis();
  taster();
  start();
}

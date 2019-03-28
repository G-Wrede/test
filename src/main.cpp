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
 * 0     1
 *    4
 * 2     3
 */

// void blink(int, int, int, bool);
const int anzahl_augen = 6;
const int ledPin[anzahl_augen] = {2, 3, 4, 5, 6, 8};
const int tasterPin = 7;
unsigned long curtime = 0;

void blink(int led, int blTime, int durTime, bool ledOFF) {
  static int ledTime[anzahl_augen] = {0};
  static unsigned long startzeit[anzahl_augen] = {0};
  static unsigned long startDurzeit[anzahl_augen] = {0};
  ledTime[led] = durTime;
  if (ledOFF) {
    digitalWrite(ledPin[led], 0);
    ledTime[led] = 0;
    startzeit[led] = 0;
    startDurzeit[led] = 0;
  } else if (startDurzeit[led] == 0) {
    startDurzeit[led] = curtime;
  } else if (curtime - startDurzeit[led] > ledTime[led]) {
    digitalWrite(ledPin[led], HIGH);
  } else if ((curtime - startzeit[led]) > blTime) {
    digitalWrite(ledPin[led], !digitalRead(ledPin[led]));
    startzeit[led] = curtime;
  }
}

void taster() {
  if (!digitalRead(tasterPin)) {
    digitalWrite(ledPin[0], HIGH);
    for (int i = 1; i < anzahl_augen; i++) {
      blink(i, 0, 0, 1);
    }
  } else {
    digitalWrite(ledPin[0], LOW);
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
  blink(2, 200, 5000, 0);
  blink(3, 200, 8000, 0);
  blink(4, 900, 10000, 0);
  blink(1, 1500, 15000, 0);
  blink(5, 100, 3000, 0);
}

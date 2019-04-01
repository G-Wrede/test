#include <Arduino.h>
/*
  Würfel mit 5 Augen
*/

// Anordnung der LED's
/*
 * 1     2
 *    0
 * 4     3
 */

const int anzahl_augen = 5;
<<<<<<< HEAD
const int ledPin[anzahl_augen] = {2, 3, 4, 5, 6}; // Arduino Pins
const int tasterPin = 7;        // Eingang fuer den Taster
const int ledInterval = 15000;  // wechselintervall zum naechsten Led in ms
const int blinkTime = 100;      // Blinkintervall der Leds
unsigned long tic = 0;         // speichert die Zeit seit dem Start in ms
bool resettimer = 0;            // Wenn gesetzt dann wird der Ausgang zurueck gesetzt
/*
Parameter:
  led     = Led Nummer
  blTime  = blinkdauer in ms
  durTime = dauer des blinkens danach bleibt das Led an
  ledReset= wenn 1 dann wird der Ausgang zurueck gesetzt
 */
=======
const int ledPin[anzahl_augen] = {2, 3, 4, 5, 6};
const int tasterPin = 7;
const int ledInterval = 1000;
const int blinkTime = 100;
unsigned long curtime = 0;
int resettimer = 0;

>>>>>>> 57c6805bcf8249c044cc1b246a7c7790350cac92
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
    startDurzeit[led] = tic;
  } else if (tic - startDurzeit[led] > ledTime[led] && ledTime[led] > 0) {
    digitalWrite(ledPin[led], HIGH);
  } else if ((tic - startzeit[led]) > blTime) {
    digitalWrite(ledPin[led], !digitalRead(ledPin[led]));
    startzeit[led] = tic;
  }
}

void taster() {
  if (!digitalRead(tasterPin)) {
    resettimer = 1;     // setzen des Reset auf HIGH
    delay(100);         // entcoppeln
  }
}

void start() {
  static unsigned long starttimer = tic;
  int i = 0;
  blink(0, 500, 0, 0);
  for (i = 0; i < anzahl_augen; i++) {
<<<<<<< HEAD
    if (tic - starttimer > ledInterval * i)
      blink(i + 1, blinkTime, ledInterval, 0);
  }
  if (tic - starttimer >= ledInterval * (anzahl_augen - 1) || resettimer) {
    Serial.print(starttimer > ledInterval * (anzahl_augen - 1));
=======
    if (curtime - starttimer > ledInterval * i)
      blink(i + 1, blinkTime, ledInterval, 0);
  }
  if (curtime - starttimer > ledInterval * (anzahl_augen - 1) || resettimer) {
>>>>>>> 57c6805bcf8249c044cc1b246a7c7790350cac92
    resettimer = 0;
    starttimer = tic;
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
  tic = millis();
  taster();
  start();
}

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

const int anzahl_leds = 5;
const int ledPin[anzahl_leds] = {2, 3, 4, 5, 6}; // Arduino Pins
const int tasterPin = 7;                         // Eingang fuer den Taster

const int aus = 0;
const int ein = 1;
const int blinken = 2;

// aktuelle Zustaende
int ledStatus[anzahl_leds];
String statusText[] = {"aus", "ein", "blinken"};

unsigned long startZeit;
unsigned long tic;

void start() {
  // Serial.println("S Hallo");
  ledStatus[0] = blinken; // led 0 blinkt immer
  for (int i = 1; i < anzahl_leds; i++)
    ledStatus[i] = aus; // alle Anderen aus
  startZeit = millis();
}

void setup() {
  Serial.begin(57600);
  for (int i = 0; i < anzahl_leds; i++)
    pinMode(ledPin[i], OUTPUT); // Pinmode setzen
  pinMode(tasterPin, INPUT_PULLUP);
  while (digitalRead(tasterPin))
    ;
  start();
}

void checkStart() {
  // Serial.println("Hallo");
  if (!digitalRead(tasterPin))
    // Serial.println("Start");
    start(); // neustart
}

void checkZustand() {
  static int sekundeAlt = 0;
  int sekunde = (tic - startZeit) / 1000; // Sekunden seit dem start
  sekunde = sekunde % 60;                 // 0 bis 59
  if (sekunde != sekundeAlt) {
    Serial.println();
    Serial.print("Sekunde ");
    Serial.println(sekunde);
    sekundeAlt = sekunde;
    if (sekunde < 15) {
      ledStatus[1] = blinken;
      ledStatus[2] = aus;
      ledStatus[3] = aus;
      ledStatus[4] = aus;
    } else if (sekunde >=15 && sekunde < 30) {
      ledStatus[1] = ein;
      ledStatus[2] = blinken;
      ledStatus[3] = aus;
      ledStatus[4] = aus;
    } else if (sekunde >=30 && sekunde < 45) {
      ledStatus[1] = ein;
      ledStatus[2] = ein;
      ledStatus[3] = blinken;
      ledStatus[4] = aus;
    } else if (sekunde >=45) {
      ledStatus[1] = ein;
      ledStatus[2] = ein;
      ledStatus[3] = ein;
      ledStatus[4] = blinken;
    }
    for (int ledNummer=1; ledNummer<anzahl_leds; ledNummer++) {
      Serial.print(ledNummer); Serial.print(" = ");
      Serial.print(statusText [ledStatus[ledNummer]]); Serial.print("; ");
    }
    Serial.println();
  }
}
void schalteLeds() {
  const int ledNummer = 0;
  const int blikStartZeit = 500;
  static unsigned long startZeit = 0;
  static bool hell = true;

  if (tic > startZeit + blikStartZeit) {
    hell = !hell;
    startZeit = tic;
    for (int i = 0; i < anzahl_leds; i++) {
      // if(ledStatus[i] == 0) {
      //   digitalWrite(ledPin[i], LOW);
      // } else if (ledStatus[i] == 2) {
      //   digitalWrite(ledPin[i], hell);
      // } else if (ledStatus[i] == 1) {
      //   digitalWrite(ledPin[i], HIGH);
      // }
      switch (ledStatus[i]) {
        case aus: digitalWrite(ledPin[i], LOW);
        break;
        case ein: digitalWrite(ledPin[i], HIGH);
        break;
        case blinken: digitalWrite(ledPin[i], hell);
      }
    }

  }
}

void loop() {
  checkStart();
  tic = millis(); // Der Zeittakt in Millisekunden
  checkZustand();
  schalteLeds();
}

/*
  Turtle Robot
  Motor Steuerungen

  Version 1.00, 29.05.2019
  Gerhard Wrede
*/

#define VERS 100;

#include "globals.h"
#include "motor.h"
#include <Arduino.h>

//=== Konstanten
//Pindefinitionen
const int links_richtung_Pin = 2;
const int links_geschwindigkeit_Pin = 9;
const int rechts_richtung_Pin = 4;
const int rechts_geschwindigkeit_Pin = 5;

// vor, zurück und Drehung (dürfen nicht geändert werden)
const int vor = 1;
const int zurueck = -1;
const int drehung_rechts = 2;
const int drehung_links = -2;

//== lokale Variablen
// Aktuelle Werte
int richtung = vor;
int kurve = 0;
int geschwindigkeit = 0;

//=== Interne Funktionen
//////////////////////////////////////////////////////////////////////////////////
// Richtung: vorwärts: vor (1), zurueck: zurueck (-1),
//           Drehung rechts: drehung_rechts (2), Drehung links: drehung_links (-2)
//           nichts ändern: motor_unveraendert (9999),
// Kurve:    Kurve rechts: > 0, Kurve links: < 0, Keine Kurve: kurve_keine (0)
//           Kurve unverändert: motor_unveraendert (9999)
//           Gültiger Bereich: motor_kurve_min .. motor_kurve_max (-3 .. +3)
//           Kleine Werte entsprechen einer schwachen Kurve
// Geschwindigkeit: Stopp: 0, nicht ändern: motor_unveraendert (9999)
//                  gültige Geschwindigkeiten: 1 .. 255
//////////////////////////////////////////////////////////////////////////////////
void steuerung(int neueRichtung, int neueKurve, int neueGeschwindigkeit) {

  // Neue aktuelle Werte
  if (neueRichtung != motor_unveraendert) richtung = neueRichtung;
  if (neueKurve != motor_unveraendert) {
    kurve = neueKurve;
    // Drehung beenden, falls eine Kurve definiert ist
    if (richtung == drehung_rechts || richtung == drehung_links)
      if (kurve != motor_kurve_keine) richtung = vor;
  }
  if (neueGeschwindigkeit != motor_unveraendert) geschwindigkeit = neueGeschwindigkeit;
  if (neueRichtung != motor_unveraendert && geschwindigkeit == 0) {
    geschwindigkeit = motor_mittel;
  }

  // Motor entsprechend den aktuellen Werten ansprechen
  switch (richtung) {
    case vor:
      digitalWrite(links_richtung_Pin, HIGH); // vor
      digitalWrite(rechts_richtung_Pin, HIGH); // vor
      break;
    case zurueck:
      digitalWrite(links_richtung_Pin, LOW); // zurück
      digitalWrite(rechts_richtung_Pin, LOW); // zurück
      break;
    case drehung_rechts:
      digitalWrite(links_richtung_Pin, HIGH); // vor
      digitalWrite(rechts_richtung_Pin, LOW); // zurueck
      kurve = motor_kurve_keine; // Keine Kurve bei Drehung
      break;
    case drehung_links:
      digitalWrite(links_richtung_Pin, LOW); // zurueck
      digitalWrite(rechts_richtung_Pin, HIGH); // vor
      kurve = motor_kurve_keine; // Keine Kurve bei Drehung
      break;
  }

  // Kurvenwerte testen
  if (kurve < motor_kurve_min) kurve = motor_kurve_min;
  if (kurve > motor_kurve_max) kurve = motor_kurve_max;

  Serial.println(geschwindigkeit);
  if (kurve == motor_kurve_keine) { // Keine Kurve
    analogWrite(links_geschwindigkeit_Pin, geschwindigkeit);
    analogWrite(rechts_geschwindigkeit_Pin, geschwindigkeit);
  } else if (kurve > 0) { // Rechtskurve
    analogWrite(links_geschwindigkeit_Pin, geschwindigkeit);
    analogWrite(rechts_geschwindigkeit_Pin, geschwindigkeit/(kurve+1));
  } else { // Linkskurve
    analogWrite(links_geschwindigkeit_Pin, geschwindigkeit/-(kurve-1));
    analogWrite(rechts_geschwindigkeit_Pin, geschwindigkeit);
  }
}

//=== Oeffentliche Funktionen
void motor_geschwindigkeit(int neueGeschwindigkeit) {
  steuerung(motor_unveraendert,motor_unveraendert,neueGeschwindigkeit);
}

void motor_schneller(int schritt) {
  geschwindigkeit += schritt;
  if (geschwindigkeit > 255) geschwindigkeit = 255;
  motor_geschwindigkeit(geschwindigkeit);
}

void motor_langsamer(int schritt) {
  geschwindigkeit -= schritt;
  if (geschwindigkeit < 0) geschwindigkeit = 0;
  motor_geschwindigkeit(geschwindigkeit);
}

void motor_stopp() {
  motor_geschwindigkeit(0);
}

void motor_vor() {
  steuerung(vor,motor_kurve_keine,motor_unveraendert);
}

void motor_zurueck() {
  steuerung(zurueck,motor_kurve_keine,motor_unveraendert);
}

void motor_drehen_rechts() {
  steuerung(drehung_rechts,motor_kurve_keine,motor_unveraendert);
}

void motor_drehen_links() {
  steuerung(drehung_links,motor_kurve_keine,motor_unveraendert);
}

void motor_kurve(int wert) {
  steuerung(motor_unveraendert,wert, motor_unveraendert);
}

void motor_kurve_rechts() {
  kurve++;
  if (kurve > motor_kurve_max) kurve = motor_kurve_max;
  motor_kurve(kurve);
}

void motor_kurve_links() {
  kurve--;
  if (kurve < motor_kurve_min) kurve = motor_kurve_min;
  motor_kurve(kurve);
}

void motor_init() {
  pinMode(links_richtung_Pin,OUTPUT);
  pinMode(rechts_richtung_Pin,OUTPUT);
  motor_stopp();
}

int motor_version() {
  return VERS;
}

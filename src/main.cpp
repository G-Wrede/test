#include <Arduino.h>
/*
  Turtle Robot
  Fahren mit Fernbedienung

  Version 1.0
  Der Hobbyelektroniker
  Der Code ist Public Domain und kann ohne Einschränkungen frei verwendet werden
*/
#include <IRremote.h>

// Infrarotempfänger
const int remote_Pin = A0;
IRrecv irEmpf(remote_Pin); // Empfängerobjekt erzeugen und Pin A0 zuweisen
decode_results irResults;  // Variable für den Empfang der Kommandos

const long cmd_vor = 0x00FF629D;
const long cmd_zurueck = 0x00FFA857;
const long cmd_links = 0x00FF22DD;
const long cmd_rechts = 0x00FFC23D;
const long cmd_stopp = 0x00FF02FD;

const long cmd_langsam = 0x00FF6897; // 1
const long cmd_mittel = 0x00FF9867;  // 2
const long cmd_schnell = 0x00FFB04F; // 3

// Motoren
const int motor_links_richtung_Pin = 2;
const int motor_links_geschwindigkeit_Pin = 9;
const int motor_rechts_richtung_Pin = 4;
const int motor_rechts_geschwindigkeit_Pin = 5;

const int geschwindigkeit_langsam = 120;
const int geschwindigkeit_mittel = 190;
const int geschwindigkeit_schnell = 255;

int geschwindigkeit; // aktuelle Geschwindigkeit

void set_geschwindigkeit(int neueGeschwindigkeit) {
  geschwindigkeit = neueGeschwindigkeit;
  analogWrite(motor_links_geschwindigkeit_Pin, geschwindigkeit);
  analogWrite(motor_rechts_geschwindigkeit_Pin, geschwindigkeit);
}

void stopp() {
  set_geschwindigkeit(0);
}

void vor() {
  if (geschwindigkeit == 0) geschwindigkeit = geschwindigkeit_mittel;
  digitalWrite(motor_rechts_richtung_Pin, HIGH); // beide vor
  digitalWrite(motor_links_richtung_Pin, HIGH);
  analogWrite(motor_links_geschwindigkeit_Pin, geschwindigkeit);
  analogWrite(motor_rechts_geschwindigkeit_Pin, geschwindigkeit);
}

void zurueck() {
  if (geschwindigkeit == 0) geschwindigkeit = geschwindigkeit_mittel;
  digitalWrite(motor_rechts_richtung_Pin, LOW); // beide zurück
  digitalWrite(motor_links_richtung_Pin, LOW);
  analogWrite(motor_links_geschwindigkeit_Pin, geschwindigkeit);
  analogWrite(motor_rechts_geschwindigkeit_Pin, geschwindigkeit);
}

void rechts() {
  if (geschwindigkeit == 0) geschwindigkeit = geschwindigkeit_mittel;
  digitalWrite(motor_rechts_richtung_Pin, LOW); // zurück
  digitalWrite(motor_links_richtung_Pin, HIGH); // vor
  analogWrite(motor_links_geschwindigkeit_Pin, geschwindigkeit);
  analogWrite(motor_rechts_geschwindigkeit_Pin, geschwindigkeit);
}

void links() {
  if (geschwindigkeit == 0) geschwindigkeit = geschwindigkeit_mittel;
  digitalWrite(motor_rechts_richtung_Pin, HIGH); // vor
  digitalWrite(motor_links_richtung_Pin, LOW); // zurück
  analogWrite(motor_links_geschwindigkeit_Pin, geschwindigkeit);
  analogWrite(motor_rechts_geschwindigkeit_Pin, geschwindigkeit);
}

void setup() {
  irEmpf.enableIRIn(); // Empfänger einschalten

  // Die digitalen Ausgänge benötigen pinMode(), die PWM-Ausgänge nicht
  pinMode(motor_links_richtung_Pin,OUTPUT);
  pinMode(motor_rechts_richtung_Pin,OUTPUT);
  stopp();  // sicherstellen, dass der Roboter nicht gleich losfährt
}



void checkCommands() {
  if (irEmpf.decode(&irResults)) { // Falls etwas empfangen wurde
    switch (irResults.value) {
      case cmd_vor: vor(); break;
      case cmd_zurueck: zurueck(); break;
      case cmd_rechts: rechts(); break;
      case cmd_links: links(); break;
      case cmd_stopp: stopp(); break;
      case cmd_langsam: set_geschwindigkeit(geschwindigkeit_langsam); break;
      case cmd_mittel: set_geschwindigkeit(geschwindigkeit_mittel); break;
      case cmd_schnell: set_geschwindigkeit(geschwindigkeit_schnell); break;
    }
    irEmpf.resume();
  }
}

void loop() {
  checkCommands();
}

/*
  Turtle Robot
  Infrared Fernbedienung

  Version 1.00, 29.05.2019
  Gerhard Wrede
*/

#define VERS 100

#include <arduino.h>
#include "globals.h"
#include "remote.h"
#include <IRremote.h>

//=== Konstanten
// Pindefinitionen
const int ir_Pin = A0;

// Codes vom Infrarot - Sender
const long taste_vor = 0x00FF629D;
const long taste_zurueck = 0x00FFA857;
const long taste_links = 0x00FF22DD;
const long taste_rechts = 0x00FFC23D;
const long taste_ok = 0x00FF02FD;

const long taste_1 = 0x00FF6897;
const long taste_2 = 0x00FF9867;
const long taste_3 = 0x00FFB04F;
const long taste_4 = 0x00FF30CF;
const long taste_5 = 0x00FF18E7;
const long taste_6 = 0x00FF7A85;
const long taste_7 = 0x00FF10EF;
const long taste_8 = 0x00FF38C7;
const long taste_9 = 0x00FF5AA5;
const long taste_0 = 0x00FF4AB5;
const long taste_stern = 0x00FF42BD;
const long taste_raute = 0x00FF52AD;

//=== Lokale Variablen
// Variable für den Empfang der Kommandos
decode_results results;

// Infrarotempfänger
IRrecv irEmpf(ir_Pin); // Empfängerobjekt erzeugen und Pin A0 zuweisen

//=== Oeffentliche Funktionen
int remote_command() {
  int result = cmd_kein;
  if (irEmpf.decode(&results)) { // Falls etwas empfangen wurde
    switch (results.value) {
      // case taste_vor: result = cmd_vor; break;
      case taste_vor: result = cmd_zurueck; break;
      // case taste_zurueck: result = cmd_zurueck; break;
      case taste_zurueck: result = cmd_vor; break;
      //case taste_rechts: result = cmd_drehen_rechts; break;
      case taste_rechts: result = cmd_kurve_rechts; break;
      //case taste_links: result = cmd_drehen_links; break;
      case taste_links: result = cmd_kurve_links; break;
      case taste_ok: result = cmd_stopp; break;
      case taste_1: result = cmd_langsam; break;
      case taste_2: result = cmd_mittel; break;
      case taste_3: result = cmd_schnell; break;
      case taste_4: result = cmd_kurve_links; break;
      case taste_6: result = cmd_kurve_rechts; break;
      case taste_7: result = cmd_langsamer; break;
      case taste_9: result = cmd_schneller; break;

      case taste_5: result = cmd_user1; break;
      case taste_8: result = cmd_user2; break;
      case taste_stern: result = cmd_user3; break;
      case taste_0: result = cmd_user4; break;
      case taste_raute: result = cmd_user5; break;
    }
    irEmpf.resume();
  }
  return result;
}

void remote_init() {
  irEmpf.enableIRIn(); // Empfänger einschalten
}

int remote_version() {
  return VERS;
}

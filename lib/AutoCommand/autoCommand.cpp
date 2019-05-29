/*
  Turtle Robot
  Automatische Kommandolisten
  Version 1.00, 05.05.2019
  Der Hobbyelektroniker
  https://community.hobbyelektroniker.ch
  https://www.youtube.com/c/HobbyelektronikerCh
  Der Code kann mit Quellenangabe frei verwendet werden.
*/

#define VERS 100

#include <arduino.h>
#include "globals.h"
#include "autoCommand.h"

// Record zur Speicherung eines Kommandos
struct command {
  int cmd;
  int wert;
  int zeit;
};

// private Variablen
int anzahl = 0;         // aktuelle Anzahl Kommandos in der Liste
int pos = 0;            // das nächste auszuführende Kommandoposition
boolean aktiv = false;
int wert;
unsigned long startZeit = 0; // Timing
long zeit = 0;

struct command commands[autoCommand_maxAnzahl]; // Die Liste

// Oeffentliche Funktionen
void autoCommand_newCommandList() {
  anzahl = 0; // Liste ist leer
  pos = 0;
  aktiv = false; // nicht aktiv
}

// Befehl und Zeit in ms hinzufügen
void autoCommand_addCommand(int cmd, int zeit, int wert) {
  if (anzahl == autoCommand_maxAnzahl) return;
  commands[anzahl].cmd = cmd;
  commands[anzahl].zeit = zeit;
  commands[anzahl].wert = wert;
  anzahl++;
}

void autoCommand_startList() {
  pos = 0;
  aktiv = true;
}

void autoCommand_stoppList() {
  aktiv = false;
}

int autoCommand_nextCommand() {
  if (!aktiv) return cmd_kein;
  if (millis() > startZeit+zeit) { // Die Zeit ist abgelaufen
    if (pos == anzahl) { // Alles erledigt
      autoCommand_stoppList();
      return cmd_stopp;
    }
    startZeit = millis();
    zeit = commands[pos].zeit;
    wert = commands[pos].wert;
    pos++;
    return commands[pos-1].cmd;
  }
}

int autoCommand_getWert() {
  return wert;
}

void autoCommand_init() {
  autoCommand_newCommandList();
}

int autoCommand_version() {
  return VERS;
}

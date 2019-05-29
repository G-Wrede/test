/*
  Turtle Robot
  Automatische Kommandolisten
  Version 1.00, 05.05.2019
  Der Hobbyelektroniker
  https://community.hobbyelektroniker.ch
  https://www.youtube.com/c/HobbyelektronikerCh
  Der Code kann mit Quellenangabe frei verwendet werden.
*/

//=== Konstanten
const int autoCommand_maxAnzahl = 50; // maximale Anzahl in Liste

//=== Funktionen
void autoCommand_newCommandList(); // Neue Liste vorbereiten

// Kommando der Liste hinzufügen, Zeit in ms
void autoCommand_addCommand(int cmd, int zeit, int wert = 0);

void autoCommand_startList();     // Liste zur Ausführung bereitmachen
void autoCommand_stoppList();     // Ausführung der Liste stoppen
int autoCommand_nextCommand();    // Nächstes Kommando in Liste
int autoCommand_getWert();        // Parameter des letzten Kommandos

void autoCommand_init();          // Initialisierung des Moduls
int autoCommand_version();        // Version (100 --> Vers. 1.00)

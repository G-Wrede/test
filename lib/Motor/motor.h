/*
  Turtle Robot
  Motor Steuerungen

  Version 1.00, 29.05.2019
  Gerhard Wrede
*/

//=== Konstanten
// Geschwindigkeiten
const int motor_langsam = 80;
const int motor_mittel = 190;
const int motor_schnell = 255;
const int motor_unveraendert = 9999;

// Erlaubte Werte für Kurven
// von kurve_min (-3) bis kurve_max (3)
// 0 entspricht keiner Kurve
const int motor_kurve_max = 3;
const int motor_kurve_min = -3;
const int motor_kurve_keine = 0;

//=== Funktionen
void motor_geschwindigkeit(int neueGeschwindigkeit);
void motor_schneller(int schritt = 30);
void motor_langsamer(int schritt = 30);
void motor_stopp();
void motor_vor();
void motor_zurueck();
void motor_drehen_rechts();
void motor_drehen_links();
void motor_kurve(int wert);
void motor_kurve_rechts();
void motor_kurve_links();
void motor_gerade();
int motor_getGeschwindigkeit();

void motor_init();
int motor_version();

// int motor_command();
// void motor_init();
// int motor_version();

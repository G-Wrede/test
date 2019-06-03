/*
Turtle Robot
Motor Steuerungen

Version 1.00, 03.06.2019
Gerhard Wrede

 */
 #define VERS 100

 #include <arduino.h>
 #include "globals.h"
 #include "augen.h"

 // NewPing kann hier nicht verwendet werden wegen Konflikt mit IRremote
 // Die Version mit PulseIn ist nicht besonders genau, genügt aber hier

 const int trigger_Pin = 12;
 const int echo_Pin = 13;

 float augen_cmAbstand() {
   // Triggersignal senden
   digitalWrite(trigger_Pin,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigger_Pin,LOW);

   // Echo auswerten
   float cm = pulseIn(echo_Pin, HIGH, 30000) / 58.00; // Timeout 50 ms
   if (!cm) cm = 1000.00;
   return cm;
 }

 void augen_init() {
   pinMode(trigger_Pin,OUTPUT);
   digitalWrite(trigger_Pin,LOW);
 }

 int augen_version() {
   return VERS;
 }

#include <Arduino.h>
/*
  Der Hobbyelektroniker
  Der einfache Einstieg in Arduino & Co - 11
 */
Test des Zufallsgenerators sofort * /

    const int tasterPin = 7;

int statistik[] = {0, 0, 0, 0, 0, 0}; // Array initialisiert mit 0

int wuerfeln() {
  randomSeed(analogRead(1));
  int result = random(1, 6);
  return result;
}

int check(int anzahl) {
  for (int i = 0; i < anzahl; i++) {
    int zahl = random(1, 6);
    statistik[zahl]++;
  }

  Serial.print("Anzahl Wuerfe: ");
  Serial.println(anzahl);

  for (int i = 1; i < 6; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(statistik[i]);
    Serial.print(" / ");
    Serial.print(100.00 / anzahl * statistik[i]);
    Serial.println(" %");
    statistik[i] = 0; // reset to 0
  }
  Serial.println("");
}

void setup() {
  Serial.begin(9600);
  pinMode(tasterPin, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(tasterPin)) {
    check(10);
    check(100);
    check(1000);
    check(10000);
    delay(300);
  }
}

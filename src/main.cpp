#include <Arduino.h>
/*
  Turtle Robot
  Fahren mit Fernbedienung

  Version 1.0
  Der Hobbyelektroniker
  Der Code ist Public Domain und kann ohne Einschränkungen frei verwendet werden
*/
#include <Augen.h>
#include <AutoCommand.h>
#include <Globals.h>
#include <Motor.h>
#include <Remote.h>

void ausfuehren(int cmd, int wert = 0) {
  switch (cmd) {
  case cmd_vor:
    motor_vor();
    break;
  case cmd_zurueck:
    motor_zurueck();
    break;
  case cmd_drehen_rechts:
    motor_drehen_rechts();
    break;
  case cmd_drehen_links:
    motor_drehen_links();
    break;
  case cmd_kurve_rechts:
    motor_kurve_rechts();
    break;
  case cmd_kurve_links:
    motor_kurve_links();
    break;
  case cmd_kurve:
    motor_kurve(wert);
    break;
  case cmd_stopp:
    motor_stopp();
    break;
  case cmd_langsam:
    motor_geschwindigkeit(motor_langsam);
    break;
  case cmd_mittel:
    motor_geschwindigkeit(motor_mittel);
    break;
  case cmd_schnell:
    motor_geschwindigkeit(motor_schnell);
    break;
  case cmd_schneller:
    motor_schneller();
    break;
  case cmd_langsamer:
    motor_langsamer();
    break;
  case cmd_gerade:
    motor_gerade();
    break;
  }
}

void setup() {
  Serial.begin(57600);
  remote_init();
  motor_init();
  autoCommand_init();
  augen_init();

  randomSeed(analogRead(0));

  // Befehlsliste füllen
  autoCommand_newCommandList(); // mit leerer Liste beginnen
  autoCommand_addCommand(cmd_vor, 1000);
  autoCommand_addCommand(cmd_kurve, 1000, 2);  // rechts
  autoCommand_addCommand(cmd_kurve, 1000, -2); // links
  autoCommand_addCommand(cmd_drehen_rechts, 1000);
  autoCommand_addCommand(cmd_drehen_links, 1000);
  autoCommand_addCommand(cmd_kurve, 1000, 1);  // rechts
  autoCommand_addCommand(cmd_kurve, 1000, -1); // rechts
}

void ausweichen() {
  int richtung = random(2);
  while (augen_cmAbstand() < 15) {
    if (richtung == 0) motor_drehen_rechts(); else motor_drehen_links();
    delay(100);
  }
  motor_gerade();
  motor_vor();
}

void loop() {
  if (augen_cmAbstand() < 10 && motor_getGeschwindigkeit() != 0) ausweichen();
  int cmd = remote_command();
  switch (cmd) {
    case cmd_user2: autoCommand_startList(); // Taste 0
                    ausfuehren(cmd_stopp);
                    break;
    case cmd_stopp: autoCommand_stoppList();
                    ausfuehren(cmd);
                    break;
    case cmd_kein:  cmd = autoCommand_nextCommand();
                    ausfuehren(cmd,autoCommand_getWert());
                    break;
    default:        ausfuehren(cmd);
  }
}

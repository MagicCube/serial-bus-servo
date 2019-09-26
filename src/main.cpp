#include <Arduino.h>

#include "ZX01Servo.h"
#include "ZX01ServoBus.h"

ZX01ServoBus bus(&Serial1);
ZX01Servo *servo;

void setup() {
  // Setup Serial1.
  // Since we use half-duplex UART, set both RX and TX pin to 5.
  Serial1.begin(115200, SERIAL_8N1, 5, 5);

  servo = bus.registerServo(1);
  bus.begin();
}

void loop() {
  bus.sendCommand(1, "2500T100");
  delay(500);
  bus.sendCommand(1, "500T100");
  delay(500);
}

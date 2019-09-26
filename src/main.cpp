#include <Arduino.h>

#include "ZX01Servo.h"
#include "ZX01ServoBus.h"

#define SERIAL_PIN 5
ZX01ServoBus bus(&Serial1);
ZX01Servo *servo;

void setup() {
  Serial.begin(115200);

  // Setup Serial1.
  // Since we use half-duplex UART, set both RX and TX pin to 5.
  Serial1.begin(115200, SERIAL_8N1, SERIAL_PIN, SERIAL_PIN);
  pinMode(SERIAL_PIN, OUTPUT | PULLUP | OPEN_DRAIN);

  // createServo
  servo = bus.createServo(1, ZX01ServoMode::COUNTERCLOCKWISE_270);

  bus.begin();
}

void loop() {
  servo->rotateTo(0);
  delay(5000);
  servo->rotateTo(270 / 2);
  delay(5000);
  servo->rotateTo(270);
  delay(5000);
}

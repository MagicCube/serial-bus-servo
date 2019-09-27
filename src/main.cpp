#include <Arduino.h>

#include <ZX01.h>

#define MAX_DEGREE 270
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
#if MAX_DEGREE == 180
  servo = bus.createServo(1, ZX01ServoMode::CLOCKWISE_180, -MAX_DEGREE / 2);
#else
  servo = bus.createServo(1, ZX01ServoMode::CLOCKWISE_270, -MAX_DEGREE / 2);
#endif

  bus.begin();

  servo->setAutoInitPosition(true);
  // servo->setCentralPosition();

  servo->factoryReset();

  // servo->rotateTo(0, 1000);
}

void loop() {
  delay(3000);
  servo->rotateTo(0);
}

#include "ZX01Servo.h"

#include "ZX01ServoBus.h"

ZX01Servo::ZX01Servo(ZX01ServoBus *bus, uint8_t id, ZX01ServoMode mode) {
  _bus = bus;
  _id = id;
  _mode = mode;
}

void ZX01Servo::begin() {
  _bus->sendCommand(_id, "MOD1");
}

int16_t ZX01Servo::rotation() {
  return 0;
}

void ZX01Servo::rotation(int16_t degree) {
  rotateTo(degree);
}

void ZX01Servo::rotateTo(int16_t degree, uint16_t duration) {
  _bus->sendCommand(_id, "", false);
}

uint16_t ZX01Servo::_convertDegreeToPosition(int16_t degree) {
  return 0;
}

int16_t ZX01Servo::_convertPositionToDegree(uint16_t position) {
  return 0;
}
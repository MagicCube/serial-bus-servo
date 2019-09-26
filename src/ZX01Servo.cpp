#include "ZX01Servo.h"

#include "ZX01ServoBus.h"

ZX01Servo::ZX01Servo(ZX01ServoBus *bus, uint8_t id, ZX01ServoMode mode) {
  _bus = bus;
  _id = id;
  _mode = mode;
  _scale.outputRange(500, 2500);
  switch (_mode) {
  case ZX01ServoMode::CLOCKWISE_270:
  case ZX01ServoMode::COUNTERCLOCKWISE_270:
    _scale.inputDomain(0, 270);
    break;
  case ZX01ServoMode::CLOCKWISE_180:
  case ZX01ServoMode::COUNTERCLOCKWISE_180:
    _scale.inputDomain(0, 180);
    break;
  }
}

void ZX01Servo::begin() {
  char command[5];
  sprintf(command, "MOD%d", (uint8_t)_mode);
  _bus->sendCommand(_id, command);
}

int16_t ZX01Servo::rotation() {
  auto res = _bus->sendCommand(_id, "RAD");
  char prefix[6];
  sprintf(prefix, "#%03dP", _id);
  if (res.startsWith(prefix)) {
    auto degree = res.substring(5).toInt();
    return _scale.invert(degree);
  }
  return 0;
}

void ZX01Servo::rotation(int16_t degree) {
  rotateTo(degree);
}

void ZX01Servo::rotateTo(int16_t degree, uint16_t duration) {
  char command[16];
  sprintf(command, "%dT%d", _scale.convert(degree), duration);
  _bus->sendCommand(_id, command, false);
}

void ZX01Servo::setInitialRotation() {
  _bus->sendCommand(_id, "CSD");
}

void ZX01Servo::loadTorque() {
  _bus->sendCommand(_id, "ULR");
}

void ZX01Servo::unloadTorque() {
  _bus->sendCommand(_id, "ULK");
}

void ZX01Servo::factoryReset() {
  _bus->sendCommand(_id, "CLE");
}

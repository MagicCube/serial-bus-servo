#include "ZX01Servo.h"

#include "ZX01ServoBus.h"

ZX01Servo::ZX01Servo(ZX01ServoBus *bus, uint8_t id, ZX01ServoMode mode, int16_t offsetDegree) {
  _bus = bus;
  _id = id;
  _mode = mode;
  _scale.outputRange(500, 2500);
  switch (_mode) {
  case ZX01ServoMode::CLOCKWISE_270:
  case ZX01ServoMode::COUNTERCLOCKWISE_270:
    _scale.inputDomain(0 + offsetDegree, 270 + offsetDegree);
    break;
  case ZX01ServoMode::CLOCKWISE_180:
  case ZX01ServoMode::COUNTERCLOCKWISE_180:
    _scale.inputDomain(0 + offsetDegree, 180 + offsetDegree);
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
  auto pos = _scale.convert(degree);
  sprintf(command, "%dT%d", pos, duration);
  _bus->sendCommand(_id, command, false);
}

void ZX01Servo::pauseRotating() {
  _bus->sendCommand(_id, "DPT");
}

void ZX01Servo::stopRotating() {
  _bus->sendCommand(_id, "DST");
}

void ZX01Servo::continueRotating() {
  _bus->sendCommand(_id, "DCT");
}

void ZX01Servo::setInitPosition() {
  _bus->sendCommand(_id, "CSD");
}

void ZX01Servo::setCentralPosition() {
  _bus->sendCommand(_id, "SCK");
}

void ZX01Servo::setAutoInitPosition(bool allow) {
  if (allow) {
    _bus->sendCommand(_id, "CSR");
  } else {
    _bus->sendCommand(_id, "CSM");
  }
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

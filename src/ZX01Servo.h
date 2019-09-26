#pragma once

#include <Arduino.h>

#include "LinearScale.h"

class ZX01ServoBus;

enum class ZX01ServoMode {
  COUNTERCLOCKWISE_270 = 1,
  CLOCKWISE_270 = 2,
  COUNTERCLOCKWISE_180 = 3,
  CLOCKWISE_180 = 4
};

// A class represents ZX01 serial servo.
class ZX01Servo {
public:
  // Creates a new instance of `ZX01Servo`.
  ZX01Servo(ZX01ServoBus *bus, uint8_t id, ZX01ServoMode mode = ZX01ServoMode::CLOCKWISE_270);

  // Gets the rotation in degrees.
  int16_t rotation();

  // Sets the rotation in degrees.
  // Same as `rotateTo()`.
  void rotation(int16_t degree);

  // Initializes the servo.
  // This method will be automatically called by servo bus.
  void begin();

  // Rotates to specific degree.
  void rotateTo(int16_t degree, uint16_t duration = 10);

  // Set current roation as initial value.
  void setInitialRotation();

  void loadTorque();

  void unloadTorque();

  void factoryReset();

private:
  uint8_t _id;
  ZX01ServoMode _mode;
  LinearScale _scale;
  ZX01ServoBus *_bus;
};

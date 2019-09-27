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
  ZX01Servo(ZX01ServoBus *bus, uint8_t id, ZX01ServoMode mode = ZX01ServoMode::CLOCKWISE_270,
            int16_t offsetDegree = 0);

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

  // Stops the current movement immediately.
  void stopRotating();

  // Pauses the current movement.
  void pauseRotating();

  // Continues paused movement.
  void continueRotating();

  // Recovers torque.
  void loadTorque();

  // Releases torque, so you can manually rotate the servo.
  void unloadTorque();

  // Sets current roation as initial position.
  void setInitPosition();

  // Sets current roation as central point.
  void setCentralPosition();

  // Sets whether it allows to automatically rotate to the initial position after powered.
  void setAutoInitPosition(bool allow);

  // Resets everything including ID.
  void factoryReset();

private:
  uint8_t _id;
  ZX01ServoMode _mode;
  LinearScale _scale;
  ZX01ServoBus *_bus;
};

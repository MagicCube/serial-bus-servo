#pragma once

#include <Arduino.h>
#include <stdlib.h>

#include "ZX01Servo.h"

// A class represents a serial servo bus.
// A servo bus can link and control serveral servos simultaneously.
class ZX01ServoBus {
  friend class ZX01Servo;

public:
  // Creates a new instance of `ZX01ServoBus`.
  ZX01ServoBus(Stream *serial);

  // Initializes the servo bus.
  void begin();

  // Registers a servo with specific ID, and returns a new instance of ZX01Servo.
  ZX01Servo *registerServo(uint8_t id, ZX01ServoMode mode = ZX01ServoMode::COUNTERCLOCKWISE_270);

  // Sends a command to specific servo.
  // Sends to all servo when `servoId` equals to 255.
  String sendCommand(uint8_t servoId, const char *command, bool withResponse = true);

private:
  Stream *_serial;
  std::vector<ZX01Servo *> _servos;

  // Writes string to the serial port.
  void print(const char *string);

  // Writes integer to the serial port.
  void print(int number, int base = 10);

  // Reads a line from the serial port.
  String readLine();
};

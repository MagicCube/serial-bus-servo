#include "ZX01ServoBus.h"

#include "ZX01Servo.h"

ZX01ServoBus::ZX01ServoBus(Stream *serial) {
  _serial = serial;
}

void ZX01ServoBus::begin() {
  for (auto servo : _servos) {
    servo->begin();
  }
}

ZX01Servo *ZX01ServoBus::createServo(uint8_t id, ZX01ServoMode mode, int16_t offsetDegree) {
  auto servo = new ZX01Servo(this, id, mode, offsetDegree);
  _servos.push_back(servo);
  return servo;
}

void ZX01ServoBus::print(const char *str) {
  _serial->print(str);
}

void ZX01ServoBus::print(int number, int base) {
  _serial->print(number, base);
}

String ZX01ServoBus::readLine() {
  String result = _serial->readStringUntil('\n');
  if (result.endsWith("\r")) {
    result = result.substring(0, result.length() - 1);
  }
  return result;
}

String ZX01ServoBus::sendCommand(uint8_t servoId, const char *command, bool withResponse) {
  // Specify servo
  print("#");
  print(servoId);
  print("P");
  // Write command
  print(command);
  // End of command
  print("\r\n");
  // Read echo
  auto echo = readLine();
  Serial.print(">> ");
  Serial.println(echo);
  if (withResponse) {
    auto res = readLine();
    Serial.print(">> ");
    Serial.println(res);
    return res;
  }
  Serial.println();
  return "";
}

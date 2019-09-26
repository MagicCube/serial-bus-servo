#pragma once

#include <Arduino.h>

#include <math.h>

// A class represents a linear scale.
class LinearScale {
public:
  // Creates a new instance of `LinearScale`.
  LinearScale() {
  }

  // Sets range of input values.
  void inputDomain(int16_t from, int16_t to) {
    _inputDomain[0] = from;
    _inputDomain[1] = to;
    _update();
  }

  // Sets range of output values.
  void outputRange(int16_t from, int16_t to) {
    _outputRange[0] = from;
    _outputRange[1] = to;
    _update();
  }

  int16_t convert(int16_t value) {
    if (value <= _inputDomain[0]) {
      return _outputRange[0];
    } else if (value >= _inputDomain[1]) {
      return _outputRange[1];
    }
    return round(_outputRange[0] + (value - _inputDomain[0]) * _ratio);
  }

  int16_t invert(int16_t scaledValue) {
    if (scaledValue <= _outputRange[0]) {
      return _inputDomain[0];
    } else if (scaledValue >= _outputRange[1]) {
      return _inputDomain[1];
    }
    return round(_inputDomain[0] + (scaledValue - _outputRange[0]) * _invertRatio);
  }

private:
  int16_t _inputDomain[2] = {0, 0};
  int16_t _outputRange[2] = {0, 0};
  float _ratio = 0;
  float _invertRatio = 0;

  void _update() {
    if (_inputDomain[1] - _inputDomain[0] != 0) {
      _ratio = (float)(_outputRange[1] - _outputRange[0]) / (_inputDomain[1] - _inputDomain[0]);
    }
    if (_outputRange[1] - _outputRange[0] != 0) {
      _invertRatio =
          (float)(_inputDomain[1] - _inputDomain[0]) / (_outputRange[1] - _outputRange[0]);
    }
  }
};

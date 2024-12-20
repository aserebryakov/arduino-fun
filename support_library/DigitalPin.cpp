// MIT License
//
// Copyright (c) 2024 Alexander Serebryakov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "DigitalPin.h"

DigitalPin::DigitalPin(const int pin_number, HwApi& hw_api) : pin_number{pin_number}, hw_api{hw_api} {
}

PIN_CHANGE DigitalPin::getPinChange() const {
  if (previous_level == current_level) {
    return PIN_CHANGE::NONE;
  }

  if (previous_level == HwApi::LEVEL_HIGH && current_level == HwApi::LEVEL_LOW) {
    return PIN_CHANGE::HIGH_LOW;
  }

  return PIN_CHANGE::LOW_HIGH;
}

HwApi::DIGITAL_PIN_LEVEL DigitalPin::read() {
  previous_level = current_level;
  current_level = hw_api.digitalRead(pin_number) == HwApi::LEVEL_HIGH ? HwApi::LEVEL_HIGH : HwApi::LEVEL_LOW;
  return current_level;
}

HwApi::DIGITAL_PIN_LEVEL DigitalPin::getLevel() const {
  return current_level;
}
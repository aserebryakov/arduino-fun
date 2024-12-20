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

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "Callback.h"
#include "DigitalPin.h"
#include "HwApi.h"

/**
 * Implements rotary encoder functionality.
 */
class RotaryEncoder {
public:
   /**
    * Constructor.
    *
    * @param dt_pin DT pin number
    * @param clk_pin CLK pin number
    * @param sw_pin SW pin number
    * @param hwapi HwApi instance
    */
   RotaryEncoder(const int dt_pin, const int clk_pin, const int sw_pin, HwApi& hwapi);

    /**
     * Reads pins levels and calls callbacks.
     */
    void readPins();

    /**
     * Sets callback when encoder is rotated clockwise.
     *
     * Callback is called when DT pin changes from LOW to HIGH and CLK pin reads HIGH.
     *
     * @param callback
     */
    void setTurnClockwiseCallback(Callback&& callback);

    /**
     * Sets callback when encoder is rotated counterclockwise.
     *
     * Callback is called when DT pin changes from LOW to HIGH and CLK pin reads LOW.
     *
     * @param callback
     */
    void setTurnCounterClockwiseCallback(Callback&& callback);

    /**
     * Sets callback when switch is pushed.
     *
     * Callback is called when SW pin changes from HIGH to LOW.
     *
     * @param callback
     */
    void setPushButtonCallback(Callback&& callback);

private:
    void readRotation();

    DigitalPin dt_pin;
    DigitalPin clk_pin;
    DigitalPin sw_pin;
    Callback on_turn_clockwise{};
    Callback on_turn_counterclockwise{};
    Callback on_push_button{};
};

#endif //ROTARYENCODER_H

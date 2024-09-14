#include "HID-Project.h"
#include "Scheduler.h"
#include "RotaryEncoder.h"
#include "RotaryEncoderPinImpl.h"

const int DT_PIN = 2;
const int CLK_PIN = 3;
const int SW_PIN = 4;

void setup() {
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);

  Consumer.begin();
  Serial.begin(9600);
  Serial.println(42);
}

class Controller {
public:
  Controller() {
    encoder.setTurnClockwiseCallback({Controller::onTurnClockwise, nullptr});
    encoder.setTurnCounterClockwiseCallback({Controller::onTurnCounterClockwise, nullptr});
    encoder.setPushButtonCallback({Controller::onPushButton, nullptr});
  }

  static void onTurnClockwise(void*) {
    Consumer.write(MEDIA_VOL_UP);
  }

  static void onTurnCounterClockwise(void*) {
    Consumer.write(MEDIA_VOL_DOWN);
  }

  static void onPushButton(void*) {
    Consumer.write(MEDIA_VOL_MUTE);
  }

  void loop() {
    encoder.readStatus();
  }

private:
  RotaryEncoderPinImpl dt{DT_PIN};
  RotaryEncoderPinImpl clk{CLK_PIN};
  RotaryEncoderPinImpl sw{SW_PIN};
  RotaryEncoder encoder{dt, clk, sw};
};

Controller controller{};

void loop() {
  controller.loop();                                 
  // if (A.read_changed() == PIN_CHANGE::LOW_HIGH) {
  //   B.read_changed();
  //   if (B.get_state()) {
  //     Consumer.write(MEDIA_VOL_UP);
  //   } else {
  //     Consumer.write(MEDIA_VOL_DOWN);
  //   }
  // }

  // if (Switch.read_changed() == PIN_CHANGE::LOW_HIGH)
  // {
  //   Serial.println("Mute");
  //   Consumer.write(MEDIA_VOL_MUTE);
  // }
  delay(10);
}

#include <MultiButton.h>

MultiButton button1(6);
MultiButton button2(7);

void setup() {
  Serial.begin(9600);
  button1.single_press([]() { Serial.println("Button 1 Single Press Detected"); });
  button1.double_press([]() { Serial.println("Button 1 Double Press Detected"); });
  button1.long_press([]() { Serial.println("Button 1 Long Press Detected"); });
  button1.long_hold([]() { Serial.println("Button 1 Long Hold Detected"); });
  button1.hold_release([]() { Serial.println("Button 1 Released from Hold"); });
  button2.single_press([]() { Serial.println("Button 2 Single Press Detected"); });
  button2.double_press([]() { Serial.println("Button 2 Double Press Detected"); });
  button2.long_press([]() { Serial.println("Button 2 Long Press Detected"); });
  button2.long_hold([]() { Serial.println("Button 2 Long Hold Detected"); });
  button2.hold_release([]() { Serial.println("Button 2 Released from Hold"); });
}

void loop() {
  button1.update();
  button2.update();
}

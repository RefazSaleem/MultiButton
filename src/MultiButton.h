#ifndef MULTIBUTTON_H
#define MULTIBUTTON_H

#include <Arduino.h>
#include <functional>

class MultiButton {
public:
  using Callback = std::function<void()>;

  MultiButton(int pin, int idleState = HIGH, unsigned long singlePressTime = 200, unsigned long longPressTime = 1000);
  void update();
  void single_press(Callback callback) { singlePressCallback = callback; }
  void double_press(Callback callback) { doublePressCallback = callback; }
  void long_press(Callback callback) { longReleaseCallback = callback; }
  void long_hold(Callback callback) { longHoldCallback = callback; }
  void hold_release(Callback callback) { releaseFromHoldCallback = callback; }

private:
  enum class ButtonState : uint8_t { IDLE, SINGLE_PRESS, DOUBLE_PRESS, LONG_RELEASE, LONG_HOLD };
  const int pin, idleState;
  const unsigned long singlePressTime, longPressTime, debounceDelay = 50;
  volatile bool isPressed = false, isHeld = false;
  unsigned long pressedTime = 0, releasedTime = 0, pressDuration = 0, lastDebounceTime = 0;
  unsigned long lastSinglePressTime = 0, counterSetTime = 0;
  int lastButtonState, buttonState, pressCounter = 0;
  ButtonState currentState;
  Callback singlePressCallback, doublePressCallback, longReleaseCallback, longHoldCallback, releaseFromHoldCallback;
};

#endif

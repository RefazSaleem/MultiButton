#include "MultiButton.h"

MultiButton::MultiButton(int pin, int idleState, unsigned long singlePressTime, unsigned long longPressTime)
    : pin(pin), idleState(idleState), singlePressTime(singlePressTime), longPressTime(longPressTime),
      lastButtonState(idleState), buttonState(idleState), currentState(ButtonState::IDLE) {
  pinMode(pin, INPUT_PULLUP);
}

void MultiButton::update() {
  int reading = digitalRead(pin);
  if (reading != lastButtonState) lastDebounceTime = millis();
  if ((millis() - lastDebounceTime) > debounceDelay && reading != buttonState) {
    buttonState = reading;
    if (buttonState == !idleState && !isPressed) {
      isPressed = true;
      pressedTime = millis();
      currentState = ButtonState::IDLE;
    } else if (buttonState == idleState && isPressed) {
      isPressed = false;
      releasedTime = millis();
      pressDuration = releasedTime - pressedTime;
      if (pressDuration < singlePressTime) {
        unsigned long currentMillis = millis();
        if (currentMillis - lastSinglePressTime < 400) pressCounter++;
        else pressCounter = 1;
        lastSinglePressTime = currentMillis;
        counterSetTime = currentMillis;
        if (pressCounter == 2) {
          currentState = ButtonState::DOUBLE_PRESS;
          if (doublePressCallback) doublePressCallback();
        } else if (pressCounter > 2) {
          currentState = ButtonState::SINGLE_PRESS;
          if (singlePressCallback) singlePressCallback();
        }
      } else if (pressDuration < longPressTime) {
        currentState = ButtonState::LONG_RELEASE;
        if (longReleaseCallback) longReleaseCallback();
      }
    }
  }
  if (isPressed && (millis() - pressedTime > longPressTime) && currentState != ButtonState::LONG_HOLD) {
    currentState = ButtonState::LONG_HOLD;
    isHeld = true;
    if (longHoldCallback) longHoldCallback();
  }
  if (!isPressed && isHeld) {
    isHeld = false;
    currentState = ButtonState::IDLE;
    if (releaseFromHoldCallback) releaseFromHoldCallback();
  }
  if (millis() - counterSetTime > 400) {
     if (pressCounter == 1){
     currentState = ButtonState::SINGLE_PRESS;
     pressCounter = 0;
     if (singlePressCallback) singlePressCallback();
   } else pressCounter = 0;
  }
  lastButtonState = reading;
}
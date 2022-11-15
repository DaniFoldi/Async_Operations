/*
    External Restart of Async_Operations
    Button press used to start an asynchronous timeout (a non-blocking delay)
    Wire a momentary button switch, between a digital/GPIO pin and ground.
    Alternatives to an external button (these all used pin 0 (zero):
        Many ESP boards came with a button labelled as "flash|boot|load."
        Uno/Nano could have a lead attached to RX0, and another to GND,
            then when shorted briefly, would act as an emergency button.
    Once you have a button wired, set the variable 'buttonPin'
        esp32, esp8266, could use 0 (labelled GPIO0)
        uno, nano, could also use 0 (labelled RX0)
*/

#include <Async_Operations.h>

int buttonPin = 0;
long long steps[] = {5000};
int step_count = sizeof(steps)/sizeof(steps[0]);
Async_Operations handler(steps, step_count, 1);

void setup() {
  Serial.begin(115200);         Serial.println();
  handler.setLoopCallback(&resetWaiting);
  pinMode(buttonPin, INPUT_PULLUP);
  //  handler.start();            // not here; started by button press
  Serial.print(millis());  Serial.print(F(" Press button connected to pin "));
  Serial.println(buttonPin);  Serial.print(F("\tto start "));  Serial.print(steps[0]);
  Serial.println(" msec asynchronous (non-blocking) timeout.");  Serial.println();
}

void resetWaiting() {
  Serial.print(millis());
  Serial.println(F(" Async timed out; press button again to restart the timeout."));  Serial.println();
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    Serial.print(millis());
    Serial.println(F(" Button pressed; starting async timeout."));
    handler.restart();
    delay(300);                   // economical debounce
  }
  handler.update();
}

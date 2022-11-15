#include <Async_Operations.h>

long long steps[] = {1000};
int step_count = sizeof(steps)/sizeof(steps[0]);
Async_Operations delayed(steps, step_count, 1);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  delayed.setLoopCallback(&cb);
  delayed.start();
}

void cb() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  delayed.update();
}

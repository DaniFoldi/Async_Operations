#include <Async_Operations.h>

long long dt[] = {1000};
int step_count = sizeof(dt)/sizeof(dt[0]);
Async_Operations delayed(dt, step_count, 1);

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

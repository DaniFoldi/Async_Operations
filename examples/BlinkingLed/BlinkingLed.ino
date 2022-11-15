#include <Async_Operations.h>

long long steps[] = {900, 100};
int step_count = sizeof(steps)/sizeof(steps[0]);
Async_Operations blinker(steps, step_count, -1, LED_BUILTIN);

void setup() {
  blinker.start();
}

void loop() {
  blinker.update();
}

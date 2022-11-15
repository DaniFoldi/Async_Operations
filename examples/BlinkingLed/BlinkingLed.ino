#include <Async_Operations.h>

long long dt[] = {900, 100};
Async_Operations blinker(dt, 2, -1, LED_BUILTIN);

void setup() {
  blinker.start();
}

void loop() {
  blinker.update();
}

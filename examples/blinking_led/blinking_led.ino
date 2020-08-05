#import <Async_Operations.h>

long long dt = {500, 500};
Async_Operations blinker(dt, 2, -1, LED_BUILTIN);

void setup() {
    blinker.start();
}

void loop() {
    blinker.update();
}

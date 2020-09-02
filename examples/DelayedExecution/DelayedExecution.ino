#import <Async_Operations.h>

long long dt = {1000};
Async_Operations delayed(&dt, 1, 1);

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

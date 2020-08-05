#import <Async_Operations.h>

long long dt = {10000};
Async_Operations handler(dt, 1, 1);

bool waiting = false;
int buttonPin = 10;

void setup() {
    handler.setLoopCallback(&resetWaiting)
    pinMode(buttonPin, INPUT_PULLUP);
}

void resetWaiting() {
    waiting = false;
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {
        waiting = true;
        handler.restart();
    }
}

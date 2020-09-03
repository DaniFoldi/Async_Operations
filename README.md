# Async_Operations library for Arduino
##### Version 1.0.2

- **No dependencies**
- **All architectures**
- **Low memory usage**

This library eases the process of creating tasks that take a long time, but the Arduino needs to be able to compute other things as well. With just a couple lines of code, you can execute code after a predefined interval.

## Installation
Download this repository and install it through the Library Manager in Arduino (tutorial [here](https://www.arduino.cc/en/Guide/Libraries))
Then import it as usual with `#import <Async_Operations.h>`

## Basic usage

#### Delayed execution
```c++
#include <Async_Operations.h>

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
```

#### Blinking LED

```c++
#include <Async_Operations.h>

long long dt = {500, 500};
Async_Operations blinker(&dt, 2, -1, LED_BUILTIN);

void setup() {
  blinker.start();
}

void loop() {
  blinker.update();
}
```

#### Timeout handler

```c++
#include <Async_Operations.h>

long long dt = {10000};
Async_Operations handler(&dt, 1, 1);

bool waiting = false;
int buttonPin = 10;

void setup() {
  handler.setLoopCallback(&resetWaiting);
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
```

## Documentation

`Async_Operations(long long *steps, int stepCount, int repeat = 0, int pin = -1; bool initialState = true, bool endState = false);`

|Parameter|Default value|Description|
|-|-|-|
|`long long *steps`|*None*|An array containing the length of each step in the iteration in milliseconds|
|`int stepCount`|*None*|The length of the `steps` array|
|`int repeat`|`0`|Number of complete cycles before the operation is automatically stopped. Set to `1` for no repetition, `-1` for infinite iterations|
|`int pin`|`-1`|A pin to automatically pulse with each step in the loop. Set to negative to disable|
|`bool initialState`|`true`|The initial state of the pin|
|`bool endState`|`false`|The state the pin is left in after the operation stops

### Available methods

`.start()`
`.stop()`
`.restart()`
`.update()`
`.pause()` - not yet available
`.continue()` - not yet available
`.play()`
`.getRunning()`
`.getPaused()`
`.getState()`
`.setStateChangeCallback(*callback)`
`.deleteStateChangeCallback()`
`.setLoopCallback(*callback)`
`.deleteLoopCallback()`

## Notes


- `initialState` is only set when the operation is started, so if the cycle contains an odd number of steps, the state will flip with each operation. Add a `0` to the end to counteract this.

## Contributing

You are welcome to open Pull Requests, or contribute in any other way.

## Todo

- pause/continue support

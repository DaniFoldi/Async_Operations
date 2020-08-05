/*
 * Async_Operations.h library for running time-consuming tasks without blocking the main thread
 * Created by Dániel Földi (05. August 2020)
 */

#ifndef Async_Operations_Header
#define Async_Operations_Header

#include "Arduino.h"

class Async_Operations {
  public:
    Async_Operations(long long *steps, int stepCount);
    Async_Operations(long long *steps, int stepCount, int repeat);
    Async_Operations(long long *steps, int stepCount, int repeat, int pin);
    Async_Operations(long long *steps, int stepCount, int repeat, int pin, bool initialState);
    Async_Operations(long long *steps, int stepCount, int repeat, int pin, bool initialState, bool endState);
    void start();
    void restart();
    void stop();
    void pause();
    void play();
    bool getPaused();
    bool getRunning();
    int getRepeatCount();
    bool getState();
    void update();
    void setStateChangeCallback(void (*stateChangeCallback)(void));
    void deleteStateChangeCallback();
    void setLoopCallback(void (*loopCallback)(void));
    void deleteLoopCallback();
  private:
    long long *steps;
    int stepCount;
    int step;
    int pin;
    bool running;
    long long startTime;
    long long lastUpdate;
    long long remaining;
    bool state;
    bool initialState;
    bool endState;
    int repeat;
    int initialRepeat;
    void (*stateChangeCallback)(void);
    void (*loopCallback)(void);
};

#endif

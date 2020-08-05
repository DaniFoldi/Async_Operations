/*
 * Async_Operations.h library for running time-consuming tasks without blocking the main thread
 * Created by Dániel Földi (05. August 2020)
 */

#include "Async_Operations.h"

Async_Operations::Async_Operations(long long *steps, int stepCount) {
  this->steps = steps;
  this->stepCount = stepCount;
  this->initialRepeat = 0;
  this->pin = -1;
  if (this->pin >= 0) {
    pinMode(this->pin, OUTPUT);
  }
  this->initialState = true;
  this->endState = false;
  this->running = false;
  this->startTime = 0;
  this->lastUpdate = 0;
  this->stateChangeCallback = 0;
  this->loopCallback = 0;
}

Async_Operations::Async_Operations(long long *steps, int stepCount, int repeat) {
  this->steps = steps;
  this->stepCount = stepCount;
  this->initialRepeat = repeat;
  this->pin = -1;
  if (this->pin >= 0) {
    pinMode(this->pin, OUTPUT);
  }
  this->initialState = true;
  this->endState = false;
  this->running = false;
  this->startTime = 0;
  this->lastUpdate = 0;
  this->stateChangeCallback = 0;
  this->loopCallback = 0;
}

Async_Operations::Async_Operations(long long *steps, int stepCount, int repeat, int pin) {
  this->steps = steps;
  this->stepCount = stepCount;
  this->initialRepeat = repeat;
  this->pin = pin;
  if (this->pin >= 0) {
    pinMode(this->pin, OUTPUT);
  }
  this->initialState = true;
  this->endState = false;
  this->running = false;
  this->startTime = 0;
  this->lastUpdate = 0;
  this->stateChangeCallback = 0;
  this->loopCallback = 0;
}

Async_Operations::Async_Operations(long long *steps, int stepCount, int repeat, int pin, bool initialState) {
  this->steps = steps;
  this->stepCount = stepCount;
  this->initialRepeat = repeat;
  this->pin = pin;
  if (this->pin >= 0) {
    pinMode(this->pin, OUTPUT);
  }
  this->initialState = initialState;
  this->endState = false;
  this->running = false;
  this->startTime = 0;
  this->lastUpdate = 0;
  this->stateChangeCallback = 0;
  this->loopCallback = 0;
}

Async_Operations::Async_Operations(long long *steps, int stepCount, int repeat, int pin, bool initialState, bool endState) {
  this->steps = steps;
  this->stepCount = stepCount;
  this->initialRepeat = repeat;
  this->pin = pin;
  if (this->pin >= 0) {
    pinMode(this->pin, OUTPUT);
  }
  this->initialState = initialState;
  this->endState = endState;
  this->running = false;
  this->startTime = 0;
  this->lastUpdate = 0;
  this->stateChangeCallback = 0;
  this->loopCallback = 0;
}

void Async_Operations::start() {
  this->startTime = millis();
  if (this->pin >= 0) {
    digitalWrite(this->pin, this->state);
  }
  this->lastUpdate = this->startTime;
  this->step = 0;
  this->remaining = this->steps[this->step];
  this->running = true;
  this->state = this->initialState;
  this->repeat = this->initialRepeat;
}

void Async_Operations::stop() {
  this->running = false;
  this->step = 0;
  this->repeat = this->initialRepeat;
}

void Async_Operations::pause() {
  //this->running = false;
  //this->remaining = this->steps[this->step] - millis() + this->start_time;
}

void Async_Operations::play() {
  //this->running = true;
  //this->start_time = millis() - this->steps[this->step] + this->remaining;
}

void Async_Operations::restart() {
  this->stop();
  this->start();
}

bool Async_Operations::getPaused() {
  return !this->running;
}

bool Async_Operations::getRunning() {
  return this->running;
}

void Async_Operations::update() {
  if (!this->running) {
    return;
  }
  long long currentTime = millis();
  while (this->lastUpdate + this->remaining < currentTime) {
    this->step++;
    if (this->step >= this->stepCount) {
      this->step = 0;
      if (this->repeat > 0) {
        this->repeat--;
      }
      if (this->repeat == 0) {
        this->remaining = 0;
        this->running = false;
        if (this->pin >= 0) {
          digitalWrite(this->pin, this->endState);
        }
        return;
      }
      if (this->loopCallback) {
        this->loopCallback();
      }
    }
    this->lastUpdate += this->remaining;
    this->remaining = this->steps[this->step];
    this->state = !this->state;
    if (this->pin >= 0) {
      digitalWrite(this->pin, this->state);
    }
    if (this->stateChangeCallback) {
      this->stateChangeCallback();
    }
  }
}

int Async_Operations::getRepeatCount() {
  return this->repeat;
}

bool Async_Operations::getState() {
  return this->state;
}

void Async_Operations::setStateChangeCallback(void (*stateChangeCallback)(void)) {
  this->stateChangeCallback = stateChangeCallback;
}

void Async_Operations::deleteStateChangeCallback() {
  this->stateChangeCallback = 0;
}

void Async_Operations::setLoopCallback(void (*loopCallback)(void)) {
  this->loopCallback = loopCallback;
}

void Async_Operations::deleteLoopCallback() {
  this->loopCallback = 0;
}

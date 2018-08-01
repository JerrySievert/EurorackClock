#include <SimpleTimer.h>

#include "calc.h"
#include "display.h"
#include "config.h"


// current state
int count = 0;

// timer
SimpleTimer timer;

int analogMultiRead(int port) {
  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(port);
  }

  return (int) total / 10;
}

void cycleOff() {
  digitalWrite(WHOLE, LOW);
  digitalWrite(HALF, LOW);
  digitalWrite(QUARTER, LOW);
  digitalWrite(EIGHTH, LOW);

  count++;

  if (count == 8) {
    count = 0;
  }
}

/*
1. * * * *
2. *
3. * *
4. *
5. * * *
6. *
7. * *
8. *
 */

void cycleOn() {
  switch (count) {
    case 0:
      digitalWrite(WHOLE, HIGH);
      digitalWrite(HALF, HIGH);
      digitalWrite(QUARTER, HIGH);
      digitalWrite(EIGHTH, HIGH);
      break;

    case 1:
      digitalWrite(WHOLE, HIGH);
      break;

    case 2:
      digitalWrite(WHOLE, HIGH);
      digitalWrite(HALF, HIGH);
      break;

    case 3:
      digitalWrite(WHOLE, HIGH);
      break;

    case 4:
      digitalWrite(WHOLE, HIGH);
      digitalWrite(HALF, HIGH);
      digitalWrite(QUARTER, HIGH);
      break;

    case 5:
      digitalWrite(WHOLE, HIGH);
      break;

    case 6:
      digitalWrite(WHOLE, HIGH);
      digitalWrite(HALF, HIGH);
      break;

    case 7:
      digitalWrite(WHOLE, HIGH);
      break;
  }

  // figure out bpm and duration values
  int bpm_pot = analogMultiRead(BPM);
  int duration_pot = analogMultiRead(DURATION);
  int bpm = round(calculatedBPM(bpm_pot));
  float percentage = calculatedPercentage(duration_pot);
  unsigned long duration = tickDuration(bpm * 2);

  // figure out the next cycle off and set it based on bpm
  unsigned long next_start = duration;

  // figure out the next cycle on and set it based on bpm
  unsigned long next_stop = (unsigned long) (duration * percentage);

  // set the timers
  timer.setTimeout(next_start, cycleOn);
  timer.setTimeout(next_stop, cycleOff);

#if HAS_SCREEN
  display_bpm(bpm);
#endif

#if DEBUG
  Serial.print("Calculated BPM: ");
  Serial.println(bpm);
  Serial.print("Start: ");
  Serial.println(next_start);
  Serial.print("Stop:  ");
  Serial.println(next_stop);
  Serial.print("Count: ");
  Serial.println(count);
#endif
}

void setup() {
#if DEBUG
  Serial.begin(115200);
  Serial.println("Setup");
#endif

  pinMode(BPM, INPUT);
  pinMode(DURATION, INPUT);
  pinMode(WHOLE, OUTPUT);
  pinMode(HALF, OUTPUT);
  pinMode(QUARTER, OUTPUT);
  pinMode(EIGHTH, OUTPUT);

#if HAS_SCREEN
  setup_display();
#endif

#if DEBUG
  int val = analogMultiRead(BPM);
  Serial.print("BPM Read: ");
  Serial.println(val);
  Serial.print("Calculated BPM: ");
  Serial.println(round(calculatedBPM(val)));
#endif
}

bool started = false;

void loop() {
  // run the first on cycle, which should set up the first set of timers
  if (!started) {
    cycleOn();
    started = true;
  }

  // turn on the timer
  timer.run();
}

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
  digitalWrite(NOTE_16, LOW);
  digitalWrite(NOTE_8, LOW);
  digitalWrite(NOTE_4, LOW);
  digitalWrite(NOTE_2, LOW);
  digitalWrite(NOTE_1, LOW);
  digitalWrite(LED_1, LOW);

  count++;

  if (count == 16) {
    count = 0;
  }
}

void cycleOnC() {
  digitalWrite(NOTE_C, HIGH);
}

void cycleOffC() {
  digitalWrite(NOTE_C, LOW);
}

void cycleOnE() {
  digitalWrite(NOTE_E, HIGH);
}

void cycleOffE() {
  digitalWrite(NOTE_E, LOW);
}

/*
 0. * * * * *
 1. *
 2. * *
 3. *
 4. * * *
 5. *
 6. * *
 7. *
 8. * * * *
 9. *
10. * *
11. *
12. * * *
13. *
14. * *
15. *
 */

void cycleOn() {
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

  // figure out the offsets for C and E
  unsigned long c_offset = (unsigned long) (duration * 0.16);
  unsigned long e_offset = (unsigned long) (duration * 0.32);

  // set the timers
  timer.setTimeout(next_start, cycleOn);
  timer.setTimeout(next_stop, cycleOff);

  if (count % 2) {
    // odd click
    timer.setTimeout(c_offset, cycleOnC);
    timer.setTimeout(e_offset, cycleOnE);
    timer.setTimeout(next_stop + c_offset, cycleOffC);
    timer.setTimeout(next_stop + e_offset, cycleOffE);
  } else {
    // even click
    timer.setTimeout(next_start, cycleOnC);
    timer.setTimeout(next_start, cycleOnE);
    timer.setTimeout(next_stop, cycleOffC);
    timer.setTimeout(next_stop, cycleOffE);
    digitalWrite(NOTE_C, HIGH);
    digitalWrite(NOTE_E, HIGH);
    digitalWrite(LED_1, HIGH);
  }


  switch (count) {
    case 0:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      digitalWrite(NOTE_4, HIGH);
      digitalWrite(NOTE_2, HIGH);
      digitalWrite(NOTE_1, HIGH);
      break;

    case 1:
      digitalWrite(NOTE_16, HIGH);
      break;

    case 2:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      break;

    case 3:
      digitalWrite(NOTE_16, HIGH);
      break;

    case 4:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      digitalWrite(NOTE_4, HIGH);
      break;

    case 5:
      digitalWrite(NOTE_16, HIGH);
      break;

    case 6:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      break;

    case 7:
      digitalWrite(NOTE_16, HIGH);
      break;

    case 8:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      digitalWrite(NOTE_4, HIGH);
      digitalWrite(NOTE_2, HIGH);
      break;

    case 9:
      digitalWrite(NOTE_16, HIGH);
      break;

    case 10:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      break;

    case 11:
      digitalWrite(NOTE_16, HIGH);
      break;

    case 12:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      digitalWrite(NOTE_4, HIGH);
      break;

    case 13:
      digitalWrite(NOTE_16, HIGH);
      break;

    case 14:
      digitalWrite(NOTE_16, HIGH);
      digitalWrite(NOTE_8, HIGH);
      break;

    case 15:
      digitalWrite(NOTE_16, HIGH);
      break;
  }

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
  pinMode(NOTE_16, OUTPUT);
  pinMode(NOTE_8, OUTPUT);
  pinMode(NOTE_4, OUTPUT);
  pinMode(NOTE_2, OUTPUT);
  pinMode(NOTE_1, OUTPUT);
  pinMode(NOTE_C, OUTPUT);
  pinMode(NOTE_E, OUTPUT);

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

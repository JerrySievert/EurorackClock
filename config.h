#pragma once

// debug mode
#define DEBUG 1

// number of BPM when turned all of the way to the left
#define MIN_BPM 60

// number of BPM when turned all of the way to the right
#define MAX_BPM 160

// bias number of MS for turning off of the signal
#define BIAS 25

// potentiometer inputs
#define BPM      A0
#define DURATION A1

// outputs
#define WHOLE   2
#define HALF    3
#define QUARTER 4
#define EIGHTH  5


// screen
#define HAS_SCREEN true
#define SCREEN_ADDR 0x3c

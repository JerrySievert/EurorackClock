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
#define NOTE_1  3
#define NOTE_2  5
#define NOTE_4  6
#define NOTE_8  9
#define NOTE_16 10
#define NOTE_C  11
#define NOTE_E  12
#define LED_1   13

// screen
#define HAS_SCREEN false
#define SCREEN_ADDR 0x3c

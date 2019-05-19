# Eurorack Clock

Clock module that can act as a master clock for Eurorack modules.  This project
is built using the Arduino development environment

## Hardware

This module is based on an Arduino with additional hardware for connection
to other Eurorack modules.

This module can optionally use a screen for display of information for the user.
By default, this display provides very basic information and visual cues.

### Inputs

There are two inputs, both potentiometers, that allow for adjustments to the
clock:

* BPM - current BPM between 60 and 160
* Duration - how long the pulse should remain high

### Outputs

There are four logical outputs, each of which can be connected to any number
of physical outputs:

* Full BPM - a pulse for every beat
* 1/2 BPM - a pulse for every other beat
* 1/4 BPM - a pulse for every fourth beat
* 1/8 BPM - a pulse for every eighth beat
* 1/16 BPM - a pulse for every sixteenth beat
* swing C
* swing E

Since each of these can be connected to any number of physical outputs, these
are treated very simply.

### Configuration

Port configuration is based on the device that you are using, but this should
provide a basic guide.  Changes should be made in `config.h` if needed:

* BPM 10k Potentiometer - A0
* Duration 10k Potentiometer - A1
* Double speed output - D2
* Normal speed output - D3
* Double speed output - D4
* Quadrupal speed output - D5
* Screen I2C Address - 0x3c

## Software

The software is fairly straightforward, and has a couple of configuration
options available in `config.h`:

* DEBUG - output debug messages on the console
* MIN_BPM [default: `60`] - minimum BPM
* MAX_BPM [default: `160`] - maximum BPM
* BIAS [default: `25`] - minimum number of milliseconds for duration
* HAS_SCREEN [default: `true`] - whether a screen is attached

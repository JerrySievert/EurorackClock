
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include "calc.h"
#include "config.h"

#if HAS_SCREEN

Adafruit_SSD1306 display(0);

void setup_display ( ) {
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR);
  display.clearDisplay();
  display.display();
}

void display_bpm (float bpm) {
  char str[24];
  ftoa(str, bpm, 2);

  display.setCursor(0, 16);
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.print(str);
  display.print(" BPM  ");
  display.display();
}



#endif

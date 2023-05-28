#include <RTClib.h>
#include <ChainableLED.h>

/*** PIN MAPPING ***/
#define NUM_LEDS 1

#define CLKPIN 7
#define DATAPIN 8

RTC_DS3231 rtc;
ChainableLED leds(CLKPIN, DATAPIN, NUM_LEDS);
bool led_on;

void setup () {
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  led_on = false;
  leds.setColorRGB(0, 0, 0, 0);
}

void loop () {
    DateTime now = rtc.now();

    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);

    if (now.hour() >= 5 and now.hour() <= 18 and led_on == false){
      Serial.print(" LED ON");
      leds.setColorRGB(0, 255, 255, 255);
      led_on = true;
    }
    else if ((now.hour() < 5 or now.hour() > 18) and led_on == true) {
      Serial.print(" LED OFF");
      leds.setColorRGB(0, 0, 0, 0);
      led_on = false;
    }
    Serial.println();

    delay(3000);
}
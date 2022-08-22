#include "Adafruit_seesaw.h"
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "config.h"

Adafruit_seesaw ss;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

AdafruitIO_Feed *powerFeed = io.feed("power");

bool currentPowerState = true;
uint16_t currentTouch = 0;
unsigned long lastMessage = 0;
unsigned long powerOnAt = 0;

void setup() {
    Serial.begin(115200);
    while (! Serial && millis() < 5000);

    Serial.println("offwhenwet starting up");

    Wire1.setPins(SDA1, SCL1);
    ss = Adafruit_seesaw(&Wire1);

#if defined(NEOPIXEL_POWER)
    pinMode(NEOPIXEL_POWER, OUTPUT);
    digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

    pinMode(POWER_PIN, OUTPUT);
    digitalWrite(POWER_PIN, HIGH);

    if (!ss.begin(SOIL_SENSOR)) {
        Serial.println("ERROR! seesaw not found");
        while (1) { delay(1); }
    } else {
       Serial.print("seesaw started! version: ");
       Serial.println(ss.getVersion(), HEX); 
    }

    pixels.begin();
    pixels.setBrightness(20);

#if defined(ENABLE_IOT)
    Serial.print("Connecting to Adafruit IO");
    io.connect();

    while (io.status() < AIO_CONNECTED) {
      Serial.print(".");
    }

    Serial.println();
    Serial.println(io.statusText());
#endif
}

void loop() {
    io.run();

    currentTouch = ss.touchRead(0);

    Serial.print(" moisture: "); Serial.println(currentTouch);

    if (currentTouch > WET) {
        // Set LED red
        pixels.fill(0xFF0000);
        pixels.show();
        // Toggle power off
        digitalWrite(POWER_PIN, LOW);
        currentPowerState = false;

        sendMessage();
        delay(200);
        return;
    }

    // Set LED green
    pixels.fill(0x00FF00);
    pixels.show();
    if (currentPowerState == false && powerOnAt == 0) {
      powerOnAt = millis() + POWER_ON_DELAY;
    }

    if (currentPowerState == false && powerOnAt < millis()) {
      // Toggle power on
      digitalWrite(POWER_PIN, HIGH);
      currentPowerState = true;
      powerOnAt = 0;
    }

    sendMessage();
    delay(200);
}


void sendMessage() {
#if defined(ENABLE_IOT)
  unsigned long now = millis();
  // millis() resets every 50 days, so account for that
  if (lastMessage > now) {
    lastMessage = now;
    return;
  }

  // Don't send anything until our message interval passes since the last message
  if (lastMessage + MESSAGE_INTERVAL_MILLIS > now) {
    return;
  }

  // Alternate between updating moisture & temperature until there's a power change
  lastMessage = now;
  Serial.print("Sending update at "); Serial.print(now); Serial.println(" millis");
  powerFeed->save(currentPowerState);
#endif
}

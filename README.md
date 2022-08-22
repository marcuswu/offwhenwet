# offwhenwet

## Description

Turns off power to a device (such as a washing machine) when a moisture sensor detects moisture.

## Setup

This project was designed to work with:
 * [Adafruit Qt Py ESP32-S2](https://www.adafruit.com/product/5325)
 * [Adafruit STEMMA Soil Sensor](https://www.adafruit.com/product/4026)
 * [Controllable Four Outlet Power Relay](https://www.adafruit.com/product/2935)
 * [4-pin JST PH to JST SH Cable](https://www.adafruit.com/product/4424)

### Dependencies
 * Adafruit_seesaw_Library
 * Adafruit_BusIO
 * Wire
 * Adafruit_NeoPixel
 * Adafruit_IO_Arduino
 * Adafruit_MQTT_Library
 * ArduinoHttpClient
 * WiFiClientSecure
 * WiFi

## 3D Printed models

 * [Qt Py Snap fit case] (https://www.printables.com/model/117246-qt-py-snap-fit-case)
 * [Sensor clip](https://www.printables.com/model/264037-adafruit-stemma-soil-moisture-sensor-clip)
 
## Other materials
 * Mounting hardware for the Qt Py case and the power outlet relay
 * Wires for connectin the Qt Py to the power outlet relay
 * USB power supply and cable

## Configuration
 * The config.h.template should be copied to config.h
 * If using wifi, add in your wifi ssid and secret
 * If using Adafruit IO, add your username and key and configure a dashboard
 * Set the pin you use for toggling power on the power outlet relay
 * Adjust the wet threshold if desired

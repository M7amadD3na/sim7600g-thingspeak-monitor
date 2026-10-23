# SIM7600G Cellular ThingSpeak Monitor

Uses a SIM7600 cellular modem and AT commands to upload DHT22 temperature and humidity readings to ThingSpeak.

## Technologies

SIM7600G, AT commands, DHT22, HTTP, ThingSpeak

## Requirements

`DHT` and `SoftwareSerial` (board support required).

## Hardware and setup notes

Uses `SoftwareSerial(8, 9)` and carrier APN configured in the sketch. Confirm the selected board, modem interface speed, SIM plan, and APN before running.

## Run

1. Install the Arduino IDE and the required board support and libraries.
2. Open `SIM7600G_ThingSpeak_Monitor.ino` from this folder.
3. Review pin assignments, the target board, and any network settings.
4. Replace placeholders (such as `YOUR_THINGSPEAK_WRITE_API_KEY`) with **your own settings locally**. Never commit real passwords or API keys.
5. Compile and upload to compatible hardware; monitor serial output where relevant.

> Note: This portfolio package is a cleaned copy of an existing project sketch, not a claim that it was retested on hardware or security-hardened.

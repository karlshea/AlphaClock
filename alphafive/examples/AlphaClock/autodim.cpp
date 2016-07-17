/*
 * Auto-dimming photoresistor support
 * (C) 2016 Karl Shea
 *
 * This program is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 */

#include "autodim.h"

int photoPin = 7; // Analog pin the photoresistor is attached to
int photoReading = 0;  // Current photocell reading
int photoReadingLast = 0; // Last photocell reading for comparison
int photoUpdateFluctuation = 50;
byte NewBrightness = 0;  // New brightness level

bool shouldUpdateBrightness(byte Brightness, byte BrightnessMax) {
    // Store last reading and read again
    photoReadingLast = photoReading;
    photoReading = analogRead(photoPin);
    
    // Bump up reading when it's brighter out to compensate for recessed cell
    if (photoReading > 500 && photoReading < 923) photoReading += 100;

    Serial.print("Photocell: ");
    Serial.println(photocellReading);
    
    // Set new brightness
    NewBrightness = map(photoReading, 0, 1023, 1, BrightnessMax);

    // Should update if the reading fluctuated greatly and the new brightness maps differently
    return abs(photoReading - photoReadingLast) > photoUpdateFluctuation 
      && NewBrightness != Brightness;
}
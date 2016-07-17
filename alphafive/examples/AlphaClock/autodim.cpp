/*
 * Auto-dimming photocell support
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

int photocellPin = 7; // Analog pin the photoresistor is attached to
int photocellReading = 0;  // Current photocell reading
int photocellReadingLast = 0; // Last photocell reading for comparison
int photocellUpdateFluctuation = 50;
byte NewBrightness = 0;  // New brightness level

bool shouldUpdateBrightness(byte Brightness, byte BrightnessMax) {
    // Store last reading and read again
    photocellReadingLast = photocellReading;
    photocellReading = analogRead(photocellPin);
    
    // Bump up reading when it's brighter out to compensate for recessed cell
    if (photocellReading > 500 && photocellReading < 923) photocellReading += 100;

    Serial.print("Photocell: ");
    Serial.println(photocellReading);
    
    // Set new brightness
    NewBrightness = map(photocellReading, 0, 1023, 1, BrightnessMax);

    // Should update if the reading fluctuated greatly and the new brightness maps differently
    return abs(photocellReading - photocellReadingLast) > photocellUpdateFluctuation 
      && NewBrightness != Brightness;
}
/*
  LightningDetector.pde - AS3935 Franklin Lightning Sensor™ IC by AMS library demo code
  Copyright (c) 2012 Raivis Rengelis (raivis [at] rrkb.lv). All rights reserved.
  Modified in 2013 for I2C by Luka Mustafa - Musti (musti [at] wlan-si.net).

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
// I2c library by Wayne Truchsess
#include "I2C.h"
#include <AS3935.h>

void printAS3935Registers();


// Iterrupt handler for AS3935 irqs
// and flag variable that indicates interrupt has been triggered
// Variables that get changed in interrupt routines need to be declared volatile
// otherwise compiler can optimize them away, assuming they never get changed
void AS3935Irq();
volatile int AS3935IrqTriggered;

// Library object initialization First argument is interrupt pin, second is device I2C address
AS3935 AS3935(2,0);

void setup()
{
  Serial.begin(9600);
  //I2C library initialization
  I2c.begin();
  I2c.pullup(true);
  I2c.setSpeed(1); //400kHz
  
  // optional control of power for AS3935 via a PNP transistor
  // very useful for lockup prevention and power saving
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
 
  // reset all internal register values to defaults
  AS3935.reset();
  // and run calibration
  // if lightning detector can not tune tank circuit to required tolerance,
  // calibration function will return false
  if(!AS3935.calibrate())
    Serial.println("Tuning out of range, check your wiring, your sensor and make sure physics laws have not changed!");

  // since this is demo code, we just go on minding our own business and ignore the fact that someone divided by zero

  // first let's turn on disturber indication and print some register values from AS3935
  // tell AS3935 we are indoors, for outdoors use setOutdoors() function
  AS3935.setIndoors();
  // turn on indication of distrubers, once you have AS3935 all tuned, you can turn those off with disableDisturbers()
  AS3935.enableDisturbers();
  printAS3935Registers();
  AS3935IrqTriggered = 0;
  // Using interrupts means you do not have to check for pin being set continiously, chip does that for you and
  // notifies your code
  // demo is written and tested on ChipKit MAX32, irq pin is connected to max32 pin 2, that corresponds to interrupt 1
  // look up what pins can be used as interrupts on your specific board and how pins map to int numbers

  // ChipKit Max32 - irq connected to pin 2
  // attachInterrupt(1,AS3935Irq,RISING);
  // uncomment line below and comment out line above for Arduino Mega 2560, irq still connected to pin 2, same for atmega328p
  attachInterrupt(0,AS3935Irq,RISING);
}

void loop()
{
  // here we go into loop checking if interrupt has been triggered, which kind of defeats
  // the whole purpose of interrupts, but in real life you could put your chip to sleep
  // and lower power consumption or do other nifty things
  if(AS3935IrqTriggered)
  {
    // reset the flag
    AS3935IrqTriggered = 0;
    // first step is to find out what caused interrupt
    // as soon as we read interrupt cause register, irq pin goes low
    int irqSource = AS3935.interruptSource();
    // returned value is bitmap field, bit 0 - noise level too high, bit 2 - disturber detected, and finally bit 3 - lightning!
    if (irqSource & 0b0001)
      Serial.println("Noise level too high, try adjusting noise floor");
    if (irqSource & 0b0100)
      Serial.println("Disturber detected");
    if (irqSource & 0b1000)
    {
      // need to find how far that lightning stroke, function returns approximate distance in kilometers,
      // where value 1 represents storm in detector's near victinity, and 63 - very distant, out of range stroke
      // everything in between is just distance in kilometers
      int strokeDistance = AS3935.lightningDistanceKm();
      if (strokeDistance == 1)
        Serial.println("Storm overhead, watch out!");
      if (strokeDistance == 63)
        Serial.println("Out of range lightning detected.");
      if (strokeDistance < 63 && strokeDistance > 1)
      {
        Serial.print("Lightning detected ");
        Serial.print(strokeDistance,DEC);
        Serial.println(" kilometers away.");
      }
    }
  }
}

void printAS3935Registers()
{
  int noiseFloor = AS3935.getNoiseFloor();
  int spikeRejection = AS3935.getSpikeRejection();
  int watchdogThreshold = AS3935.getWatchdogThreshold();
  Serial.print("Noise floor is: ");
  Serial.println(noiseFloor,DEC);
  Serial.print("Spike rejection is: ");
  Serial.println(spikeRejection,DEC);
  Serial.print("Watchdog threshold is: ");
  Serial.println(watchdogThreshold,DEC);  
}

// this is irq handler for AS3935 interrupts, has to return void and take no arguments
// always make code in interrupt handlers fast and short
void AS3935Irq()
{
  AS3935IrqTriggered = 1;
}

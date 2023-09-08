//
// Arduino Mbed Core Deep Sleep Lock Analyzer (USB and micros() Timer Deactivation Edition)
//
// Original author: A. Vidstrom (http://arduino.cc)
//
// This code is in the public domain.
//
// WARNING: This sketch uses an undocumented method to extract the number of active deep sleep locks from
//          the Mbed Core and might break at any time in the future. Use it only for experimental purposes.

#include <mbed.h>
#include <usb_phy_api.h>

uint16_t getDeepSleepLockNumber()
{
  return *((uint16_t*) *((uint32_t*) ((((uint32_t) &sleep_manager_can_deep_sleep) & 0xfffffffe) + 0x10)));
}

void setup() {
  pinMode(LEDB, OUTPUT);
  // Turn off USB
  USBPhy *phy = get_usb_phy();
  phy->deinit();
  // Turn of micros() timer
  getTimer(TIMER).stop();
}

void loop() {
  uint16_t numLocks = getDeepSleepLockNumber();
  for (uint16_t i=0; i<numLocks; i++)
  {
    digitalWrite(LEDB, LOW);
    delay(250);
    digitalWrite(LEDB, HIGH);
    delay(250);
  }
  delay(2000);
}

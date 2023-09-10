//
// Arduino Mbed Core Deep Sleep Lock Analyzer (USB and micros() Timer Deactivation with Proportion Indication Edition)
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
  pinMode(LEDR, OUTPUT);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, HIGH);
  // Turn off USB
  USBPhy *phy = get_usb_phy();
  phy->deinit();
  // Turn off micros() timer
  getTimer(TIMER).stop();
  // Red when there are deep sleep locks acquired, and blue when no deep sleep locks are acquired.
  // The resulting color indicates the proportion of time between these two states.
  for ( ; ;)
  {
    uint16_t numLocks = getDeepSleepLockNumber();
    if (0 == numLocks)
    {
      digitalWrite(LEDB, LOW);
      digitalWrite(LEDR, HIGH);
    }
    else
    {
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, HIGH);  
    }
  }
}

void loop() {
}

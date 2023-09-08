//
// Arduino Mbed Core Deep Sleep Lock Analyzer
//
// Original author: A. Vidstrom (http://arduino.cc)
//
// This code is in the public domain.
//
// WARNING: This sketch uses an undocumented method to extract the number of active deep sleep locks from
//          the Mbed Core and might break at any time in the future. Use it only for experimental purposes.

#include <mbed.h>

uint16_t getDeepSleepLockNumber()
{
  return *((uint16_t*) *((uint32_t*) ((((uint32_t) &sleep_manager_can_deep_sleep) & 0xfffffffe) + 0x10)));
}

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
}

void loop() {
  bool can_deep_sleep = sleep_manager_can_deep_sleep();
  Serial.print("Mbed can deep sleep: ");
  can_deep_sleep ? Serial.println("Yes") : Serial.println("No");

  uint16_t numLocks = getDeepSleepLockNumber();
  Serial.print("Number of active deep sleep locks: ");
  Serial.println(numLocks);

  delay(1000);
}

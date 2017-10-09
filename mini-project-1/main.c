#include <stdio.h>
#include <rtt_stdio.h>
#include "xtimer.h"
#include <string.h>
#include "saul_reg.h"

#define ENABLE_DEBUG    (0)
#include "debug.h"

#ifndef SAMPLE_INTERVAL
#define SAMPLE_INTERVAL ( 1000000UL)
#endif

void critical_error(void) {
  DEBUG("CRITICAL ERROR, REBOOT\n");
  NVIC_SystemReset();
  return;
}

int main(void) {

  while (1) {
    xtimer_usleep(SAMPLE_INTERVAL);
    LED_TOGGLE;
  }

  return 0;
}

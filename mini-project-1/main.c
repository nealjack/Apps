#include <stdio.h>
#include <rtt_stdio.h>
#include "xtimer.h"
#include <string.h>
#include "periph/i2c.h"
#include "periph/gpio.h"

#define ENABLE_DEBUG    (0)
#include "debug.h"

#ifndef SAMPLE_INTERVAL
#define SAMPLE_INTERVAL ( 2000000UL)
#endif

void critical_error(void) {
  DEBUG("CRITICAL ERROR, REBOOT\n");
  NVIC_SystemReset();
  return;
}

void shutdown_sensors(void) {
  i2c_acquire(I2C_0);
  i2c_init_master(I2C_0, I2C_SPEED_NORMAL);

  // shutdown TMP006 temperature sensor
  // address 0x44
  uint8_t tmp006_off[2] = {0x0, 0x0};
  i2c_write_regs(I2C_0, 0x44, 0x02, tmp006_off, 2);

  // shutdown HDC1080 temperature/humidity
  // Automatically goes into sleep mode!

  // shutdown APDS-9007 light sensor
  // shutdown with pin PA28, active high
  gpio_init(GPIO_PIN(0, 28), GPIO_OUT);
  gpio_write(GPIO_PIN(0, 28), 1);

  // shutdown FXOS8700 accel/mag
  // address 0x1e
  uint8_t fxos8700_off= 0x0;
  i2c_write_reg(I2C_0, 0x1e, 0x2c, fxos8700_off);
}

int main(void) {
  xtimer_init();
  shutdown_sensors();

  while (1) {
    xtimer_usleep(SAMPLE_INTERVAL);
    LED_TOGGLE;
  }

  return 0;
}

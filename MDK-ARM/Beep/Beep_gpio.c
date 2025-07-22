#include "Beep_gpio.h"

void beep_on(BEEP_CONFIG config)
{
  // Use the config structure to access the GPIO port and pin
  gpio_setpin(config.gpio_port, config.gpio_pin);
}

void beep_off(BEEP_CONFIG config)
{
  // Use the config structure to access the GPIO port and pin
  gpio_resetpin(config.gpio_port, config.gpio_pin);
}
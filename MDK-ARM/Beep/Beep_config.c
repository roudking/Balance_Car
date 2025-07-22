
#include "Beep_config.h"

#define BEEP_GPIO_PORT GPIOA
#define BEEP_GPIO_PIN GPIO_PIN_0   

BEEP_CONFIG beep_config = {
    .gpio_port = BEEP_GPIO_PORT,
    .gpio_pin = BEEP_GPIO_PIN
};

#include "Driver_Encoder.h"

void DriverEncoder_start(DRIVER_CONFIG driver)
{
     encoder_init(driver.Encoder_PORT);
}

int16_t DriverEncoder_getcounter(DRIVER_CONFIG driver)
{
    if (driver.Encoder_polarity == 1) {
        return encoder_getcounter(driver.Encoder_PORT);
    }
    else {
        return -encoder_getcounter(driver.Encoder_PORT);
    }

}

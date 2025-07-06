#ifndef _DRIVER_ENCODER_H
#define _DRIVER_ENCODER_H


#include "Driver_config.h"
#include "stdint.h"


void DriverEncoder_start(DRIVER_CONFIG driver);
int16_t DriverEncoder_getcounter(DRIVER_CONFIG driver);


#endif

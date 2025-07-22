#ifndef _BEEP_H
#define _BEEP_H

#include "Beep_gpio.h"

typedef struct {
   BEEP_CONFIG beepconfig; // Configuration for the beep
} BEEPER;

void Beep_create(BEEPER *beeper, BEEP_CONFIG config);
void Beep_on(BEEPER *beeper);
void Beep_off(BEEPER *beeper);

#endif



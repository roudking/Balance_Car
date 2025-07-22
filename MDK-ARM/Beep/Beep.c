#include "Beep.h"

void Beep_create(BEEPER *beeper, BEEP_CONFIG config)
{
    // Initialize the beeper with its configuration
    beeper->beepconfig = config;
}

void Beep_on(BEEPER *beeper)
{
 beep_on(beeper->beepconfig);
}

void Beep_off(BEEPER *beeper)
{
 beep_off(beeper->beepconfig);
}
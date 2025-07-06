#include "Driver_pwm.h"

void DriverPwm_start(DRIVER_CONFIG driver)
{
  pwm_init(driver.DriverPWM_PORT, driver.Channel[0]);
  pwm_init(driver.DriverPWM_PORT, driver.Channel[1]);
}

static void Driverpwm_set(DRIVER_CONFIG driver,int channel, int pwm)
{
    pwm_set(driver.DriverPWM_PORT,driver.Channel[channel - 1],pwm);
}

void Driver_setpwm(DRIVER_CONFIG driver,int pwm)
{
	if (driver.Pwm_polarity == 0){
		if (pwm > 0) {
			Driverpwm_set(driver, 1, pwm);
			Driverpwm_set(driver, 2, 0);
		} else if (pwm < 0) {
			Driverpwm_set(driver, 1, 0);
			Driverpwm_set(driver, 2, -pwm);
		}
	} else if (driver.Pwm_polarity == 1) {
		if (pwm > 0) {
			Driverpwm_set(driver, 1, 0);
			Driverpwm_set(driver, 2, pwm);
		} else if (pwm < 0) {
			Driverpwm_set(driver, 1, -pwm);
			Driverpwm_set(driver, 2, 0);
		}
	}
	if (pwm == 0) {
		Driverpwm_set(driver, 1, 0);
		Driverpwm_set(driver, 2, 0);
	}
}

//void Driver_setpwm(DRIVER_CONFIG driver,int pwm)
//{
//	if (driver.Pwm_polarity == 1) {
//		if (pwm > 0) {
//			Driverpwm_set(driver, 1, driver.DriverPWMTimer_autoreload - pwm);
//			Driverpwm_set(driver, 2, driver.DriverPWMTimer_autoreload);
//		} else if (pwm < 0) {
//			Driverpwm_set(driver, 1, driver.DriverPWMTimer_autoreload);
//			Driverpwm_set(driver, 2, driver.DriverPWMTimer_autoreload  + pwm);
//		}
//	} else if (driver.Pwm_polarity == 0) {
//		if (pwm > 0) {
//			Driverpwm_set(driver, 1, driver.DriverPWMTimer_autoreload);
//			Driverpwm_set(driver, 2, driver.DriverPWMTimer_autoreload - pwm);
//		} else if (pwm < 0) {
//			Driverpwm_set(driver, 1, driver.DriverPWMTimer_autoreload  + pwm);
//			Driverpwm_set(driver, 2, driver.DriverPWMTimer_autoreload);
//		}
//	}
//	if (pwm == 0) {
//		Driverpwm_set(driver, 1, driver.DriverPWMTimer_autoreload);
//		Driverpwm_set(driver, 2, driver.DriverPWMTimer_autoreload);
//	}
//}




#include "motor.h"
#include "gpio.h"
#include "pwm.h"




void motor_init(void)
{
	motor_gpio_init();
	pwm_init();
}





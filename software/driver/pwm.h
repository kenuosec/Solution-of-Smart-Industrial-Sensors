#ifndef __PWM_H
#define __PWM_H

#include "system.h"



void pwm_init(void);
void pwm_set(u8 percent, u8 dir);
void pwm_front_init(void);
void pwm_front_set(u8 percent, u8 dir);




#endif



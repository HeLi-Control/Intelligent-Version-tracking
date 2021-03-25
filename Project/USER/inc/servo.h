#ifndef _SERVO_H_
#define _SERVO_H_

#include "headfile.h"
#include <rtthread.h>

#define TRACKING_SERVO			PWM4_MODULE2_CHA_C30
#define IDENTIFYING_SERVO		PWM4_MODULE3_CHA_C31

struct servo_duty{
	uint16 tracking_duty;
	uint16 identifying_duty;
};
extern struct servo_duty servo_duty;

typedef enum{tracking_servo = 1, identifying_servo}Servo_enum;

extern void servo_init(void);
extern void servo_turn(Servo_enum servo);

#endif /* _SERVO_H_ */

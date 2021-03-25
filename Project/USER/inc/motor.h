#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "headfile.h"

#define MOTOR_RIGHT_FORWARD		PWM1_MODULE3_CHA_D0
#define MOTOR_RIGHT_BACKWARD	PWM1_MODULE3_CHB_D1
#define	MOTOR_LEFT_FORWARD		PWM2_MODULE3_CHA_D2
#define	MOTOR_LEFT_BACKWARD		PWM2_MODULE3_CHB_D3

struct motor_duty{
	uint16 motor_right_forward;
	uint16 motor_right_backward;
	uint16 motor_left_forward;
	uint16 motor_left_backward;
};
typedef enum{Forward,Backward}run_direction_enum;

extern struct motor_duty motor_duty;

extern void motor_init(void);
extern void motor_run(run_direction_enum Dir);

#endif /* _MOTOR_H_ */

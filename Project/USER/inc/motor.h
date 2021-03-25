#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "headfile.h"

#define MOTOR_RIGHT_FORWARD		PWM1_MODULE3_CHA_D0
#define MOTOR_RIGHT_BACKWARD	PWM1_MODULE3_CHB_D1
#define	MOTOR_LEFT_FORWARD		PWM2_MODULE3_CHA_D2
#define	MOTOR_LEFT_BACKWARD		PWM2_MODULE3_CHB_D3

extern uint8 Motor_Run_Flag;

struct motor_duty{
	uint16 motor_right_forward;
	uint16 motor_right_backward;
	uint16 motor_left_forward;
	uint16 motor_left_backward;
};
typedef enum{Forward = 1,Backward}run_direction_enum;

extern struct motor_duty motor_duty;

extern void motor_init(void);
extern uint8 motor_run(run_direction_enum Direction);

#endif /* _MOTOR_H_ */

#include "servo.h"

struct servo_duty servo_duty;

void servo_init(void)
{
	// 两路pwm都设置成50Hz,占空比7.5%
	pwm_init(TRACKING_SERVO, 50, 3750);
	servo_duty.tracking_duty = 3750;
	pwm_init(IDENTIFYING_SERVO, 50, 3750);
	servo_duty.identifying_duty = 3750;
}

void servo_turn(Servo_enum servo)
{
	switch (servo)
	{
		case tracking_servo:
			pwm_duty(TRACKING_SERVO, servo_duty.tracking_duty);
			break;
		case identifying_servo:
			pwm_duty(IDENTIFYING_SERVO, servo_duty.identifying_duty);
			break;
	}
}


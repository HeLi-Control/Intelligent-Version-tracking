#include "motor.h"

struct motor_duty motor_duty;

void motor_init(void)
{
	// 电机的四路PWM都是12KHz,0%的占空比,这里AB相不能同时输出
	pwm_init(PWM1_MODULE3_CHA_D0, 12000, 0);// 占空比为5000/PWM_DUTY_MAX PWM_DUTY_MAX在fsl_pwm.h文件中 默认为50000
	motor_duty.motor_right_forward = 0;
	pwm_init(PWM1_MODULE3_CHB_D1, 12000, 0);
	motor_duty.motor_left_backward = 0;
	
	pwm_init(PWM2_MODULE3_CHA_D2, 12000, 0);
	motor_duty.motor_left_forward = 0;
	pwm_init(PWM2_MODULE3_CHB_D3, 12000, 0);
	motor_duty.motor_left_backward = 0;
}

void motor_run(run_direction_enum Dir)
{
	switch (Dir)
	{
		case (Forward):
			if (motor_duty.motor_right_backward != 0 && motor_duty.motor_right_forward != 0)
				motor_duty.motor_right_backward = 0;
			if (motor_duty.motor_left_backward != 0 && motor_duty.motor_left_forward != 0)
				motor_duty.motor_left_backward = 0;
			pwm_duty(MOTOR_RIGHT_FORWARD, motor_duty.motor_right_forward);
			pwm_duty(MOTOR_LEFT_FORWARD, motor_duty.motor_left_forward);
			break;
		case (Backward):
			if (motor_duty.motor_right_backward != 0 && motor_duty.motor_right_forward != 0)
				motor_duty.motor_right_forward = 0;
			if (motor_duty.motor_left_backward != 0 && motor_duty.motor_left_forward != 0)
				motor_duty.motor_left_forward = 0;
			pwm_duty(MOTOR_RIGHT_FORWARD, motor_duty.motor_right_backward);
			pwm_duty(MOTOR_LEFT_FORWARD, motor_duty.motor_left_backward);
			break;
	}
}


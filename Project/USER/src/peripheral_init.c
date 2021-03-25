#include "peripheral_init.h"

void peripherial_init(void)
{
	motor_init();
	servo_init();
	gpio_init(B9,GPO,0,GPIO_PIN_CONFIG);// ¾ÍÐ÷Ö¸Ê¾µÆ
}

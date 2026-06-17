#ifndef _LED_OPR_H_
#define _LED_OPR_H_

struct led_opr 
{
	int(*init)(int which),
	int(*ctl)(int which,char status),
};

struct led_opr *get_led_opr(void);

#endif

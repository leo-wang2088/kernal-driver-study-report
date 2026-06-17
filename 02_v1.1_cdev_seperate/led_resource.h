#ifndef _LED_RESOURCE_H__
#define _LED_RESOURCE_H__

#define PIN(x)     (x&0xFFFF)
#define GROUP(x)   (x>>16)
#define GROUP_PIN(x,y) ((x<<16)|(y))
struct led_source
{
	int resource,
};

struct led_source *get_led_source(void);

#endif

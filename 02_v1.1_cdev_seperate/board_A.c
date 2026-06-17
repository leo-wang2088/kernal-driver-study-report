#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/gfp.h>
#include <linux/err.h>
#include "led_opr.h"
#include "led_resource.h"

/* 板载层级，只声明该板的硬件资源*/

struct led_source led_resource =
{
	.resource=GROUP_PIN(5,1),
};


struct led_opr *get_led_resource(void)
{
	return &led_resource;
}



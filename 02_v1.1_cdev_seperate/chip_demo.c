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

/*芯片级，只负责操作芯片引脚*/

static struct led_resource *led_rsc=NULL;

static int led_init(int which)
{
	if(!led_src)
		led_rsc=get_led_resource();
	printk("init gpio:group %d , pin:%d\n",GROUP(led_rsc->resource),PIN(led_rsc->resource))
	switch(GROUP(led_rsc->resource))
	{
		case 0:
		{
			printk("init pin of group 0 ...\n");
			break;
		}
		/*可继续填充其他case*/
	}
	return 0;
}

static int led_ctl(int which,char status)
{
	printk("set led %s: group %d, pin %d\n", status ? "on" : "off", GROUP(led_rsc->pin), PIN(led_rsc->pin));
	
	switch(GROUP(led_rsc->pin))
	{
		case 0:
		{
			printk("set pin of group 0 ...\n");
			break;
		}
		/*可继续填充其他case*/
	}

}

struct led_opr led_operations = 
{
	.init=led_init,
	.ctl=led_ctl,
}

struct led_opr *get_led_opr(void)
{
	return &led_operations;
}




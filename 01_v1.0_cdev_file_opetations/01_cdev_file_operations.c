#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/gfp.h>
#include <linux/err.h>


static int led_major;
static struct class *led_class=NULL;
static struct device *led_device=NULL;

static int led_drv_open (struct inode *node, struct file *file)
{
	printk("%s %s line %d\n",__FILE__,__FUNCTION__,__LINE__);
	return 0;
}

static ssize_t led_drv_write (struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
	char status;
	int err = copy_from_user(&status,buf,1);
	//理论上这里应该是要加一个mutex
	//根据status的值，执行关灯开灯操作
	//....
	//理论上这里应该是要释放对应的mutex
	return 1;
}

static ssize_t led_drv_read (struct file *file, char __user *buf, size_t size, loff_t *offset){
	printk("%s %s line %d\n",__FILE__,__FUNCTION__,__LINE__);
	return 0;
}

static int led_drv_close (struct inode *node, struct file *file){
	printk("%s %s line %d\n",__FILE__,__FUNCTION__,__LINE__);
	return 0;

}


static struct file_operations led_opr = 
{
	.owner=THIS_MODULE,
	.open=led_drv_open,
	.write=led_drv_write,
	.read=led_drv_read,
	.release=led_drv_close,
};


static int __init led_drv_init(void)
{
	int ret=0;
	/* 1.设备注册 */
	led_major=register_chrdev(0,"led_cdev",&led_opr);
	if(led_major<0)
	{
		printk("register char device failed err=%d\n",led_major);
		return led_major;
	}
	/* 2.类创建 */
	led_class=class_create(THIS_MODULE,"led_class");
	if(IS_ERR(led_class))
	{
		ret = PTR_ERR(led_class);
		printk("led class create failed,ret=%d\n",ret);
		goto err_unreg_chr;
		
	}
	/* 3.设备创建 */
	led_device=device_create(led_class,NULL,MKDEV(led_major,0),NULL,"device0");
	if(IS_ERR(led_device))
	{
		ret=PTR_ERR(led_device);
		printk("led device create failed,ret=%d\n",ret);
		goto err_cre_fail;
	}
	printk("led_drv_init ok\n");
	return 0;


	
err_cre_fail:
	class_destroy(led_class);
err_unreg_chr:
	unregister_chrdev(led_major,"led_cdev");
	return ret;

	
}

static void __exit led_drv_exit(void)
{
	if(led_device)
		device_destroy(led_class,MKDEV(led_major,0));
	if(led_class)
		class_destroy(led_class);
	unregister_chrdev(led_major,"led_cdev");
}
module_init(led_drv_init);
module_exit(led_drv_exit);
MODULE_LICENSE("GPL");



#include <linux/module.h>
#include <linux/kernel.h>
int init_module(void)
{
	printk(KERN_ALERT "Hello Humans,This is Vaibhav Choudhary speaking");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_ALERT "Goodbye Humans");
}

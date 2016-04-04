#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include "query_ioctls.h"
static dev_t device1;              //struct dev_t stores the major and minor numbers
static struct cdev cdev_device1    // To register as a character device in the kernel
static struct class *cl 		   // udev daemon uses this to create device files
static int variable1=1,variable2=2; //Copy of the variables maintained by the driver
static int open1(struct inode *i, struct file *f) 	//.open in file operations
{
    printk(KERN_INFO "Device has been opened\n")
    return 0;
}
static int close1(struct inode *i, struct file *f)  //.close in file operations
{
    printk(KERN_INFO "Device has been closed\n")
    return 0;
}

static struct file_operations file_ops =			//fileoperations structure
{
    .owner = THIS_MODULE,
    .open = open1,
    .release = close1,
    .unlocked_ioctl = ioctl1                        //assuming kernelversion>(2,6,35)
};

static long ioctl1(struct file *f, unsigned int cmd, unsigned long arg) //function to perform ioctls
{
	query_for_ioctls q1;
	switch(cmd)
	{
		case query_getvar:
		q1.variable1=variable1;
		q1.variable2=variable2;
		copy_to_user((query_for_ioctls *)arg, &q1, sizeof(query_for_ioctls);
		break;
	
	 	case query_clearvar:
	 	variable1=0;
	 	variable2=0;
	 	break;
	 	case query_setvar:
	 	copy_from_user(&q1, (query_for_ioctls *)arg, sizeof(query_for_ioctls);
	 	variable1=q1.variable1;
	 	variable2=q2.variable2;
	 	break;

	}

return 0;
}
static int __init query_init(void)
{
	struct device *dev_ret;
	if ( alloc_chrdev_region(&device1, 0, 1, "query_ioctl") < 0)
    {
        return -1;
        printk(KERN_INFO "No major and minor numbers were assigned");
    }
 
    cdev_init(&cdev_device1, &file_ops);
 
    if (cdev_add(&cdev_device1, device1, 1) < 0)
    {
        return -1;
        printk(KERN_INFO "Device has not been succesfully registered in the kernel");
    }
     
    cl = class_create(THIS_MODULE, "char1"); //Creates class cl that will be populated by Kernel
    dev_ret = device_create(cl, NULL, device1, NULL, "query_for_ioctls");//cl is populated for udev daemon
 
    return 0;
}
 
static void __exit query_exit(void)
{
    device_destroy(cl, device1);
    class_destroy(cl);
    cdev_del(&cdev_device1);
    unregister_chrdev_region(device1, 1);
}
 
module_init(query_init);
module_exit(query_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vaibhav Choudhary");
MODULE_DESCRIPTION("Char Driver implementing ioctls");
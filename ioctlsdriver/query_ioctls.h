#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H
#include <linux/ioctl.h> //For including <asm/ioctl.h to help with choosing ioctl numbers>
 typedef struct           //  struct containing variables that will be queried.
{
	int variable1,variable2;
} query_for_ioctls;
#define query_getvar  _IOR('q',1,query_for_ioctls *);
#define query_clearvar  _IO('q',2);
#define query_setvar  _IOW('q',3,query_for_ioctls *);

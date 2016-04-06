//Application to perform ioctls
#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "query_ioctls.h"
int fd;
void get_variables(int fd)
{
	query_for_ioctls query1;
	ioctl(fd, query_getvar, &query1);
	printf("The value of variable1 is : &d\n",query1.variable1);
	printf("The value of variable2 is : &d\n",query1.variable2);
}
void clear_variables(int fd)
{
    ioctl(fd, query_clearvar);
 	printf("The variables have been cleared\n");
 	   
}

void set_variables(int fd)
{
    int variable;
    query_for_ioctls query1;
 
    printf("Enter variable1: ");
    scanf("%d", &variable);
    getchar();
    query1.variable1 = variable;
    printf("Enter variable2: ");
    scanf("%d", &variable2);
    getchar();
    query1.variable2 = variable;
 	ioctl(fd, query_setvar, &query1)
}
int main()
{
	char *file="/dev/query_for_ioctls";
	int option=0;
	char ans='Y';
	fd = open(file, O_RDWR);
	while(ans=='y'||ans=='Y')
	{
		printf("Please enter what you wish to do:\n");
		printf("1.) Get the variabels stored in the memory\n");
		printf("2.) Clear the variabels stored in the memory\n");
		printf("3.) Set the variabels stored in the memory\n");
		scanf("%d",&option);
		getchar();
		
		switch(option)
		{
			case 1:
			get_variables(fd);
			break;
			case 2:
			clear_variables(fd);
			break;
			case 3:
			set_variables(fd);
			break;
		}
		printf("Want to perform more actions?\n");
		scanf("%c",&ans);
		

	}

close(fd);
return 0;
}





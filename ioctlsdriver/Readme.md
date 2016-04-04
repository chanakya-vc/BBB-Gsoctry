This contains a driver that enables the use of ioctls.

The driver is query_ioctldriver.c.

query_ioctls.h defines the structure containing the variables that will be queried.It also defines that macros that help set up
command numbers.

App_to_perform_ioctls.c is the userland API,that enables the user to get,set and clear the values of the variables using ioctls. 

#include "os.h"

int i = 0;
void start_kernel(void)
{	
	uart_init();
	printf("this is uart_test: %d + %s = %c\nDone!\n",1, "1", '2');
	

	page_init();

	sched_init();


	schedule();

	printf("Would not go here\n");
	while (1) {
		// uart_puts("666");
	}; // stop here!

}


#include "os.h"

int i = 0;
void start_kernel(void)
{	
	uart_init();
	int ch = 1;
	uart_puts("777\n");
	printf("bbbb%cbbbbb\n", 'a');
	

	page_init();
	while (1) {
		// uart_puts("666");
	}; // stop here!

}


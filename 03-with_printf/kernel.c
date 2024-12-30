#include "os.h"

void start_kernel(void)
{	
	uart_init();
	uart_puts("Hello, RVOS!1\n");
	int i = 0;
	printf("Hello, RVOS!22\n");
	printf("Hello, RVOS!333\n");
	printf("%d", 123);
	printf("11111111111\n");
	// printf("%c\n", 'a');
	// while( i < 10){
	// 	printf("%d", i);
	// 	i++;
	// }

	while (1) {}; // stop here!

}


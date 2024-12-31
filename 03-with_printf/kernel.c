#include "os.h"

int i = 0;
void start_kernel(void)
{	
	// uart_init();
	// i++;
	// if(i > 3){
	// 	uart_puts("stop");
	// 	while(1){};
	// }
	// else{
	// 	uart_puts("start");
	// }
	// uart_puts("Hello, RVOS!1\n");
	// int i = 0;
	// printf("Hello, RVOS!22\n");
	// printf("Hello, RVOS!333\n");
	// printf("11111111111\n");
	// printf("%d\n", 123);
	// printf("%c\n", 'a');
	// while( i < 10){
	// 	printf("%d", i);
	// 	i++;
	// }
	int ch = 1;
	uart_puts("777\n");
	printf("bbbb%cbbbbb\n", 'a');
	switch (ch) {
	case 1:
		uart_puts("1\n");
		break;
	case 2:
		uart_puts("2\n");
		break;
	case 3:
		uart_puts("3\n");
		break;
	case 4:
		uart_puts("4\n");
		break;
	case 5:
		uart_puts("5\n");
		break;
	default:
		uart_puts("default\n");
		break;
	}

	while (1) {
		// uart_puts("666");
	}; // stop here!

}


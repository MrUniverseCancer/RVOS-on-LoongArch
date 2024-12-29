extern void uart_init(void);
extern void uart_puts(char *s);

void start_kernel(void)
{	
	while (1) {}; // stop here!
	uart_init();
	uart_puts("Hello, RVOS!11\n");


}


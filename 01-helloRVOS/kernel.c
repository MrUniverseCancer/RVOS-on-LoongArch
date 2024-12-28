extern void uart_init(void);
extern void uart_puts(char *s);

// #define LSR_TX_IDLE  (1 << 5)
// unsigned long uart_base = 0x1fe001e0;

// #define UART0_THR  (uart_base + 0)
// #define UART0_LSR  (uart_base + 5)

// static char io_readb(unsigned long addr)
// {
//     return *(volatile char*)addr;
// }

// static void io_writeb(unsigned long addr, char c)
// {
//     *(char*)addr = c;
// }
// static void putc(char c)
// {
//     // wait for Transmit Holding Empty to be set in LSR.
//     while((io_readb(UART0_LSR) & LSR_TX_IDLE) == 0);
//     io_writeb(UART0_THR, c);
// }

// static void puts(char *str)
// {
//     while (*str != 0) {
//         putc(*str);
//         str++;
//     }
// }


void start_kernel(void *a0, void *a1, void *a2)
{
	// uart_init();
	uart_puts("Hello, RVOS!11\n");

	while (1) {}; // stop here!
}


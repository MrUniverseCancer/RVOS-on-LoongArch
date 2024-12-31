#ifndef __OS_H__
#define __OS_H__

#include "types.h"
#include "platform.h"

#include <stddef.h>
#include <stdarg.h>

/* uart */
extern int uart_putc(char ch);
extern void uart_puts(char *s);
extern void uart_init();

/* printf */
extern int  printf(const char* s, ...);
extern void panic(char *s);


#endif /* __OS_H__ */

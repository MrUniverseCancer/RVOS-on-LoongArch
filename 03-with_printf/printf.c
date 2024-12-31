#include "os.h"

/*
 * ref: https://github.com/cccriscv/mini-riscv-os/blob/master/05-Preemptive/lib.c
 */

static int _vsnprintf(char * out, size_t n, const char* s, va_list vl)
{
	int format = 0;
	int longarg = 0;
	size_t pos = 0;
	for (; *s; s++) {
		if (format) {
			uart_puts("adskufhbesr\n");
			switch (*s) {
			case 'c':{
				// uart_puts("get %% d here\n");
				if (out && pos < n) {
					out[pos] = (char)va_arg(vl,int);
				}
				pos++;
				longarg = 0;
				format = 0;
				break;
				}
			case 'd': {
				// long num = 123;
				uart_puts("get %% d here\n");
				long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
				if (num < 0) {
					num = -num;
					if (out && pos < n) {
						out[pos] = '-';
					}
					pos++;
				}
				long digits = 1;
				for (long nn = num; nn /= 10; digits++);
				for (int i = digits-1; i >= 0; i--) {
					if (out && pos + i < n) {
						out[pos + i] = '0' + (num % 10);
					}
					num /= 10;
				}
				pos += digits;
				longarg = 0;
				format = 0;
				break;
			}
			case 's': {
				const char* s2 = va_arg(vl, const char*);
				while (*s2) {
					if (out && pos < n) {
						out[pos] = *s2;
					}
					pos++;
					s2++;
				}
				longarg = 0;
				format = 0;
				break;
			}
			case 'p': {
				longarg = 1;
				if (out && pos < n) {
					out[pos] = '0';
				}
				pos++;
				if (out && pos < n) {
					out[pos] = 'x';
				}
				pos++;
			}
			case 'x': {
				long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
				int hexdigits = 2*(longarg ? sizeof(long) : sizeof(int))-1;
				for(int i = hexdigits; i >= 0; i--) {
					int d = (num >> (4*i)) & 0xF;
					if (out && pos < n) {
						out[pos] = (d < 10 ? '0'+d : 'a'+d-10);
					}
					pos++;
				}
				longarg = 0;
				format = 0;
				break;
			}
			default:
				uart_puts("error: unknown format\n");
				break;
			}
			
			
			// switch(*s) {
			// case 'l': {
			// 	longarg = 1;
			// 	break;
			// }
			// case 'p': {
			// 	longarg = 1;
			// 	if (out && pos < n) {
			// 		out[pos] = '0';
			// 	}
			// 	pos++;
			// 	if (out && pos < n) {
			// 		out[pos] = 'x';
			// 	}
			// 	pos++;
			// }
			// case 'x': {
			// 	long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
			// 	int hexdigits = 2*(longarg ? sizeof(long) : sizeof(int))-1;
			// 	for(int i = hexdigits; i >= 0; i--) {
			// 		int d = (num >> (4*i)) & 0xF;
			// 		if (out && pos < n) {
			// 			out[pos] = (d < 10 ? '0'+d : 'a'+d-10);
			// 		}
			// 		pos++;
			// 	}
			// 	longarg = 0;
			// 	format = 0;
			// 	break;
			// }
			// case 'd': {
			// 	// long num = 123;
			// 	uart_puts("get %% d here\n");
			// 	long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
			// 	if (num < 0) {
			// 		num = -num;
			// 		if (out && pos < n) {
			// 			out[pos] = '-';
			// 		}
			// 		pos++;
			// 	}
			// 	long digits = 1;
			// 	for (long nn = num; nn /= 10; digits++);
			// 	for (int i = digits-1; i >= 0; i--) {
			// 		if (out && pos + i < n) {
			// 			out[pos + i] = '0' + (num % 10);
			// 		}
			// 		num /= 10;
			// 	}
			// 	pos += digits;
			// 	longarg = 0;
			// 	format = 0;
			// 	break;
			// }
			// case 's': {
			// 	const char* s2 = va_arg(vl, const char*);
			// 	while (*s2) {
			// 		if (out && pos < n) {
			// 			out[pos] = *s2;
			// 		}
			// 		pos++;
			// 		s2++;
			// 	}
			// 	longarg = 0;
			// 	format = 0;
			// 	break;
			// }
			// case 'c': {
			// 	uart_puts("get %% d here\n");
			// 	if (out && pos < n) {
			// 		out[pos] = (char)va_arg(vl,int);
			// 	}
			// 	pos++;
			// 	longarg = 0;
			// 	format = 0;
			// 	break;
			// }
			// default:
			// 	uart_puts("error: unknown format\n");
			// 	break;
			// }
		} else if (*s == '%') {
			format = 1;
			uart_puts("get %% here\n");
		} else {
			if (out && pos < n) {
				out[pos] = *s;
			}
			pos++;
		}
    	}
	uart_puts("stop here\n");
	if (out && pos < n) {
		out[pos] = 0;
	} else if (out && n) {
		out[n-1] = 0;
	}
	return pos;
}

static char out_buf[1000]; // buffer for _vprintf()

static int _vprintf(const char* s, va_list vl)
{
	// int res = 0;
	if(*s == '%'){
		uart_puts("_vprintf1_%%d: \n");
	}
	else{
		uart_puts("_vprintf1_hello: \n");
	}
	int res = _vsnprintf(NULL, -1, s, vl);
	if(*s == '%'){
		uart_puts("_vprintf2_%%d: \n");
	}
	else{
		uart_puts("_vprintf2_hello: \n");
	}
	if (res+1 >= sizeof(out_buf)) {
		uart_puts("error: output string size overflow\n");
		while(1) {}
	}
	_vsnprintf(out_buf, res + 1, s, vl);
	uart_puts(out_buf);
	return res;
}

int printf(const char* s, ...)
{
	int res = 0;
	va_list vl;
	uart_puts(s);
	va_start(vl, s);
	res = _vprintf(s, vl);
	va_end(vl);
	// uart_puts(s);
	// uart_puts("\n\n");
	return res;
}

void panic(char *s)
{
	printf("panic: ");
	printf(s);
	printf("\n");
	while(1){};
}

#ifndef LIB_CONSOLE_H_
#define LIB_CONSOLE_H_
#include <stdarg.h>
#include <arch/console.h>

int printf(const char *format, ...);
void puts(const char *str);
void putns(const char *str, int n);
void putd(const int num);
void putu(const unsigned num);
void putlu(unsigned long long num);
void putx(const unsigned num);
int getns(char *s, int size);

#endif /* LIB_CONSOLE_H_*/

#ifndef KERN_MEMORY_H
#define KERN_MEMORY_H
#include <lib/types.h>

size_t memory_init(void);
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void malloc_dump(void);
#endif

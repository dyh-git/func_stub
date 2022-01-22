#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

extern void malloc_free_so(size_t size);

void malloc_self(size_t size)
{
	printf("%s, %s, %d begin\n", __FILE__, __func__, __LINE__);
	malloc_free_so(size);
	printf("%s, %s, %d end\n", __FILE__, __func__, __LINE__);
	
	return;
}
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>

#define BUF_LENGTH	30

extern void malloc_free_so(size_t size);

#if 0 		/*编译的时候打桩*/
void wrap_malloc_free_sox(size_t size)
{
	printf("%s, %s, %d\n", __FILE__, __func__, __LINE__);
	malloc_free_so(size);
}

#define malloc_free_so(size)	wrap_malloc_free_sox(size)
#endif

void func_else(void)
{
	malloc_free_so(BUF_LENGTH);
	
	return;
}

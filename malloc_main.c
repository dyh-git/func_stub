#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>
#include <dlfcn.h>			/*运行时打桩*/

#define BUF_LENGTH	30

extern void malloc_free_so(size_t size);
extern void malloc_self(size_t size);
extern void func_else(void);
#if 0 		/*编译时打桩*/
void wrap_malloc_free_so(size_t size)
{
	printf("%s, %s, %d\n", __FILE__, __func__, __LINE__);
	malloc_free_so(size);
}

#define malloc_free_so(size)	wrap_malloc_free_so(size)
#endif

#if 0		/*链接时打桩*/
extern void __real_malloc_free_so(size_t size);

void __wrap_malloc_free_so(size_t size)
{
	printf("%s, %s, %d\n", __FILE__, __func__, __LINE__);
	__real_malloc_free_so(size);
}
#endif

#if 1		/*运行时打桩*/
typedef void (*malloc_t)(size_t size);
malloc_t malloc_f = NULL;

void malloc_free_so(size_t size)
{
	printf("%s, %s, %d\n", __FILE__, __func__, __LINE__);
	malloc_f(size);
	
	return;
}

static void wrap_init(void)
{
	void *handle = NULL;
	
	handle = dlopen("./output/libs/libmalloc0.so", RTLD_NOW);
	malloc_f = dlsym(handle, "malloc_free_so");
	if (!malloc_f)
		printf("error.%s\n", dlerror());
	
	return;
}
#endif

void func(void)
{
	malloc_free_so(BUF_LENGTH);
	malloc_self(BUF_LENGTH);
	
	return;
}

int main(int argc, char *argv[])
{	
	wrap_init();		/*运行时打桩*/
	func();
	func_else();
	
	return 0;	
}
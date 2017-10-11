#include <sys/mman.h>
#include <stdlib.h>

int		munmap_ptr(char *ptr, size_t size, int ret)
{
	munmap((void*)ptr, size);
	return (ret);
}

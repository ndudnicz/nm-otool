#include <sys/mman.h>
#include <stdlib.h>

int		munmap_ptr(char *ptr, size_t size, int ret)
{
	munmap((void*)ptr, size);
	return (ret);
}

int		free_all(void **array, int ret)
{
	size_t		i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
	return (ret);
}

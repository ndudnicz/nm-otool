#include "display.h"
#include "error.h"
#include <stdlib.h>
#include "sort.h"
#include "display_name.h"
#include "free.h"

static int	init_handle(t_handle *handle, char const *exec_name, char *ptr,
							char const *filename)
{
	handle->ptr = ptr;
	handle->filename = (char*)filename;
	handle->exec_name = (char*)exec_name;
	return (0);
}

int			handle_32(char const *exec_name, char *ptr,
							char const *filename, t_env *env)
{
	t_handle		handle;
	void			**array;

	array = NULL;
	if (ptr == NULL)
		return (0);
	if (init_handle(&handle, exec_name, ptr, filename) < 0)
		return (-1);
	handle.mmaped_size = env->mmaped_size;
	if (get_symbol_32(ptr, &handle, env->options, 0) < 0)
	{
		if (env->options & MULTI_FILE)
			display_name(filename, env->options, env->cputype, env->nfat_arch);
		return (free_all(array, -1));
	}
	else
	{
		if (!(array = sort(&(handle.list), env->options)))
			return (ft_error(exec_name, "Error", MALLOC_FAIL));
		if (!env->host_cputype)
			display_name(filename, env->options, env->cputype, env->nfat_arch);
		display(array, env->options);
		return (free_all(array, 0));
	}
}

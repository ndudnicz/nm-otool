#include "display_64.h"
#include "error.h"
#include <stdlib.h>
#include "sort_64.h"
#include "display_name.h"
#include "free.h"

static int	init_handle_64(t_handle_64 *handle_64, char const *exec_name,
							char *ptr, char const *filename)
{
	handle_64->ptr = ptr;
	handle_64->filename = (char*)filename;
	handle_64->exec_name = (char*)exec_name;
	return (0);
}

int			handle_64(char const *exec_name, char *ptr,
							char const *filename, t_env *env)
{
	t_handle_64		handle_64;
	void			**array;

	if (ptr == NULL)
		return (0);
	if (init_handle_64(&handle_64, exec_name, ptr, filename))
		return (-1);
	if (env->cputype == CPU_TYPE_X86_64 && env->host_cputype == 1)
		env->host_cputype = 2;
	handle_64.mmaped_size = env->mmaped_size;
	if (get_symbol_64(ptr, &handle_64, env->options, 0) < 0)
	{
		if (env->options & MULTI_FILE)
			display_name(filename, env->options, env->cputype, env->nfat_arch);
		return (free_all(NULL, -1));
	}
	else
	{
		if (!(array = sort_64(&(handle_64.list), env->options)))
			return (ft_error(exec_name, "Error", MALLOC_FAIL));
		if (!env->host_cputype)
			display_name(filename, env->options, env->cputype, env->nfat_arch);
		display_64(array, env->options);
		return (free_all(array, 0));
	}
}

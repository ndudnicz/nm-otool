#include "display_64.h"
#include "error.h"
#include <stdlib.h>
#include "display_name.h"
#include "nope.h"

static int	init_handle_64(t_handle_64 *handle_64, char const *exec_name,
							char const *filename)
{
	handle_64->filename = (char*)filename;
	handle_64->exec_name = (char*)exec_name;
	return (0);
}

int			handle_64(char const *exec_name, char *ptr,
							char const *filename, t_env *env)
{
	t_handle_64		handle_64;

	if (ptr == NULL)
		return (0);
	if (init_handle_64(&handle_64, exec_name, filename))
		return (-1);
	if (env->cputype == CPU_TYPE_X86_64 && env->host_cputype == 1)
		env->host_cputype = 2;
	handle_64.ptr = env->options & IS_FAT ? env->ptr : ptr;
	handle_64.mmaped_size = env->mmaped_size;
	handle_64.cputype = env->cputype;
	if (nope(ptr, ptr + sizeof(struct mach_header_64), handle_64.mmaped_size))
		return (-1);
	if (get_section_64(ptr, &handle_64, env->options, 0) < 0)
		return (-1);
	else
	{
		display_name_64(filename, env, &handle_64);
		display_64(handle_64.list, handle_64.addr, handle_64.cputype, 1);
		return (0);
	}
}

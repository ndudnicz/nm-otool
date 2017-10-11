#include "display.h"
#include "error.h"
#include <stdlib.h>
#include "display_name.h"
#include "nope.h"

static int	init_handle(t_handle *handle, char const *exec_name,
							char const *filename)
{
	handle->filename = (char*)filename;
	handle->exec_name = (char*)exec_name;
	return (0);
}

int			handle_32(char const *exec_name, char *ptr,
							char const *filename, t_env *env)
{
	t_handle		handle;

	if (ptr == NULL)
		return (0);
	if (init_handle(&handle, exec_name, filename))
		return (-1);
	handle.ptr = env->options & IS_FAT ? env->ptr : ptr;
	handle.mmaped_size = env->mmaped_size;
	handle.cputype = env->cputype;
	if (nope(ptr, ptr + sizeof(struct mach_header), handle.mmaped_size))
		return (-1);
	if (get_section_32(ptr, &handle, env->options, 0) < 0)
		return (-1);
	else
	{
		display_name(filename, env, &handle);
		display(handle.list, handle.addr, handle.cputype, 1);
		return (0);
	}
}

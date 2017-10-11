#include "handle.h"
#include "nope.h"

int		check_start_32(char *ptr, t_handle *handle)
{
	if (nope(handle->ptr, (void*)ptr + sizeof(struct mach_header),
	handle->mmaped_size))
		return (-1);
	else if (nope(handle->ptr, (void*)ptr + sizeof(struct mach_header) +
	sizeof(struct load_command), handle->mmaped_size))
		return (-1);
	else
		return (0);
}

#include "handle_64.h"
#include "nope.h"

int		check_start_64(char *ptr, t_handle_64 *handle_64)
{
	if (nope(handle_64->ptr, (void*)ptr + sizeof(struct mach_header_64),
	handle_64->mmaped_size))
		return (-1);
	else if (nope(handle_64->ptr, (void*)ptr + sizeof(struct mach_header_64) +
	sizeof(struct load_command), handle_64->mmaped_size))
		return (-1);
	else
		return (0);
}

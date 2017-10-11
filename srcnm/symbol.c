#include "env.h"
#include "handle.h"
#include <unistd.h>
#include "list_create.h"
#include "swap.h"
#include "nope.h"
#include "check_mmaped_data.h"

static int		get_symbol(char *ptr, t_handle *handle,
							struct symtab_command *sym)
{
	uint32_t			i;
	struct nlist		*elements;
	char				*stringtable;

	i = 0;
	elements = (void*)ptr + swapuint32(sym->symoff, handle->swap_needed);
	if (nope(handle->ptr, elements, handle->mmaped_size) ||
	nope(handle->ptr, ptr + swapuint32(sym->stroff, handle->swap_needed),
	handle->mmaped_size))
		return (-1);
	stringtable = (void*)ptr + swapuint32(sym->stroff, handle->swap_needed);
	while (i < swapuint32(sym->nsyms, handle->swap_needed))
	{
		if (nope(handle->ptr, &elements[i], handle->mmaped_size))
			return (-1);
		if (create_32(handle, &(elements[i]),
		stringtable + swapuint32(elements[i].n_un.n_strx,
		handle->swap_needed)) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static void		init_handle(t_handle *handle, char *ptr,
								unsigned char const options)
{
	handle->list = NULL;
	handle->header = (struct mach_header*)ptr;
	handle->lc = (void*)ptr + sizeof(*handle->header);
	handle->swap_needed = options & SWAP_NEEDED;
}

int				get_symbol_32(char *ptr, t_handle *handle,
								unsigned char const options, uint32_t i)
{
	struct load_command		*lc;

	if (check_start_32(ptr, handle))
		return (-1);
	init_handle(handle, ptr, options);
	lc = handle->lc;
	while (i < swapuint32(handle->header->ncmds, handle->swap_needed))
	{
		if (swapuint32(lc->cmd, handle->swap_needed) == LC_SYMTAB)
		{
			if (get_symbol(ptr, handle, (struct symtab_command*)lc) < 0)
				return (-1);
			else
				break ;
		}
		if (!swapuint32(lc->cmdsize, handle->swap_needed) ||
		nope(ptr, (void*)lc + swapuint32(lc->cmdsize, handle->swap_needed),
		handle->mmaped_size))
			return (-1);
		lc = (void*)lc + swapuint32(lc->cmdsize, handle->swap_needed);
		if (nope(ptr, lc + sizeof(struct load_command), handle->mmaped_size))
			return (-1);
		i++;
	}
	return (0);
}

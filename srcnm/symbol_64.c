#include "env.h"
#include "handle_64.h"
#include <unistd.h>
#include "list_create_64.h"
#include "swap.h"
#include "nope.h"
#include "check_mmaped_data_64.h"

static int		get_symbol(char *ptr, t_handle_64 *handle_64,
							struct symtab_command *sym)
{
	uint32_t			i;
	struct nlist_64		*elements;
	char				*stringtable;

	i = 0;
	elements = (void*)ptr + swapuint64(sym->symoff, handle_64->swap_needed);
	if (nope(handle_64->ptr, elements, handle_64->mmaped_size) ||
	nope(handle_64->ptr, ptr + swapuint32(sym->stroff, handle_64->swap_needed),
	handle_64->mmaped_size))
		return (-1);
	stringtable = (void*)ptr + swapuint64(sym->stroff, handle_64->swap_needed);
	while (i < swapuint64(sym->nsyms, handle_64->swap_needed))
	{
		if (nope(handle_64->ptr, &elements[i], handle_64->mmaped_size))
			return (-1);
		if (create_64(handle_64, &(elements[i]),
		stringtable + swapuint64(elements[i].n_un.n_strx,
		handle_64->swap_needed)) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static void		init_handle_64(t_handle_64 *handle_64, char *ptr,
								unsigned char const options)
{
	handle_64->list = NULL;
	handle_64->header = (struct mach_header_64*)ptr;
	handle_64->lc = (void*)ptr + sizeof(*handle_64->header);
	handle_64->swap_needed = options & SWAP_NEEDED;
}

int				get_symbol_64(char *ptr, t_handle_64 *handle_64,
								unsigned char const options, uint64_t i)
{
	struct load_command		*lc;

	if (check_start_64(ptr, handle_64))
		return (-1);
	init_handle_64(handle_64, ptr, options);
	lc = handle_64->lc;
	while (i < swapuint64(handle_64->header->ncmds, handle_64->swap_needed))
	{
		if (swapuint64(lc->cmd, handle_64->swap_needed) == LC_SYMTAB)
		{
			if (get_symbol(ptr, handle_64, (struct symtab_command*)lc) < 0)
				return (-1);
			else
				break ;
		}
		if (!swapuint64(lc->cmdsize, handle_64->swap_needed) ||
		nope(ptr, (void*)lc + swapuint64(lc->cmdsize, handle_64->swap_needed),
		handle_64->mmaped_size))
			return (-1);
		lc = (void*)lc + swapuint64(lc->cmdsize, handle_64->swap_needed);
		if (nope(ptr, lc + sizeof(struct load_command), handle_64->mmaped_size))
			return (-1);
		i++;
	}
	return (0);
}

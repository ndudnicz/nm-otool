#include "symbol.h"
#include "error.h"
#include "swap.h"
#include <stdlib.h>
#include "typedef.h"
#include "nope.h"
#include "list_create.h"
#include "libft.h"

static char		*parse_sections(t_handle *handle, uint8_t const n_sect,
									uint32_t i)
{
	t_box	b;

	b.lc = handle->lc;
	b.offset = 0;
	while (i < swapuint32(handle->header->ncmds, handle->swap_needed))
	{
		if (swapuint32(b.lc->cmd, handle->swap_needed) == LC_SEGMENT)
		{
			b.section = (struct section*)((char*)b.lc + sizeof(t_sc));
			if (n_sect < b.offset + swapuint32(((t_sc*)b.lc)->nsects,
			handle->swap_needed))
				return (b.section[n_sect - b.offset].sectname);
			b.offset += swapuint32(((t_sc*)b.lc)->nsects, handle->swap_needed);
		}
		if (!swapuint32(b.lc->cmdsize, handle->swap_needed))
			return ("error");
		b.lc = (void*)b.lc + swapuint32(b.lc->cmdsize,
			handle->swap_needed);
		if (nope(handle->ptr, b.lc + sizeof(t_lc), handle->mmaped_size))
			return ("error");
		i++;
	}
	return (NULL);
}

/*
** Sources:
** - https://sourceware.org/binutils/docs/binutils/nm.html
** - mach-o/nlist.h
*/

static char		sub_get_type(uint8_t n_type, uint32_t n_value)
{
	if ((n_type & N_TYPE) == N_INDR)
		return (!(n_type & N_EXT) ? 'i' : 'I');
	else if ((n_type & N_TYPE) == N_STAB)
		return ('-');
	else if ((n_type & N_TYPE) == N_UNDF && (n_type & N_EXT) && n_value != 0)
		return ('C');
	else if (((n_type & N_TYPE) == N_UNDF && (n_type & N_TYPE) == N_PBUD) ||
	(n_type & N_TYPE) == N_UNDF)
		return (!(n_type & N_EXT) ? 'u' : 'U');
	else if ((n_type & N_TYPE) == N_ABS)
		return (!(n_type & N_EXT) ? 'a' : 'A');
	else
		return (0);
}

static char		get_type(t_handle *handle, uint8_t const n_type,
							uint32_t const n_value, uint8_t const n_sect)
{
	char	*sect_name;
	char	t;

	if ((t = sub_get_type(n_type, n_value)))
		return (t);
	sect_name = parse_sections(handle, n_sect - 1, 0);
	if (sect_name && !ft_strcmp(sect_name, "error"))
		return (-1);
	if ((n_type & N_TYPE) == N_SECT)
	{
		if (sect_name && (!ft_strcmp(sect_name, SECT_TEXT) ||
			!ft_strcmp(sect_name, SECT_BSS) ||
			!ft_strcmp(sect_name, SECT_DATA)))
			t = !(n_type & N_EXT) ? sect_name[2] : ft_toupper(sect_name[2]);
		else
			t = 'S';
	}
	return (t && !(n_type & N_EXT) ? ft_tolower(t) : t);
}

static int		init_and_push(t_handle *handle, t_symbol *new,
								struct nlist *elem, char const *name)
{
	t_symbol	*tmp;

	new->name = (char*)name;
	new->value = swapuint32(elem->n_value, handle->swap_needed);
	new->type = get_type(handle, elem->n_type, new->value, elem->n_sect);
	if (new->type < 0)
		return (-1);
	new->next = NULL;
	tmp = handle->list;
	if (tmp == NULL)
		handle->list = new;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int				create_32(t_handle *handle, struct nlist *elem,
							char const *name)
{
	t_symbol	*new;

	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return (ft_error(handle->exec_name, "Error", MALLOC_FAIL));
	if (init_and_push(handle, new, elem, name) < 0)
		return (-1);
	return (0);
}

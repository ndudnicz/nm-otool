#include "symbol_64.h"
#include "error.h"
#include "swap.h"
#include <stdlib.h>
#include "typedef.h"
#include "nope.h"
#include "list_create_64.h"
#include "libft.h"

static char		*parse_sections(t_handle_64 *handle_64, uint8_t const n_sect,
									uint32_t i)
{
	t_box_64	b;

	b.lc = handle_64->lc;
	b.offset = 0;
	while (i < swapuint32(handle_64->header->ncmds, handle_64->swap_needed))
	{
		if (swapuint32(b.lc->cmd, handle_64->swap_needed) == LC_SEGMENT_64)
		{
			b.section = (struct section_64*)((char*)b.lc +
				sizeof(t_sc64));
			if (n_sect < b.offset + swapuint64(((t_sc64*)b.lc)->nsects,
				handle_64->swap_needed))
				return (b.section[n_sect - b.offset].sectname);
			b.offset += swapuint64(((t_sc64*)b.lc)->nsects,
				handle_64->swap_needed);
		}
		if (!swapuint32(b.lc->cmdsize, handle_64->swap_needed))
			return ("error");
		b.lc = (struct load_command*)((char*)b.lc + swapuint64(b.lc->cmdsize,
			handle_64->swap_needed));
		if (nope(handle_64->ptr, b.lc + sizeof(t_lc), handle_64->mmaped_size))
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

static char		sub_get_type(uint8_t n_type, uint64_t n_value)
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

static char		get_type(t_handle_64 *handle_64, uint8_t n_type,
							uint64_t n_value, uint8_t n_sect)
{
	char	*sect_name;
	char	t;

	if ((t = sub_get_type(n_type, n_value)))
		return (t);
	if ((n_type & N_TYPE) == N_SECT)
	{
		sect_name = parse_sections(handle_64, n_sect - 1, 0);
		if (sect_name && !ft_strcmp(sect_name, "error"))
			return (-1);
		if (sect_name && (!ft_strcmp(sect_name, SECT_TEXT) ||
			!ft_strcmp(sect_name, SECT_BSS) ||
			!ft_strcmp(sect_name, SECT_DATA)))
			t = !(n_type & N_EXT) ? sect_name[2] : ft_toupper(sect_name[2]);
		else
			t = 'S';
	}
	return (t && !(n_type & N_EXT) ? ft_tolower(t) : t);
}

static int		init_and_push(t_handle_64 *handle_64, t_symbol_64 *new,
						struct nlist_64 *elem, char const *name)
{
	t_symbol_64	*tmp;

	new->name = (char*)name;
	new->value = swapuint64(elem->n_value, handle_64->swap_needed);
	new->type = get_type(handle_64, elem->n_type, elem->n_value, elem->n_sect);
	if (new->type < 0)
		return (-1);
	new->next = NULL;
	tmp = handle_64->list;
	if (tmp == NULL)
		handle_64->list = new;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int				create_64(t_handle_64 *handle_64, struct nlist_64 *elem,
							char const *name)
{
	t_symbol_64	*new;

	if (!(new = (t_symbol_64*)malloc(sizeof(t_symbol_64))))
		return (ft_error(handle_64->exec_name, "Error", MALLOC_FAIL));
	if (init_and_push(handle_64, new, elem, name) < 0)
		return (-1);
	return (0);
}

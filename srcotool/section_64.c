#include "env.h"
#include <unistd.h>
#include "list_create_64.h"
#include "swap.h"
#include "nope.h"
#include "check_mmaped_data_64.h"
#include "typedef.h"
#include "section_64.h"
#include "libft.h"

static int		get_section(uint32_t const *ptr, t_handle_64 *handle_64)
{
	uint32_t		i;
	uint32_t		mod;
	uint32_t const	mask[4] = {0x000000ff, 0x0000ffff, 0x00ffffff, 0xffffffff};

	i = 0;
	mod = handle_64->size % sizeof(uint32_t);
	while (i < handle_64->size / sizeof(uint32_t))
	{
		if (create_64(handle_64, swapuint32((uint32_t)ptr[i],
		handle_64->swap_needed), mask[3]) < 0)
			return (-1);
		i += 1;
	}
	if (mod && create_64(handle_64, swapuint32(mask[mod - 1] & (uint32_t)ptr[i],
	handle_64->swap_needed), mask[mod - 1]) < 0)
		return (-1);
	return (0);
}

static int		init_handle(t_handle_64 *handle_64, char *ptr,
								unsigned char const options)
{
	if (check_start_64(ptr, handle_64))
		return (-1);
	handle_64->list = NULL;
	handle_64->header = (struct mach_header_64*)ptr;
	handle_64->cputype = options & IS_FAT ?
	handle_64->cputype : handle_64->header->cputype;
	handle_64->lc = (void*)ptr + sizeof(struct mach_header_64);
	handle_64->swap_needed = options & SWAP_NEEDED;
	return (0);
}

static int		set_handle_get_sect(char *ptr, uint32_t *sub_ptr,
										t_handle_64 *handle_64,
										struct section_64 *section)
{
	if (!ft_strcmp(SECT_TEXT, section->sectname))
	{
		handle_64->sectname = section->sectname;
		handle_64->segname = section->segname;
		handle_64->addr = swapuint64(section->addr, handle_64->swap_needed);
		handle_64->size = swapuint64(section->size, handle_64->swap_needed);
		if (nope(handle_64->ptr, (void*)((char*)ptr + handle_64->size),
		handle_64->mmaped_size))
			return (-1);
		if (get_section(sub_ptr, handle_64) < 0)
			return (-1);
	}
	return (0);
}

static int		set_section(char *ptr, t_handle_64 *handle_64, t_box_64 *b,
							uint32_t *i)
{
	if (nope(handle_64->ptr, (void*)((char*)b->lc +
	sizeof(t_sc64)), handle_64->mmaped_size))
		return (-1);
	b->section = (struct section_64*)((char*)b->lc + sizeof(t_sc64));
	if (nope(handle_64->ptr, handle_64->ptr +
	swapuint32(b->section->offset, handle_64->swap_needed),
	handle_64->mmaped_size))
		return ((*i)++);
	b->sub_ptr = (uint32_t*)(ptr +
	swapuint32(b->section->offset, handle_64->swap_needed));
	return (0);
}

int				get_section_64(char *ptr, t_handle_64 *handle_64,
								unsigned char const options, uint32_t i)
{
	t_box_64	b;

	if (init_handle(handle_64, ptr, options) < 0)
		return (-1);
	b.lc = handle_64->lc;
	while (i < swapuint32(handle_64->header->ncmds, handle_64->swap_needed))
	{
		if (swapuint32(b.lc->cmd, handle_64->swap_needed) == LC_SEGMENT_64)
		{
			if ((b.ret = set_section(ptr, handle_64, &b, &i)) < 0)
				return (-1);
			else if (b.ret > 0)
				continue ;
			if (set_handle_get_sect(ptr, b.sub_ptr, handle_64, b.section) < 0)
				return (-1);
		}
		if (nope(handle_64->ptr, (void*)((char*)b.lc +
		swapuint32(b.lc->cmdsize, handle_64->swap_needed)),
		handle_64->mmaped_size))
			return (-1);
		b.lc = (struct load_command*)((char*)b.lc +
		swapuint32(b.lc->cmdsize, handle_64->swap_needed));
		i++;
	}
	return (0);
}

#include "env.h"
#include <unistd.h>
#include "list_create.h"
#include "swap.h"
#include "typedef.h"
#include "nope.h"
#include "section.h"
#include "check_mmaped_data.h"
#include "libft.h"

static int		get_section(uint32_t const *ptr, t_handle *handle)
{
	uint32_t		i;
	uint32_t		mod;
	uint32_t const	mask[4] = {0x000000ff, 0x0000ffff, 0x00ffffff, 0xffffffff};

	i = 0;
	mod = handle->size % sizeof(uint32_t);
	while (i < handle->size / sizeof(uint32_t))
	{
		if (create_32(handle, swapuint32((uint32_t)ptr[i],
						handle->swap_needed), mask[3]) < 0)
			return (-1);
		i += 1;
	}
	if (mod && create_32(handle, swapuint32(mask[mod - 1] & (uint32_t)ptr[i],
	handle->swap_needed), mask[mod - 1]) < 0)
		return (-1);
	return (0);
}

static int		init_handle(t_handle *handle, char *ptr,
								unsigned char const options)
{
	if (check_start_32(ptr, handle))
		return (-1);
	handle->list = NULL;
	handle->header = (struct mach_header*)ptr;
	handle->cputype = options & IS_FAT ?
	handle->cputype : handle->header->cputype;
	handle->lc = (void*)ptr + sizeof(struct mach_header);
	handle->swap_needed = options & SWAP_NEEDED;
	return (0);
}

static int		set_handle_get_sect(char *ptr, uint32_t *sub_ptr,
										t_handle *handle,
										struct section *section)
{
	if (!ft_strcmp(SECT_TEXT, section->sectname))
	{
		handle->sectname = section->sectname;
		handle->segname = section->segname;
		handle->addr = swapuint32(section->addr, handle->swap_needed);
		handle->size = swapuint32(section->size, handle->swap_needed);
		if (nope(handle->ptr, (void*)((char*)ptr + handle->size),
		handle->mmaped_size))
			return (-1);
		if (get_section(sub_ptr, handle) < 0)
			return (-1);
	}
	return (0);
}

static int		set_section(char *ptr, t_handle *handle, t_box *b,
							uint32_t *i)
{
	if (nope(handle->ptr, (void*)((char*)b->lc +
	sizeof(t_sc)), handle->mmaped_size))
		return (-1);
	b->section = (struct section*)((char*)b->lc + sizeof(t_sc));
	if (nope(handle->ptr, handle->ptr +
	swapuint32(b->section->offset, handle->swap_needed),
	handle->mmaped_size))
		return ((*i)++);
	b->sub_ptr = (uint32_t*)(ptr +
	swapuint32(b->section->offset, handle->swap_needed));
	return (0);
}

int				get_section_32(char *ptr, t_handle *handle,
								unsigned char const options, uint32_t i)
{
	t_box	b;

	if (init_handle(handle, ptr, options) < 0)
		return (-1);
	b.lc = handle->lc;
	while (i < swapuint32(handle->header->ncmds, handle->swap_needed))
	{
		if (swapuint32(b.lc->cmd, handle->swap_needed) == LC_SEGMENT)
		{
			if ((b.ret = set_section(ptr, handle, &b, &i)) < 0)
				return (-1);
			else if (b.ret > 0)
				continue ;
			if (set_handle_get_sect(ptr, b.sub_ptr, handle, b.section) < 0)
				return (-1);
		}
		if (nope(handle->ptr, (void*)((char*)b.lc +
		swapuint32(b.lc->cmdsize, handle->swap_needed)),
		handle->mmaped_size))
			return (-1);
		b.lc = (struct load_command*)((char*)b.lc +
		swapuint32(b.lc->cmdsize, handle->swap_needed));
		i++;
	}
	return (0);
}

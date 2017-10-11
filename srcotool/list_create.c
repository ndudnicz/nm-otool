#include "section.h"
#include "error.h"
#include "swap.h"
#include <stdlib.h>
#include "typedef.h"
#include "nope.h"
#include "list_create.h"

static int	init_and_push(t_handle *handle, t_section *new,
							uint32_t const data, uint32_t const mask)
{
	t_section	*tmp;

	if (handle->cputype == CPU_TYPE_ARM)
		new->data = swapuint32(data, 1);
	else
		new->data = swapuint32(data, handle->swap_needed);
	new->next = NULL;
	new->mask = mask;
	tmp = handle->list;
	if (tmp == NULL)
	{
		new->last = new;
		handle->list = new;
	}
	else
	{
		tmp->last->next = new;
		tmp->last = new;
	}
	return (0);
}

int			create_32(t_handle *handle, uint32_t const data,
						uint32_t const mask)
{
	t_section	*new;

	if (!(new = (t_section*)malloc(sizeof(t_section))))
		return (ft_error(handle->exec_name, "Error", MALLOC_FAIL));
	init_and_push(handle, new, data, mask);
	return (0);
}

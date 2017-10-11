#include "section_64.h"
#include "error.h"
#include "swap.h"
#include <stdlib.h>
#include "typedef.h"
#include "nope.h"
#include "list_create_64.h"

static int		init_and_push(t_handle_64 *handle_64, t_section_64 *new,
								uint32_t const data, uint32_t const mask)
{
	t_section_64	*tmp;

	new->data = swapuint32(data, handle_64->swap_needed);
	new->next = NULL;
	new->last = NULL;
	new->mask = mask;
	tmp = handle_64->list;
	if (tmp == NULL)
	{
		new->last = new;
		handle_64->list = new;
	}
	else
	{
		tmp->last->next = new;
		tmp->last = new;
	}
	return (0);
}

int				create_64(t_handle_64 *handle_64, uint32_t const data,
							uint32_t const mask)
{
	t_section_64	*new;

	if (!(new = (t_section_64*)malloc(sizeof(t_section_64))))
		return (ft_error(handle_64->exec_name, "Error", MALLOC_FAIL));
	init_and_push(handle_64, new, data, mask);
	return (0);
}

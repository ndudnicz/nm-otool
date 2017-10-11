#ifndef LIST_CREATE_H
# define LIST_CREATE_H

# include "handle.h"

typedef struct	s_box
{
	struct load_command		*lc;
	struct section			*section;
	uint32_t				offset;
}				t_box;

int				create_32(t_handle *handle, struct nlist *elem,
							char const *name);

#endif

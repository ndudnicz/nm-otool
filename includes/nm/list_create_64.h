#ifndef LIST_CREATE_64_H
# define LIST_CREATE_64_H

# include "handle_64.h"

typedef struct	s_box_64
{
	struct load_command		*lc;
	struct section_64		*section;
	uint64_t				offset;
}				t_box_64;

int				create_64(t_handle_64 *handle_64, struct nlist_64 *elem,
							char const *name);

#endif

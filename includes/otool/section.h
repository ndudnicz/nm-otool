#ifndef SECTION_H
# define SECTION_H

# include "handle.h"

typedef struct	s_box
{
	int						ret;
	uint32_t				*sub_ptr;
	struct load_command		*lc;
	struct section			*section;
}				t_box;

typedef struct	s_section
{
	uint32_t			data;
	uint32_t			mask;
	struct s_section	*last;
	struct s_section	*next;
}				t_section;

int				get_section_32(char *ptr, t_handle *handle,
								unsigned char const options, uint32_t i);

#endif

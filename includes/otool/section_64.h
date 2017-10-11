#ifndef SECTION_64_H
# define SECTION_64_H

# include "handle_64.h"

typedef struct	s_box_64
{
	int						ret;
	uint32_t				*sub_ptr;
	struct load_command		*lc;
	struct section_64		*section;
}				t_box_64;

typedef struct	s_section_64
{
	uint32_t			data;
	uint32_t			mask;
	struct s_section_64	*last;
	struct s_section_64	*next;
}				t_section_64;

int				get_section_64(char *ptr, t_handle_64 *handle_64,
								unsigned char const options, uint32_t i);

#endif

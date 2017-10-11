#ifndef HANDLE_64_H
# define HANDLE_64_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "env.h"

typedef struct	s_handle_64
{
	unsigned char			swap_needed;
	int						cputype;
	char					*exec_name;
	char					*filename;
	char					*sectname;
	char					*segname;
	void					*ptr;
	uint64_t				addr;
	uint64_t				size;
	unsigned long int		mmaped_size;
	struct s_section_64		*list;
	struct mach_header_64	*header;
	struct load_command		*lc;
}				t_handle_64;

int				handle_64(char const *exec_name, char *ptr,
							char const *filename, t_env *env);

#endif

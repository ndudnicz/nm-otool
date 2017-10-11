#ifndef HANDLE_H
# define HANDLE_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "env.h"

typedef struct	s_handle
{
	unsigned char			swap_needed;
	int						cputype;
	char					*exec_name;
	char					*filename;
	char					*sectname;
	char					*segname;
	uint32_t				addr;
	uint32_t				size;
	void					*ptr;
	unsigned long int		mmaped_size;
	struct s_section		*list;
	struct mach_header		*header;
	struct load_command		*lc;
}				t_handle;

int				handle_32(char const *exec_name, char *ptr,
							char const *filename, t_env *env);

#endif

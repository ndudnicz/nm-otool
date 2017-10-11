#ifndef HANDLE_H
# define HANDLE_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "env.h"

typedef struct				s_handle
{
	unsigned char			swap_needed;
	char					*exec_name;
	char					*filename;
	int						cputype;
	void					*ptr;
	long int				mmaped_size;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct s_symbol			*list;
}							t_handle;

int							handle_32(char const *exec_name, char *ptr,
										char const *filename, t_env *env);

#endif

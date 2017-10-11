#ifndef HANDLE_64_H
# define HANDLE_64_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "env.h"

typedef struct				s_handle_64
{
	unsigned char			swap_needed;
	char					*exec_name;
	char					*filename;
	int						cputype;
	void					*ptr;
	long int				mmaped_size;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct s_symbol_64		*list;
}							t_handle_64;

int							handle_64(char const *exec_name, char *ptr,
										char const *filename, t_env *env);

#endif

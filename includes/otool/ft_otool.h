#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# define PREAD PROT_READ
# define PPRIVATE MAP_PRIVATE

# include "env.h"

int		open_file(char const *exec_name, char const *filename, t_env *env);
int		iter_open_file(int const ac, char **av, t_env *env);
int		map_file(char const *exec_name, char const *filename,
					int const fd, t_env *env);

#endif

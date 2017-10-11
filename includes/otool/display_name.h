#ifndef DISPLAY_NAME_H
# define DISPLAY_NAME_H

# include "handle.h"
# include "handle_64.h"

void	display_name(char const *filename, t_env *env,
						t_handle *handle);
void	display_name_64(char const *filename, t_env *env,
							t_handle_64 *handle_64);

#endif

#ifndef SYMBOL_64_H
# define SYMBOL_64_H

# include "handle_64.h"

typedef struct			s_symbol_64
{
	char				type;
	uint64_t			value;
	char				*name;
	struct s_symbol_64	*next;
}						t_symbol_64;

int						get_symbol_64(char *ptr, t_handle_64 *handle_64,
										unsigned char const option, uint64_t i);

#endif

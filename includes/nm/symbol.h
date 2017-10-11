#ifndef SYMBOL_H
# define SYMBOL_H

# include "handle.h"

typedef struct			s_symbol
{
	char				type;
	uint32_t			value;
	char				*name;
	struct s_symbol		*next;
}						t_symbol;

int						get_symbol_32(char *ptr, t_handle *handle,
									unsigned char const options, uint32_t i);

#endif

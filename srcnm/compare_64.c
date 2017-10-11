#include "symbol_64.h"
#include "libft.h"

int		compare_alpha_64(t_symbol_64 *a, t_symbol_64 *b)
{
	int		cmp;

	cmp = ft_strcmp(a->name, b->name);
	return (cmp < 0 || (!cmp && a->value < b->value));
}

int		compare_num_64(t_symbol_64 *a, t_symbol_64 *b)
{
	uint64_t	va;
	uint64_t	vb;

	va = ft_tolower(a->type) == 't' && !a->value ? 1 : a->value;
	vb = ft_tolower(b->type) == 't' && !b->value ? 1 : b->value;
	return (va || vb ? va < vb : compare_alpha_64(a, b));
}

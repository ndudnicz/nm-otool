#include "symbol.h"
#include "libft.h"

int		compare_alpha(t_symbol *a, t_symbol *b)
{
	int		cmp;

	cmp = ft_strcmp(a->name, b->name);
	return (cmp < 0 || (!cmp && a->value < b->value));
}

int		compare_num(t_symbol *a, t_symbol *b)
{
	uint32_t	va;
	uint32_t	vb;

	va = ft_tolower(a->type) == 't' && !a->value ? 1 : a->value;
	vb = ft_tolower(b->type) == 't' && !b->value ? 1 : b->value;
	return (va || vb ? va < vb : compare_alpha(a, b));
}

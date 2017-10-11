#include "symbol.h"
#include "symbol_64.h"

int		ft_list_len(t_symbol **begin)
{
	t_symbol	*tmp;
	int			n;

	tmp = *begin;
	n = 0;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

int		ft_list_len_64(t_symbol_64 **begin)
{
	t_symbol_64	*tmp;
	int			n;

	tmp = *begin;
	n = 0;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

#include "list_len.h"
#include <stdlib.h>
#include "swap.h"
#include "compare.h"

static void		fill_array(t_symbol **begin, void **array)
{
	t_symbol	*tmp;
	int			i;

	tmp = *begin;
	i = 0;
	while (tmp)
	{
		array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
}

/*
** Source: https://en.wikipedia.org/wiki/Quicksort
*/

static int		partition(void **array, int start, int end,
							int (*compare)(t_symbol*, t_symbol*))
{
	int		j;
	int		i;
	void	*pivot;

	pivot = array[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (compare((t_symbol*)array[j], (t_symbol*)pivot))
		{
			i++;
			swap(&array[i], &array[j]);
		}
		j++;
	}
	if (compare((t_symbol*)array[end], (t_symbol*)array[i + 1]))
		swap(&array[i + 1], &array[end]);
	return (i + 1);
}

static void		quick_sort(void **array, int start, int end,
							int (*compare)(t_symbol*, t_symbol*))
{
	int		pivot;

	if (start < end)
	{
		pivot = partition(array, start, end, compare);
		quick_sort(array, start, pivot - 1, compare);
		quick_sort(array, pivot + 1, end, compare);
	}
}

void			**sort(t_symbol **begin, unsigned char const options)
{
	void	**array;
	int		list_len;

	list_len = ft_list_len(begin);
	if (!(array = (void**)malloc(sizeof(void*) * (list_len + 1))))
		return (NULL);
	fill_array(begin, array);
	if (options & NO_SORT)
		return (array);
	else if (options & SORT_NUM)
		quick_sort(array, 0, list_len - 1, &compare_num);
	else
		quick_sort(array, 0, list_len - 1, &compare_alpha);
	return (array);
}

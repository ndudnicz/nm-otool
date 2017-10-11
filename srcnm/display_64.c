#include "display_64.h"
#include <stdio.h>
#include "libft.h"

static void	print_value(t_symbol_64 const *tmp, unsigned char const options)
{
	if ((long)tmp->value)
	{
		if (!(options & ONLY_SYM_NAME))
			printf("%016lx %c %s\n", (long)tmp->value, tmp->type, tmp->name);
	}
	else
	{
		if ((tmp->type == 't' || tmp->type == 'T' ||
		tmp->type == 'a' || tmp->type == 'A') &&
		(!(options & ONLY_UNDEFINED) && !(options & ONLY_SYM_NAME)))
			printf("0000000000000000 %c %s\n", tmp->type, tmp->name);
		else if (!(options & ONLY_UNDEFINED) && !(options & ONLY_SYM_NAME))
			printf("%16c %c %s\n", ' ', tmp->type, tmp->name);
	}
}

void		display_64(void **array, unsigned char const options)
{
	int				i;
	t_symbol_64		*tmp;

	i = 0;
	while (array && array[i])
	{
		tmp = (t_symbol_64*)array[i];
		if (!tmp->name || !ft_strlen(tmp->name) ||
		(tmp->type == 'u') ||
		(options & ONLY_UNDEFINED && 'u' != ft_tolower(tmp->type)) ||
		(options & NO_UNDEFINED && 'u' == ft_tolower(tmp->type)) || !tmp->type)
		{
			i++;
			continue ;
		}
		else
		{
			print_value(tmp, options);
			i++;
		}
	}
}

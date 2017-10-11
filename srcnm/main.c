#include "ft_nm.h"
#include "env.h"
#include "options_handling.h"
#include "libft.h"

static int		print_usage(void)
{
	ft_putendl("\nUSAGE: ./ft_nm [options] <input files>\n");
	ft_putendl("General options:\n");
	ft_putendl("\t-n\t Sort numerically rather than alphabetically.\n");
	ft_putendl("\t-u\t Display only undefined symbols.\n");
	ft_putendl("\t-U\t Don't display undefined symbols.\n");
	ft_putendl("\t-j\t Just display the symbol names (no value or type).\n");
	ft_putendl("\t-p\t Don't sort; display in symbol-table order.\n");
	return (-1);
}

int				main(int ac, char **av)
{
	t_env	env;

	init_env(&env);
	if (get_options(&env, &ac, av) < 0)
		return (print_usage());
	if (ac < 2)
		open_file(av[0], "a.out", &env);
	else
	{
		env.options |= ac > 2 ? MULTI_FILE : 0x00;
		iter_open_file(ac, av, &env);
	}
	return (0);
}

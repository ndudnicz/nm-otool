#include "ft_otool.h"
#include "env.h"
#include "error.h"
#include "libft.h"

static int		print_usage(void)
{
	ft_error("error", "ft_otool", NO_INPUT_OBJECT_FILE);
	ft_putstr("Usage: ./ft_otool <object file>\n");
	return (-1);
}

int				main(int ac, char **av)
{
	t_env	env;

	init_env(&env);
	if (ac < 2)
		return (print_usage());
	else
	{
		env.options |= ac > 2 ? MULTI_FILE : 0x00;
		return (iter_open_file(ac, av, &env));
	}
	return (0);
}

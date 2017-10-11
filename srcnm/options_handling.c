#include "env.h"
#include "error.h"
#include "libft.h"

static void	del_null_params(int const ac, char **av)
{
	int		i;
	int		n;
	char	*tmp;

	n = 1;
	while (n < ac)
	{
		i = 1;
		while (i < ac - 1)
		{
			if (av[i] == NULL)
			{
				tmp = av[i];
				av[i] = av[i + 1];
				av[i + 1] = tmp;
			}
			i++;
		}
		n++;
	}
}

static int	set_options(char *arg, t_env *env)
{
	arg += arg ? 1 : 0;
	while (arg && *arg)
	{
		if (*arg && ft_strchr(PARAMS_STR, (int)(*arg)))
		{
			env->options |= *arg == SORT_NUM_CHAR ? SORT_NUM : 0x00;
			env->options |= *arg == ONLY_UNDEFINED_CHAR ? ONLY_UNDEFINED : 0x00;
			env->options |= *arg == NO_UNDEFINED_CHAR ? NO_UNDEFINED : 0x00;
			env->options |= *arg == NO_SORT_CHAR ? NO_SORT : 0x00;
			env->options |= *arg == ONLY_SYM_NAME_CHAR ? ONLY_SYM_NAME : 0x00;
		}
		else
			return (-1);
		arg++;
	}
	return (0);
}

int			get_options(t_env *env, int *ac, char **av)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	while (i < *ac)
	{
		if (av[i][0] == '-')
		{
			if (set_options(av[i], env) < 0)
				return (ft_error(av[0], "", UNKNOW_ARG));
			av[i] = NULL;
			n++;
		}
		i++;
	}
	del_null_params(*ac, av);
	*ac -= n;
	return (0);
}

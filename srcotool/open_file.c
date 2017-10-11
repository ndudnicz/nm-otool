#include "ft_otool.h"
#include "error.h"
#include <unistd.h>
#include <fcntl.h>

int		open_file(char const *exec_name, char const *filename, t_env *env)
{
	int		fd;
	int		ret;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ft_error(exec_name, filename, BAD_FILENAME));
	ret = map_file(exec_name, filename, fd, env);
	return (close(fd) < 0 ? ft_error(exec_name, filename, CLOSE_FAILED) : ret);
}

int		iter_open_file(int const ac, char **av, t_env *env)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		hard_reset_env(env);
		if (open_file(av[0], av[i], env) < 0)
			return (-1);
		i++;
	}
	return (0);
}

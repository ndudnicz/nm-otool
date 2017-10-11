#include "ft_nm.h"
#include "error.h"
#include <fcntl.h>
#include <unistd.h>

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
		open_file(av[0], av[i], env);
		i++;
	}
	return (0);
}

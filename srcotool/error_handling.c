#include "error.h"
#include "ft_otool.h"
#include <stdlib.h>
#include "libft.h"

int		ft_error(char const *exec_name, char const *filename, char const *type)
{
	char	*joined_msg;

	if (!(joined_msg = ft_strjoin(filename, type)))
		return (ft_putstr_fd(MALLOC_FAIL, 2));
	ft_putstr_fd(exec_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(joined_msg, 2);
	ft_putstr_fd("\n", 2);
	free(joined_msg);
	return (-1);
}

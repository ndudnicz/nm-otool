#include "display_arch.h"
#include "env.h"
#include "handle.h"
#include "handle_64.h"
#include <stdio.h>
#include "libft.h"

void	display_name(char const *filename, t_env *env, t_handle *handle)
{
	printf("%s", filename);
	if (env->options & IS_FAT && !env->host_cputype)
		printf("%s%s%s\n", " (architecture ", display_arch(env->cputype), "):");
	else
		printf(":\n");
	printf("Contents of (%s,%s) section\n",
			handle->segname, handle->sectname);
}

void	display_name_64(char const *filename, t_env *env,
						t_handle_64 *handle_64)
{
	printf("%s", filename);
	if (env->options & IS_FAT && !env->host_cputype)
	{
		printf("%s%s%s\n", " (architecture ", display_arch(env->cputype), "):");
	}
	else
		printf(":\n");
	printf("Contents of (%s,%s) section\n",
			handle_64->segname, handle_64->sectname);
}

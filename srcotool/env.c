#include "env.h"
#include <stdlib.h>

void	init_env(t_env *env)
{
	env->options = 0;
	env->host_cputype = 0;
	env->cputype = 0;
	env->mmaped_size = 0;
	env->ptr = NULL;
}

void	soft_reset_env(t_env *env)
{
	env->options &= (IS_FAT | MULTI_FILE);
}

void	hard_reset_env(t_env *env)
{
	env->options &= MULTI_FILE;
	env->host_cputype = 0;
	env->cputype = 0;
	env->mmaped_size = 0;
	env->ptr = NULL;
}

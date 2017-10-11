#include "env.h"

void	init_env(t_env *env)
{
	env->options = 0;
	env->host_cputype = 0;
	env->nfat_arch = 0;
	env->cputype = 0;
	env->mmaped_size = 0;
}

void	soft_reset_env(t_env *env)
{
	env->options &= (IS_FAT | MULTI_FILE |
					SORT_NUM |
					NO_SORT |
					NO_UNDEFINED |
					ONLY_UNDEFINED |
					ONLY_SYM_NAME);
}

void	hard_reset_env(t_env *env)
{
	env->options &= (MULTI_FILE |
					SORT_NUM |
					NO_SORT |
					NO_UNDEFINED |
					ONLY_UNDEFINED |
					ONLY_SYM_NAME);
	env->host_cputype = 0;
	env->nfat_arch = 0;
	env->cputype = 0;
	env->mmaped_size = 0;
}

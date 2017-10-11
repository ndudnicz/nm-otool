#include "env.h"
#include "error.h"
#include "swap.h"
#include "handle.h"
#include "handle_64.h"
#include "handle_fat.h"
#include "typedef.h"
#include <mach-o/fat.h>
#include <stdlib.h>
#include "nope.h"

static int	get_all_cputypes(char *ptr, t_env *env)
{
	t_fh		*fat_header;
	uint32_t	i;

	i = 0;
	env->options |= IS_FAT;
	if (nope(ptr, (void*)ptr + sizeof(t_fh), env->mmaped_size))
		return (-1);
	fat_header = (t_fh*)((void*)(ptr));
	env->nfat_arch = swapuint32(fat_header->nfat_arch, 1);
	while (i < swapuint32(fat_header->nfat_arch, 1))
	{
		if (nope(ptr, (t_fa*)((void*)(ptr) + sizeof(t_fh) + sizeof(t_fa) * i),
		env->mmaped_size))
			return (-1);
		if ((int)(swapuint32(((t_fa*)((void*)(ptr) + sizeof(t_fh) +
		sizeof(t_fa) * i))->cputype, 1)) == CPU_TYPE_X86_64)
			return (env->host_cputype = 1);
		i++;
	}
	return (0);
}

int			handle_fat(char const *exec_name, char *ptr, char const *filename,
						t_env *env)
{
	t_fh		*fat_header;
	uint32_t	i;
	char		*sub_ptr;

	i = 0;
	if (get_all_cputypes(ptr, env) < 0)
		return (-1);
	fat_header = (t_fh*)((void*)(ptr));
	while (i < swapuint32(fat_header->nfat_arch, 1))
	{
		soft_reset_env(env);
		env->cputype = (int)(swapuint32(((t_fa*)((void*)(ptr) +
			sizeof(t_fh) + sizeof(t_fa) * i))->cputype, 1));
		sub_ptr = ptr + swapuint32(((t_fa*)((void*)(ptr) + sizeof(t_fh) +
			sizeof(t_fa) * i))->offset, 1);
		env->options |= is_swap_needed((uint32_t)*((uint32_t*)sub_ptr));
		if (!(env->cputype & CPU_ARCH_ABI64) && !env->host_cputype)
			handle_32(exec_name, sub_ptr, filename, env);
		if ((env->cputype & CPU_ARCH_ABI64 && !env->host_cputype) ||
		(env->host_cputype == 1 && (env->cputype == CPU_TYPE_X86_64)))
			handle_64(exec_name, sub_ptr, filename, env);
		i++;
	}
	return (0);
}

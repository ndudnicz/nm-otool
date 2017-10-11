#include "ft_otool.h"
#include "error.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include "env.h"
#include "handle.h"
#include "handle_64.h"
#include "handle_fat.h"
#include "swap.h"
#include "free.h"

static int	is_swap_needed(uint32_t const m)
{
	return (m == MH_CIGAM || m == FAT_CIGAM || m == MH_CIGAM_64);
}

static int	is_64(uint32_t const magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

static int	is_32(uint32_t const magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM);
}

static int	is_fat(uint32_t const magic)
{
	return (magic == FAT_MAGIC || magic == FAT_CIGAM);
}

int			map_file(char const *exec_name, char const *filename, int const fd,
						t_env *env)
{
	struct stat		buf;
	char			*ptr;
	unsigned int	magic;
	int				ret;

	if (fstat(fd, &buf) < 0)
		return (ft_error(exec_name, "Error", FSTAT_FAILED));
	if ((ptr = mmap(0, buf.st_size, PREAD, PPRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error(exec_name, "Error", MMAP_FAILED));
	magic = *((unsigned int*)ptr);
	env->mmaped_size = buf.st_size;
	env->options |= is_swap_needed(magic) ? SWAP_NEEDED : 0x00;
	if ((ret = is_64(magic)) && handle_64(exec_name, ptr, filename, env) < 0)
		return (munmap_ptr(ptr, (size_t)buf.st_size, -1));
	else if (!ret && (ret = is_32(magic)) &&
	handle_32(exec_name, ptr, filename, env) < 0)
		return (munmap_ptr(ptr, (size_t)buf.st_size, -1));
	else if (!ret && (ret = is_fat(magic)) &&
	handle_fat(exec_name, ptr, filename, env) < 0)
		return (munmap_ptr(ptr, (size_t)buf.st_size, -1));
	else if (!ret)
		return (munmap_ptr(ptr, (size_t)buf.st_size,
		ft_error(exec_name, filename, BAD_ARCH)));
	else
		return (ret);
}

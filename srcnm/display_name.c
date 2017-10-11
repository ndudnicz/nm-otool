#include "display_arch.h"
#include "env.h"
#include "libft.h"
#include <stdio.h>

void	display_name(char const *filename, unsigned char const options,
						int const cputype, unsigned int const nfat_arch)
{
	if (options & MULTI_FILE || options & IS_FAT)
	{
		if (!(options & IS_FAT && nfat_arch < 2) ||
		(options & IS_FAT && options & MULTI_FILE && nfat_arch > 1))
			printf("%c", '\n');
		printf("%s", filename);
		if (options & IS_FAT && nfat_arch > 1)
			printf("%s%s%s\n", " (for architecture ", display_arch(cputype), "):");
		else
			printf("%s\n", ":");
	}
}

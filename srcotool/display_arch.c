#include <mach-o/fat.h>
#include <stdlib.h>
#include "libft.h"

char	*display_arch(int const cputype)
{
	char	*arch;

	arch = NULL;
	arch = cputype == CPU_TYPE_VAX ? "vax" : arch;
	arch = cputype == CPU_TYPE_MC680x0 ? "mc680x0" : arch;
	arch = cputype == CPU_TYPE_I386 ? "i386" : arch;
	arch = cputype == CPU_TYPE_X86_64 ? "x86_64" : arch;
	arch = cputype == CPU_TYPE_MC98000 ? "mc98000" : arch;
	arch = cputype == CPU_TYPE_HPPA ? "hppa" : arch;
	arch = cputype == CPU_TYPE_ARM ? "arm" : arch;
	arch = cputype == CPU_TYPE_ARM64 ? "arm64" : arch;
	arch = cputype == CPU_TYPE_MC88000 ? "mc88000" : arch;
	arch = cputype == CPU_TYPE_SPARC ? "sparc" : arch;
	arch = cputype == CPU_TYPE_I860 ? "i860" : arch;
	arch = cputype == CPU_TYPE_POWERPC ? "ppc" : arch;
	arch = cputype == CPU_TYPE_POWERPC64 ? "ppc64" : arch;
	arch = arch == NULL ? "unknown" : arch;
	return arch;
}

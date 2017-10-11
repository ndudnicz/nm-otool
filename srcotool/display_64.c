#include "display_64.h"
#include <stdlib.h>
#include "print_data.h"
#include <stdio.h>

void	display_64(t_section_64 *begin, uint64_t addr, int const cpu,
					uint32_t i)
{
	t_section_64	*tmp_next;
	char const		*padding;

	padding = cpu == CPU_TYPE_ARM || cpu == CPU_TYPE_POWERPC ? "" : " ";
	printf("%016lx\t", (long)addr);
	while (begin)
	{
		if (i % 4)
		{
			print_data(begin->data, padding, begin->next ? " " : " \n",
			begin->mask);
		}
		else
		{
			addr += 16;
			print_data(begin->data, padding, " \n", begin->mask);
			if (begin->next)
				printf("%016lx\t", (long)addr);
		}
		tmp_next = begin->next;
		free(begin);
		begin = tmp_next;
		i++;
	}
}

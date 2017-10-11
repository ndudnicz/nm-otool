#include "display.h"
#include <stdlib.h>
#include "print_data.h"
#include <stdio.h>

void			display(t_section *begin, uint32_t addr, int const cpu,
							uint32_t i)
{
	t_section		*tmp_next;
	char const		*padding;

	padding = cpu == CPU_TYPE_ARM || cpu == CPU_TYPE_POWERPC ? "" : " ";
	printf("%08lx\t", (long)addr);
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
				printf("%08lx\t", (long)addr);
		}
		tmp_next = begin->next;
		free(begin);
		begin = tmp_next;
		i++;
	}
}

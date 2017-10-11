#include <stdint.h>
#include <stdio.h>

void	print_data(uint32_t const data, char const *padd, char const *new_line,
					uint32_t const mask)
{
	if (mask == 0xffffffff)
	{
		printf("%02lx%s%02lx%s%02lx%s%02lx%s", (long)(data & 0x000000ff), padd,
		(long)((data & 0x0000ff00) >> 8), padd,
		(long)((data & 0x00ff0000) >> 16), padd,
		(long)((data & 0xff000000) >> 24), new_line);
	}
	else if (mask == 0x00ffffff)
	{
		printf("%02lx%s%02lx%s%02lx%s",
		(long)((data & 0x0000ff)), padd,
		(long)((data & 0x00ff00) >> 8), padd,
		(long)((data & 0xff0000) >> 16), new_line);
	}
	else if (mask == 0x0000ffff)
	{
		printf("%02lx%s%02lx%s",
		(long)((data & 0x00ff) >> 0), padd,
		(long)((data & 0xff00) >> 8), new_line);
	}
	else if (mask == 0x000000ff)
	{
		printf("%02lx%s",
		(long)((data & 0x000000ff)), new_line);
	}
}

#include "swap.h"

uint32_t	swapuint32(uint32_t n, unsigned char const swap)
{
	if (swap)
		return ((n & 0x000000ff) << 24 |
		(n & 0x0000ff00) << 8 |
		(n & 0x00ff0000) >> 8 |
		(n & 0xff000000) >> 24);
	else
		return (n);
}

uint64_t	swapuint64(uint64_t n, unsigned char const swap)
{
	if (swap)
		return ((n & 0x00000000000000ff) << 56 |
		(n & 0x000000000000ff00) << 40 |
		(n & 0x0000000000ff0000) << 24 |
		(n & 0x00000000ff000000) << 8 |
		(n & 0x000000ff00000000) >> 8 |
		(n & 0x0000ff0000000000) >> 24 |
		(n & 0x00ff000000000000) >> 40 |
		(n & 0xff00000000000000) >> 56);
	else
		return (n);
}

void		swap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

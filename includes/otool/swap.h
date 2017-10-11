#ifndef SWAP_H
# define SWAP_H

# include <stdint.h>

uint32_t	swapuint32(uint32_t n, unsigned char const swap);
uint64_t	swapuint64(uint64_t n, unsigned char const swap);
void		swap(void **a, void **b);

#endif

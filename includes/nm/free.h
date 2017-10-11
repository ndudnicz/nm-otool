#ifndef FREE_H
# define FREE_H

int		munmap_ptr(char *ptr, size_t size, int ret);
int		free_all(void **array, int ret);

#endif

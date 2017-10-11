#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

// void		ft_putendl(char const *s);
int			ft_putstr_fd(char const *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(const char *s1, const char *s2);
// int			ft_toupper(int c);
// int			ft_tolower(int c);
size_t	ft_strlen(const char *s);
int			ft_putstr(char const *s);
void		ft_putendl(char const *s);
void		ft_putchar(char c);
// char		*ft_strchr(const char *s, int c);
char		*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strnew(size_t size);
void				ft_bzero(void *s, size_t n);

#endif

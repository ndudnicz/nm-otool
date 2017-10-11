#ifndef ENV_H
# define ENV_H

/*
** Options
*/

# define SWAP_NEEDED			0x01
# define MULTI_FILE				0x02
# define IS_FAT					0x04

typedef struct		s_env
{
	unsigned char	options;
	unsigned char	host_cputype;
	int				cputype;
	char			*ptr;
	long int		mmaped_size;
}					t_env;

void				init_env(t_env *env);
void				soft_reset_env(t_env *env);
void				hard_reset_env(t_env *env);

#endif

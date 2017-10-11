#ifndef ENV_H
# define ENV_H

/*
** Options
*/

# define SWAP_NEEDED			0x01
# define MULTI_FILE				0x02
# define IS_FAT					0x04
# define SORT_NUM				0x08
# define ONLY_UNDEFINED			0x10
# define NO_UNDEFINED			0x20
# define NO_SORT				0x40
# define ONLY_SYM_NAME			0x80

# define SORT_NUM_CHAR			'n'
# define ONLY_UNDEFINED_CHAR	'u'
# define NO_UNDEFINED_CHAR		'U'
# define NO_SORT_CHAR			'p'
# define ONLY_SYM_NAME_CHAR		'j'

# define PARAMS_STR				"nuUpj"

typedef struct	s_env
{
	unsigned char	options;
	unsigned char	host_cputype;
	unsigned int	nfat_arch;
	int				cputype;
	long int		mmaped_size;
}				t_env;

void			init_env(t_env *env);
void			soft_reset_env(t_env *env);
void			hard_reset_env(t_env *env);

#endif

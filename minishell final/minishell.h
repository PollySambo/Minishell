

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct	s_ints
{
	int			i;
	int			j;
	int			l;
	int			m;
	int			len;
}				t_ints;

typedef struct	s_built
{
	int			args_len;
	int			env_len;
	int			e;
	int			len;
	char		*line;
	char		*path;
	char		*home;
	char		*pwd;
	char		*temp;
	char		*newlvl;
	char		*both;
	char		*var;
	char		*val;
	char		**e_args;
	char		**temp1;
	char		**temp2;
	char		**args;
	char		**paths;
	char		cwd[512];
	char		**env;
}				t_built;

void			ft_init_vars(t_built *shell);
void			ft_check_args(t_built *shell, int i, const char **in);
void			ft_extern(t_built *shell);
void			ft_shsplit(t_built *shell, int i, int j, int k);
int				ft_argcount(char *str, int i, int count);
int				ft_chrpos(char *str, char c);
void			ft_builtin(t_built *shell, int i);
void			ft_echo(t_built *shell);
void			ft_cd(t_built *shell);
char			*ft_envseek(t_built *shell, char *arg);
void			ft_unsetenv(t_built *shell);
void			ft_export(t_built *shell);
void			ft_setenv(t_built *shell, int j, int m, int l);
void			ft_env(t_built *shell);
void			ft_check_line(t_built *shell);
void			ft_errexit(t_built *shell);
void			ft_shlvl(t_built *shell);

#endif



#include <minishell.h>

void			ft_extern(t_built *shell)
{
	int			sig;
	int			pid;

	sig = 1;
	if (shell->path == NULL && shell->e == 0)
	{
		ft_putstr("Error: Command Not Found: ");
		ft_putendl(shell->args[0]);
	}
	else if (shell->path != NULL && shell->e == 0)
	{
		pid = fork();
		if (pid < 0)
			ft_putendl("Error: Forking Failed");
		else if (pid > 0)
			wait(&sig);
		else if (pid == 0)
			execve(shell->path, shell->e_args, shell->env);
	}
	else if (shell->e == -1)
		shell->e = 0;
}

void			ft_check_args(t_built *shell, int i, const char **in)
{
	while (++i < 6 && shell->e == 0)
	{
		if (shell->e == 0 && ft_strcmp(shell->args[0], in[i]) == 0)
			ft_builtin(shell, i);
	}
	i = -1;
	if (shell->e == 0 && access(shell->args[0], F_OK) == -1)
	{
		while (shell->e == 0 && ++i < ft_arrlen(shell->paths))
		{
			shell->temp = ft_strjoin(shell->paths[i], "/");
			shell->path = ft_strjoin(shell->temp, shell->args[0]);
			ft_strdel(&shell->temp);
			if (access(shell->path, F_OK) != -1)
				break ;
			else
				ft_strdel(&shell->path);
		}
	}
	else if (shell->e == 0)
		shell->path = ft_strdup(shell->args[0]);
	shell->e_args = shell->args;
	ft_extern(shell);
}

void			ft_init_vars(t_built *shell)
{
	char		*temp;

	if (shell->line != NULL)
		ft_strdel(&shell->line);
	if (shell->args != NULL)
		ft_arrdel(shell->args);
	if (shell->path != NULL)
		ft_strdel(&shell->path);
	if (shell->paths != NULL && *shell->paths != NULL)
		ft_arrdel(shell->paths);
	shell->home = ft_envseek(shell, "HOME");
	shell->pwd = ft_envseek(shell, "PWD");
	temp = ft_envseek(shell, "PATH");
	if (temp)
		shell->paths = ft_strsplit(temp, ':');
	else
		shell->paths = NULL;
	if (getcwd(shell->cwd, sizeof(shell->cwd)) == NULL)
		shell->e = 1;
	shell->args_len = 0;
	shell->line = NULL;
}

int				main(void)
{
	extern char	**environ;
	t_built		shell;

	shell.e = -1;
	shell.line = NULL;
	shell.args = NULL;
	shell.path = NULL;
	shell.paths = NULL;
	shell.env_len = ft_arrlen(environ);
	shell.env = (char **)ft_memalloc(sizeof(char *) * (shell.env_len + 1));
	while (++shell.e < shell.env_len)
		shell.env[shell.e] = ft_strdup(environ[shell.e]);
	shell.env[shell.e] = NULL;
	shell.e = 0;
	ft_shlvl(&shell);
	while (1)
	{
		ft_init_vars(&shell);
		if (shell.e != 0)
			ft_errexit(&shell);
		ft_putstr("$>");
		get_next_line(STDIN, &shell.line);
		ft_check_line(&shell);
	}
	sleep(50);
	return (0);
}

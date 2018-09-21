#include <minishell.h>

void	ft_builtin(t_built *shell, int i)
{
	shell->e = -1;
	if (i == 0)
		ft_echo(shell);
	else if (i == 1)
		ft_export(shell);
	else if (i == 2)
		ft_unsetenv(shell);
	else if (i == 3)
	{
		ft_cd(shell);
		ft_bzero((void *)shell->cwd, sizeof(shell->cwd));
		getcwd(shell->cwd, sizeof(shell->cwd));
		shell->var = "PWD";
		shell->val = shell->cwd;
		ft_setenv(shell, -1, 0, -1);
	}
	else if (i == 4)
		ft_env(shell);
	else if (i == 5)
		shell->e = 9;
}

void	ft_echo(t_built *shell)
{
	t_ints		k;
	char		*temp;

	k.i = 0;
	k.j = -1;
	if (shell->args_len > 1)
	{
		while (++k.i < shell->args_len)
		{
			if (shell->args[k.i][0] == '$')
				temp = ft_envseek(shell, shell->args[k.i]);
			else
				temp = shell->args[k.i];
			ft_putstr(temp);
			if (k.i != shell->args_len)
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
}

void	ft_cd(t_built *shell)
{
	if (shell->args_len == 1)
		shell->path = ft_strdup(shell->home);
	else if (shell->args_len > 1)
	{
		if (shell->args[1][0] == '~')
		{
			shell->newlvl = shell->args[1];
			shell->path = ft_strjoin(shell->home, ++shell->newlvl);
			shell->newlvl--;
		}
		else if (ft_strcmp(shell->args[1], "-") == 0)
			shell->path = ft_strdup(ft_envseek(shell, "OLDPWD"));
		else
			shell->path = ft_strdup(shell->args[1]);
	}
	shell->len = chdir(shell->path);
	if (shell->len == 0)
	{
		shell->var = "OLDPWD";
		shell->val = shell->cwd;
		ft_setenv(shell, -1, 0, -1);
	}
	else
		ft_putendl("Error: chdir Failed");
}

#include <minishell.h>

int				ft_argcount(char *str, int i, int count)
{
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '"')
			i++;
		else
		{
			count++;
			if (i > 0 && str[i - 1] == '"' && i != (int)ft_strlen(str))
			{
				while (str[i] && str[i] != '"')
					i++;
			}
			else
			{
				while (str[i] && str[i] != ' ' && str[i] != '\t')
					i++;
			}
		}
	}
	return (count);
}

void			ft_shsplit(t_built *shell, int i, int j, int k)
{
	shell->args_len = ft_argcount(shell->line, 0, 0);
	shell->args = (char**)ft_memalloc(sizeof(char *) * (shell->args_len + 1));
	if (!shell->args)
		shell->e = 2;
	while (shell->e == 0 && ++j < shell->args_len && shell->line[i])
	{
		k = 0;
		while ((shell->line[i] == ' ' || shell->line[i] == '\t'
			|| shell->line[i] == '"') && shell->line[i])
			i++;
		if (i > 0 && shell->line[i - 1] == '"')
		{
			while (shell->line[i + k] != '"' && shell->line[i + k])
				k++;
		}
		else
		{
			while ((shell->line[i + k] != ' ' && shell->line[i + k] != '\t')
				&& shell->line[i + k])
				k++;
		}
		shell->args[j] = ft_strsub(shell->line, i, k);
		i += k;
	}
	shell->args[j] = NULL;
}

void			ft_check_line(t_built *shell)
{
	const char	*in[6];

	in[0] = "echo";
	in[1] = "setenv";
	in[2] = "unsetenv";
	in[3] = "cd";
	in[4] = "env";
	in[5] = "exit";
	if (shell->line != NULL)
	{
		ft_shsplit(shell, 0, -1, 0);
		if (shell->args[0] != NULL)
			ft_check_args(shell, -1, in);
	}
	else
		shell->args = NULL;
}

void			ft_shlvl(t_built *shell)
{
	int		level;

	level = ft_atoi(ft_envseek(shell, "SHLVL")) + 1;
	shell->newlvl = ft_itoa(level);
	shell->var = "SHLVL";
	shell->val = shell->newlvl;
	ft_setenv(shell, -1, 0, -1);
	ft_strdel(&shell->newlvl);
}

void			ft_errexit(t_built *shell)
{
	ft_arrdel(shell->env);
	if (shell->paths != NULL)
		ft_arrdel(shell->paths);
	if (shell->e == 1)
		ft_puterror("Error: cannot get current working directory");
	if (shell->e == 2)
		ft_puterror("Error: cannot malloc");
	if (shell->e == 9)
	{
		ft_putendl("Exiting done");
		exit(EXIT_SUCCESS);
	}
}

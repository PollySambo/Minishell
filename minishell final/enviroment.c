#include <unistd.h>
#include <minishell.h>

void		ft_unsetenv(t_built *shell)
{
	t_ints	k;

	k.i = 0;
	while (++k.i < shell->args_len)
	{
		k.j = -1;
		k.l = -1;
		k.len = ft_strlen(shell->args[k.i]);
		if (ft_envseek(shell, shell->args[k.i]) != NULL)
		{
			shell->temp2 = (char **)ft_memalloc(sizeof(char *) * (shell->env_len));
			while (++k.l < shell->env_len)
			{
				if (ft_strncmp(shell->args[k.i], shell->env[k.l], k.len) == 0
					&& shell->env[k.l][k.len] == '=')
					continue;
				else
					shell->temp2[++k.j] = ft_strdup(shell->env[k.l]);
			}
			shell->temp2[++k.j] = NULL;
			ft_arrdel(shell->env);
			shell->env = shell->temp2;
			shell->env_len--;
		}
	}
}

void		ft_export(t_built *shell)
{
	int		i;

	i = 1;
	while (i < shell->args_len)
	{
		if (ft_chrpos(shell->args[i], '=') != -1)
		{
			shell->var = ft_strsub(shell->args[i], 0,
				ft_chrpos(shell->args[i], '='));
			shell->val = ft_strsub(shell->args[i], ft_chrpos(shell->args[i], '=') + 1,
				ft_strlen(shell->args[i]) - (ft_chrpos(shell->args[i], '=') + 1));
			ft_setenv(shell, -1, 0, -1);
			ft_strdel(&shell->var);
			ft_strdel(&shell->val);
		}
		else if ((i + 1) < shell->args_len)
		{
			shell->var = shell->args[i];
			shell->val = shell->args[i + 1];
			ft_setenv(shell, -1, 0, -1);
			i++;
		}
		i++;
	}
}

void		ft_setenv(t_built *shell, int j, int m, int l)
{
	shell->len = ft_strlen(shell->var);
	shell->temp = ft_strjoin(shell->var, "=");
	shell->both = ft_strjoin(shell->temp, shell->val);
	while (shell->env[++j] != NULL && m != 1)
	{
		if (ft_strncmp(shell->var, shell->env[j], shell->len) == 0
			&& shell->env[j][shell->len] == '=')
		{
			ft_strdel(&shell->env[j]);
			shell->env[j] = shell->both;
			m = 1;
		}
	}
	if (m != 1)
	{
		shell->temp2 = (char **)ft_memalloc(sizeof(char *) * (shell->env_len + 2));
		while (++l < shell->env_len)
			shell->temp2[l] = ft_strdup(shell->env[l]);
		shell->temp2[l] = shell->both;
		shell->temp2[++l] = NULL;
		ft_arrdel(shell->env);
		shell->env = shell->temp2;
		shell->env_len++;
	}
	ft_strdel(&shell->temp);
}

void		ft_env(t_built *shell)
{
	t_ints	k;

	k.i = 0;
	k.j = -1;
	k.m = -1;
	k.len = -1;
	k.l = -1;
	if (shell->args_len == 1)
	{
		while (shell->env[++k.l] != NULL)
			ft_putendl(shell->env[k.l]);
	}
}

char		*ft_envseek(t_built *shell, char *arg)
{
	t_ints	k;
	char	*temp1;
	char	*temp2;

	k.i = 0;
	k.j = -1;
	if (arg[0] == '$')
		arg++;
	k.l = ft_strlen(arg);
	while (++k.j < shell->env_len && shell->env[k.j] != NULL)
	{
		if ((int)ft_strlen(shell->env[k.j]) > k.l)
			temp1 = ft_strsub(shell->env[k.j], 0, k.l);
		if (!temp1)
			continue ;
		else if (ft_strcmp(temp1, arg) == 0 && shell->env[k.j][k.l] == '=')
		{
			temp2 = ft_strchr(shell->env[k.j], '=');
			ft_strdel(&temp1);
			return (++temp2);
		}
		ft_strdel(&temp1);
	}
	return (NULL);
}

#include "minishell.h"

char	**copy_env(char **envp)
{
	int		n;
	int		i;
	char	**dup;

	n = 0;
	i = 0;
	dup = NULL;

	while (envp && envp[n])
		n++;
	dup = (char **)malloc(sizeof(char *) * (n + 1));
	if (!dup)
		return (NULL);
	while (i < n)
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[n] = NULL;
	return (dup);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	*get_env_value(t_shell *sh, const char *name)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!sh || !name)
		return (NULL);
	len = ft_strlen(name);
	while (sh->envp && sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], name, len) == 0
				&& sh->envp[i][len] == '=')
			return (sh->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	init_shell(t_shell *shell, char **envp)
{
	if (!shell)
		return ;
	shell->envp = copy_env(envp);
	if (!shell->envp)
	{
		shell->last_status = EXIT_KO;
		shell->running = 0;
		shell->cmds = NULL;
		return ;
	}
	shell->last_status = EXIT_OK;
	shell->running = 1;
	shell->cmds = NULL;
}

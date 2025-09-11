/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:05:19 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:05:21 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	int		n;
	int		i;
	char	**dup;

	n = 0;
	i = 0;
	while (envp && envp[n])
		n++;
	dup = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	while (i < n)
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
		{
			free_env(dup);
			return (NULL);
		}
		i++;
	}
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

static void	set_min_env(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	free_env(shell->envp);
	shell->envp = malloc(sizeof(char *) * 8);
	shell->envp[0] = ft_strjoin("PWD=", cwd);
	shell->envp[1] = ft_strdup("LS_COLORS=");
	shell->envp[2] = ft_strdup("LESSCLOSE=/usr/bin/lesspipe %s %s");
	shell->envp[3] = ft_strdup("LESSOPEN=| /usr/bin/lesspipe %s");
	shell->envp[4] = ft_strdup("SHLVL=1");
	shell->envp[5] = ft_strdup("_=/usr/bin/env");
	shell->envp[6] = ft_strdup("PATH=/usr/bin:/bin");
	shell->envp[7] = NULL;
	free(cwd);
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
	if (!envp || !envp[0])
		set_min_env(shell);
	shell->last_status = EXIT_OK;
	shell->running = 1;
	shell->cmds = NULL;
	shell->need_newline = 0;
}

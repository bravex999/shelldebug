/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:10:23 by alvera-f          #+#    #+#             */
/*   Updated: 2025/09/03 19:24:26 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	find_env_index(char **envp, char *key)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len)
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	**remove_env_var(char **envp, char *key)
{
	int	i;
	int	idx;

	idx = find_env_index(envp, key);
	if (idx == -1)
		return (envp);
	free(envp[idx]);
	i = idx;
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	return (envp);
}

int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	error;

	if (!cmd || !cmd->argv)
		return (1);
	i = 1;
	error = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_unset_identifier(cmd->argv[i]))
		{
			write(2, "minishell: unset: `", 19);
			write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
			write(2, "': not a valid identifier\n", 27);
			error = 1;
		}
		else if (shell->envp)
		{
			shell->envp = remove_env_var(shell->envp, cmd->argv[i]);
		}
		i++;
	}
	shell->last_status = error;
	return (error);
}

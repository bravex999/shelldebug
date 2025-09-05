/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:10:50 by alvera-f          #+#    #+#             */
/*   Updated: 2025/09/03 19:10:52 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_whitespace(const char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	print_env_vars(char **env)
{
	char	*equal;

	while (env && *env)
	{
		equal = ft_strchr(*env, '=');
		if (equal && *(equal + 1))
		{
			write(1, *env, ft_strlen(*env));
			write(1, "\n", 1);
		}
		env++;
	}
}

int	ft_env(t_cmd *cmd, t_shell *shell)
{
	if (cmd->argv[1] && is_only_whitespace(cmd->argv[1]))
	{
		write(2, "env: '", 6);
		write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(2, "': No such file or directory\n", 30);
		shell->last_status = 127;
		return (127);
	}
	print_env_vars(shell->envp);
	shell->last_status = 0;
	return (0);
}

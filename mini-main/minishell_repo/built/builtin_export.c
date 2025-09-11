/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:41:55 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/03 19:09:07 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_single_var(const char *var)
{
	char	*equal;

	write(1, "declare -x ", 11);
	equal = ft_strchr(var, '=');
	if (equal)
	{
		write(1, var, equal - var + 1);
		write(1, "\"", 1);
		write(1, equal + 1, ft_strlen(equal + 1));
		write(1, "\"", 1);
	}
	else
		write(1, var, ft_strlen(var));
	write(1, "\n", 1);
}

static int	print_exported_vars(char **envp)
{
	int		i;
	char	**sorted;

	sorted = sort_envp(envp);
	if (!sorted)
		return (1);
	i = 0;
	while (sorted[i])
	{
		print_single_var(sorted[i]);
		free(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

static int	handle_export_arg(char *arg, t_shell *shell)
{
	char	*sep;
	char	*key;
	char	*value;

	if (!is_valid_identifier_aux(arg))
	{
		print_export_error(arg);
		return (1);
	}
	sep = ft_strchr(arg, '=');
	if (sep)
	{
		key = ft_substr(arg, 0, sep - arg);
		value = sep + 1;
		ft_setenv(&shell->envp, key, value);
		free(key);
	}
	else
		ft_setenv(&shell->envp, arg, "");
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	error;
	int	r;

	if (!cmd->argv[1])
		return (print_exported_vars(shell->envp));
	i = 1;
	error = 0;
	while (cmd->argv[i])
	{
		r = handle_export_arg(cmd->argv[i], shell);
		if (r)
			error = 1;
		i++;
	}
	return (error);
}

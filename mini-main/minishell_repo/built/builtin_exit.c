/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:11:00 by alvera-f          #+#    #+#             */
/*   Updated: 2025/09/03 19:11:03 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

static int	is_numeric_aux(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_numeric_error(char *arg, t_shell *shell)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 29);
	free_env_array(shell->envp);
	exit(255);
}

int	ft_exit(t_cmd *cmd, t_shell *shell)
{
	long	code;

	write(1, "exit\n", 5);
	if (!cmd->argv[1])
	{
		free_env_array(shell->envp);
		exit(shell->last_status);
	}
	if (!is_numeric_aux(cmd->argv[1]))
		exit_numeric_error(cmd->argv[1], shell);
	if (cmd->argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->last_status = 1;
		return (1);
	}
	code = ft_atol(cmd->argv[1]);
	free_env_array(shell->envp);
	exit((unsigned char)code);
}

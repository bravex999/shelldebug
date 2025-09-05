/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:10:05 by alvera-f          #+#    #+#             */
/*   Updated: 2025/09/03 19:14:49 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_shell *shell)
{
	char	cwd[1024];

	(void)cmd;
	(void)shell;
	if (getcwd(cwd, sizeof(cwd)))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

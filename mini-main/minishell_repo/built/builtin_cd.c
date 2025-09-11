/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:10:43 by alvera-f          #+#    #+#             */
/*   Updated: 2025/09/03 19:10:46 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_home(char *arg, t_shell *shell)
{
	char	*home;
	char	*expanded;

	home = ft_getenv(shell->envp, "HOME");
	if (!home)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (NULL);
	}
	expanded = ft_strjoin(home, arg + 1);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*resolve_cd_target(t_cmd *cmd, t_shell *shell)
{
	char	*home;

	if (!cmd->argv[1])
	{
		home = ft_getenv(shell->envp, "HOME");
		if (!home)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		return (ft_strdup(home));
	}
	return (resolve_cd_argument(cmd->argv[1], shell));
}

char	*resolve_cd_argument(char *arg, t_shell *shell)
{
	char	*oldpwd;

	if (ft_strcmp(arg, "-") == 0)
	{
		oldpwd = ft_getenv(shell->envp, "OLDPWD");
		if (!oldpwd)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			return (NULL);
		}
		printf("%s\n", oldpwd);
		return (ft_strdup(oldpwd));
	}
	else if (arg[0] == '~')
	{
		return (expand_home(arg, shell));
	}
	return (ft_strdup(arg));
}

void	update_pwd_and_oldpwd(t_shell *shell)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = ft_getenv(shell->envp, "PWD");
	if (oldpwd)
		ft_setenv(&shell->envp, "OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_setenv(&shell->envp, "PWD", cwd);
		free(cwd);
	}
	else
	{
		perror("minishell: cd");
	}
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target_dir;

	target_dir = resolve_cd_target(cmd, shell);
	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, target_dir, ft_strlen(target_dir));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		free(target_dir);
		return (1);
	}
	update_pwd_and_oldpwd(shell);
	free(target_dir);
	return (0);
}

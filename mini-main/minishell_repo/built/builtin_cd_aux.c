/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:10:35 by alvera-f          #+#    #+#             */
/*   Updated: 2025/09/03 19:10:38 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **envp, const char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	while (*envp)
	{
		if (ft_strncmp(*envp, key, key_len) == 0 && (*envp)[key_len] == '=')
			return (*envp + key_len + 1);
		envp++;
	}
	return (NULL);
}

char	*build_env_var(const char *key, const char *value)
{
	char	*tmp;
	char	*var;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	var = ft_strjoin(tmp, value);
	free(tmp);
	return (var);
}

static void	add_new_env_var(char ***envp, const char *key, const char *value)
{
	int		i;
	char	*new_var;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	ft_memcpy(new_envp, *envp, sizeof(char *) * i);
	new_var = build_env_var(key, value);
	if (!new_var)
		return ;
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}

void	ft_setenv(char ***envp, const char *key, const char *value)
{
	int		i;
	int		key_len;
	char	*new_var;

	key_len = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, key_len) == 0
			&& (*envp)[i][key_len] == '=')
		{
			new_var = build_env_var(key, value);
			if (!new_var)
				return ;
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return ;
		}
		i++;
	}
	add_new_env_var(envp, key, value);
}

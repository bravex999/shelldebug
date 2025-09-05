/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:22:24 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/03 19:46:01 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_cmp(const char *s1, const char *s2)
{
	size_t	n1;
	size_t	n2;
	size_t	n;

	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	if (n1 > n2)
		n = n1 + 1;
	else
		n = n2 + 1;
	return (ft_strncmp(s1, s2, n));
}

static void	sort_envp_custom(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (str_cmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**sort_envp(char **envp)
{
	int		count;
	char	**copy;

	count = 0;
	copy = copy_env(envp);
	if (!copy)
		return (NULL);
	while (copy[count])
		count++;
	sort_envp_custom(copy);
	return (copy);
}

int	is_valid_identifier_aux(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	print_export_error(const char *arg)
{
	write(2, "bash: export: `", 15);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

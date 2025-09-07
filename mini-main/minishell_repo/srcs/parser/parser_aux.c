/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:16:41 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:16:43 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	fill_single(char **result, const char *s)
{
	result[0] = ft_strdup(s);
	if (!result[0])
		return (0);
	result[1] = NULL;
	return (1);
}

char	**super_split(char const *s, char c, char b)
{
	char	**result;

	(void)c;
	(void)b;
	if (!s)
		return (NULL);
	result = ft_calloc(2, sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_single(result, s))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

t_token	*filter_argv_tokens(t_token *tokens)
{
	t_token	*argv_list;
	t_token	*current;

	argv_list = NULL;
	current = tokens;
	while (current)
	{
		if (current->type < T_REDIR_IN || current->type > T_HEREDOC)
		{
			add_token(&argv_list, create_token_safe(current->type,
					ft_strdup(current->str)));
			current = current->next;
		}
		else
		{
			if (current->next)
				current = current->next->next;
			else
				current = current->next;
		}
	}
	return (argv_list);
}

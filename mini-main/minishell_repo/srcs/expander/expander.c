/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:12:11 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:12:13 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*new_list;
	t_token	*e_token;
	t_token	*current;

	new_list = NULL;
	e_token = NULL;
	current = tokens;
	while (current)
	{
		if (current->expand == 1)
		{
			e_token = expander_ultra(current, shell);
			add_token(&new_list, e_token);
		}
		else
		{
			e_token = create_token_safe(current->type, ft_strdup(current->str));
			if (!e_token)
				return (NULL);
			e_token->join_next = current->join_next;
			add_token(&new_list, e_token);
		}
		current = current->next;
	}
	return (new_list);
}

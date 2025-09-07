/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:16:55 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:16:59 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_redirections(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == T_REDIR_IN
			|| current->type == T_REDIR_OUT
			|| current->type == T_REDIR_APPEND)
			return (1);
		current = current->next;
	}
	return (0);
}

int	has_pipes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

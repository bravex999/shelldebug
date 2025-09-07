/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:15:58 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:16:00 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	return (build_expanded_string(line, shell));
}

int	is_heredoc(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
}

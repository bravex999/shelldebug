/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:23:53 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:23:55 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_word(t_token *token_list)
{
	if (token_list->type != T_WORD
		&& token_list->type != T_QUOTED_SINGLE
		&& token_list->type != T_QUOTED_DOUBLE)
		return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

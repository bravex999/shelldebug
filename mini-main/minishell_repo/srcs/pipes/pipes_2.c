/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:20:22 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:20:23 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*build_segment_cmd(t_token *start, t_token *end, t_shell *sh)
{
	t_token	*seg;
	t_cmd	*node;

	seg = copy_segment(start, end);
	node = parse_one_segment(seg, sh);
	free_tokens(seg);
	return (node);
}

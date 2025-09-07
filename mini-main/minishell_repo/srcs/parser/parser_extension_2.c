/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extension_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:17:38 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:17:47 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_outfile_and_touch(t_cmd *cmd, const char *name, int append)
{
	int	fd;
	int	flags;

	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(name);
	cmd->append = append;
	flags = O_CREAT | O_WRONLY;
	if (append)
		flags = flags | O_APPEND;
	else
		flags = flags | O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd != -1)
		close(fd);
}

t_token	*process_single_redirection(t_cmd *cmd, t_token *current)
{
	if (current->type == T_REDIR_IN && current->next)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(current->next->str);
		return (current->next->next);
	}
	if (current->type == T_REDIR_OUT && current->next)
	{
		set_outfile_and_touch(cmd, current->next->str, 0);
		return (current->next->next);
	}
	if (current->type == T_REDIR_APPEND && current->next)
	{
		set_outfile_and_touch(cmd, current->next->str, 1);
		return (current->next->next);
	}
	return (current->next);
}

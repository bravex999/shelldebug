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

static int	set_outfile_and_touch(t_cmd *cmd, const char *name, int append)
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
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

static int	set_infile_and_probe(t_cmd *cmd, const char *name)
{
	int	fd;

	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup(name);
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

t_token	*process_single_redirection(t_cmd *cmd, t_token *current)
{
	if (current->type == T_REDIR_IN && current->next)
	{
		if (set_infile_and_probe(cmd, current->next->str) == -1)
			return (NULL);
		return (current->next->next);
	}
	if (current->type == T_REDIR_OUT && current->next)
	{
		if (set_outfile_and_touch(cmd, current->next->str, 0) == -1)
			return (NULL);
		return (current->next->next);
	}
	if (current->type == T_REDIR_APPEND && current->next)
	{
		if (set_outfile_and_touch(cmd, current->next->str, 1) == -1)
			return (NULL);
		return (current->next->next);
	}
	return (current->next);
}

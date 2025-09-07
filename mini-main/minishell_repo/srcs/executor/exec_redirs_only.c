/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_only.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:06:13 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:06:17 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	touch_one(const char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	handle_only_redirections(t_cmd *cmd)
{
	int	fail;
	int	flags;

	fail = 0;
	if (cmd->infile)
		if (touch_one(cmd->infile, O_RDONLY, 0) != 0)
			fail = 1;
	if (cmd->outfile)
	{
		flags = O_CREAT | O_WRONLY;
		if (cmd->append)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		if (touch_one(cmd->outfile, flags, 0644) != 0)
			fail = 1;
	}
	if (fail)
		return (1);
	return (0);
}

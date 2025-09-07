/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:04:17 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:04:23 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_ctrl_c(char **line, t_shell *shell);

static void	process_read_line(char **line, t_shell *shell)
{
	t_token	*tokens;

	if (g_signal == SIGINT && handle_ctrl_c_signal(line, shell))
	{
		g_signal = 0;
		return ;
	}
	if (isatty(STDIN_FILENO) && history(*line))
		add_history(*line);
	tokens = tokenize_line(*line, shell);
	if (tokens)
		process_tokens(tokens, *line, shell);
	else
		free(*line);
}

void	start_loop(t_shell *shell)
{
	char	*line;

	line = NULL;
	g_signal = 0;
	while (shell->running)
	{
		if (shell->need_newline)
		{
			write(STDOUT_FILENO, "\n", 1);
			shell->need_newline = 0;
		}
		line = read_input();
		if (check_ctrl_d(line))
			break ;
		process_read_line(&line, shell);
	}
}

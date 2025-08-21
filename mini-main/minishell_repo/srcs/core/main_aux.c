#include "minishell.h"

int			handle_ctrl_c(char **line, t_shell *shell);

void	start_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;

	line = NULL;
	tokens = NULL;
	while (shell->running)
	{
		line = read_input();
		if (check_ctrl_d(line))
			break ;
		if (handle_ctrl_c_signal(&line, shell))
		{
			g_signal = 0;
		}
		else
		{
			if (isatty(STDIN_FILENO) && history(line))
				add_history(line);
			tokens = tokenize_line(line, shell);
			if (tokens)
				process_tokens(tokens, line, shell);
			else
				free(line);
		}
	}
}

int	handle_ctrl_c(char **line, t_shell *shell)
{
	g_signal = 0;
	shell->last_status = SIGINT_EXIT;
/*	printf("\n");*/
	rl_on_new_line();
	rl_replace_line("", 0);
/*	rl_redisplay();*/
	free(*line);
	*line = NULL;
	return (1);
}

/*static void	print_syntax_error(char *token_str)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (token_str)
		write(2, token_str, ft_strlen(token_str));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
}

static void	process_tokens(t_token *tokens, char *line, t_shell *shell)
{
	t_cmd	*commands;
	t_cmd	*pipeline_cmds;
	t_token	*expanded;
	t_token	*final;

	commands = NULL;
	pipeline_cmds = NULL;
	expanded = expand_tokens(tokens, shell);
	free_tokens(tokens);
	if (!expanded)
	{
		shell->last_status = INVALID;
		free_everything(line, NULL, NULL);
		return ;
	}
	final = finalize_and_join_tokens(expanded);
	free_tokens(expanded);
	if (final && (check_initial_token(final) || check_all_pipe(final)
		|| check_all_redirections(final)))
	{
		shell->last_status = INVALID;
		if (check_all_redirections(final))
			print_syntax_error(NULL);
		else if (check_initial_token(final))
			print_syntax_error(final->str);
		else
			print_syntax_error("|");
		free_everything(line, final, NULL);
		return ;
	}
	if (has_pipes(final))
	{
		pipeline_cmds = parse_pipeline(final, shell);
		if (!pipeline_cmds)
		{
			shell->last_status = INVALID;
			print_syntax_error("|");
			free_everything(line, final, NULL);
			return ;
		}
		execute_pipeline(pipeline_cmds, shell);
		free_commands(pipeline_cmds);
		free_everything(line, final, NULL);
		return ;
	}
	commands = parse_tokens(final, shell);
	if (!commands)
	{
		shell->last_status = INVALID;
		free_everything(line, final, NULL);
		return ;
	}
	execute_commands(commands, shell);
	free_everything(line, final, commands);
}*/

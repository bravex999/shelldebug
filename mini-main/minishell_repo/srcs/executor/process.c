#include "minishell.h"

static void	print_syntax_error(char *token_str)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (token_str)
		write(2, token_str, ft_strlen(token_str));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
}

static int	check_syntax_errors(t_token *final, t_shell *shell)
{
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
		return (1);
	}
	return (0);
}

static void	exec_branch(t_token *final, t_shell *shell, int is_pipe)
{
	t_cmd	*commands;

	commands = NULL;
	if (is_pipe)
		commands = parse_pipeline(final, shell);
	else
		commands = parse_tokens(final, shell);
	if (!commands)
	{
		if (shell->last_status == SIGINT_EXIT && is_heredoc(final))
			return ;
		shell->last_status = INVALID;
		if (is_pipe)
			print_syntax_error("|");
		return ;
	}
	if (is_pipe)
		execute_pipeline(commands, shell);
	else
		execute_commands(commands, shell);
	free_commands(commands);
}

static void	execute_token_list(t_token *final, t_shell *shell)
{
	int	is_pipe;

	is_pipe = has_pipes(final);
	exec_branch(final, shell, is_pipe);
}

/*static void	execute_token_list(t_token *final, t_shell *shell)
{
	t_cmd	*commands;

	if (has_pipes(final))
	{
		commands = parse_pipeline(final, shell);
		if (!commands)
		{	
			if (shell->last_status == SIGINT_EXIT && is_heredoc(final))
				return;
			shell->last_status = INVALID;
			print_syntax_error("|");
			return ;
		}
		execute_pipeline(commands, shell);
	}
	else
	{
		commands = parse_tokens(final, shell);
		if (!commands)
		{
			if (shell->last_status == SIGINT_EXIT && is_heredoc(final))
				return;
			shell->last_status = INVALID;
			return ;
		}
		execute_commands(commands, shell);
	}
	free_commands(commands);
}*/

void	process_tokens(t_token *tokens, char *line, t_shell *shell)
{
	t_token	*expanded;
	t_token	*final;

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
	if (check_syntax_errors(final, shell))
	{
		free_everything(line, final, NULL);
		return ;
	}
	execute_token_list(final, shell);
	free_everything(line, final, NULL);
}

#include "minishell.h"

t_cmd	*one_word_command(t_token *token_list)
{
	t_cmd	*new_command;

	new_command = NULL;
	new_command = ft_calloc(1, sizeof(t_cmd));
	if (!new_command)
		return (NULL);
	new_command->argv = super_split(token_list->str, ' ', '\t');
	return (new_command);
}

t_cmd	*words_plus_cmd(t_token *token_list)
{
	t_token	*current;
	t_cmd	*new_command;

	new_command = NULL;
	current = token_list;
	new_command = ft_calloc(1, sizeof(t_cmd));
	if (!new_command)
		return (NULL);
	while (current)
	{
		if (current->next && is_token_word(current->next))
			current = current->next;
		else
			break ;
	}
	if (is_token_word(current)
		&& current->next == NULL)
		new_command->argv = ultra_split(token_list);
	return (new_command);
}

static	t_token	*process_single_redirection(t_cmd *cmd, t_token *current)
{
	if (current->type == T_REDIR_IN && current->next)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(current->next->str);
		return (current->next->next);
	}
	else if (current->type == T_REDIR_OUT && current->next)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(current->next->str);
		cmd->append = 0;
		return (current->next->next);
	}
	else if (current->type == T_REDIR_APPEND && current->next)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(current->next->str);
		cmd->append = 1;
		return (current->next->next);
	}
	return (current->next);
}

static void	extract_redirections(t_cmd *cmd, t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
		current = process_single_redirection(cmd, current);
}

t_cmd	*build_command_with_redirections(t_token *token_list)
{
	t_cmd	*cmd;
	t_token	*argv_tokens;

	argv_tokens = NULL;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	extract_redirections(cmd, token_list);
	argv_tokens = filter_argv_tokens(token_list);
	cmd->argv = ultra_split(argv_tokens);
	free_tokens(argv_tokens);
	return (cmd);
}

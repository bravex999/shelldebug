#include "minishell.h"

static t_token	*copy_segment(t_token *a, t_token *b)
{
	t_token	*head;
	t_token	*cur;
	t_token	*nt;

	head = NULL;
	cur = a;
	while (cur && cur != b)
	{
		nt = create_token_safe(cur->type, ft_strdup(cur->str));
		if (!nt)
			return (free_tokens(head), NULL);
		nt->expand = cur->expand;
		nt->join_next = cur->join_next;
		nt->quoted_del = cur->quoted_del;
		add_token(&head, nt);
		cur = cur->next;
	}
	return (head);
}

static t_cmd	*parse_one_segment(t_token *seg, t_shell *sh)
{
	if (is_heredoc(seg))
		return (build_heredoc_cmd(seg, sh));
	if (has_redirections(seg))
		return (build_command_with_redirections(seg));
	if (is_token_word(seg) && seg->next == NULL)
		return (one_word_command(seg));
	if (is_token_word(seg) && seg->next != NULL)
		return (words_plus_cmd(seg));
	return (NULL);
}

t_cmd	*parse_pipeline(t_token *tokens, t_shell *sh)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_token	*cur;
	t_token	*start;
	t_token	*seg;
	t_cmd	*newc;

	head = NULL;
	tail = NULL;
	cur = tokens;
	start = tokens;
	while (cur)
	{
		if (cur->type == T_PIPE)
		{
			seg = copy_segment(start, cur);
			newc = parse_one_segment(seg, sh);
			free_tokens(seg);
			if (!newc)
				return (free_pipeline_list(head), NULL);
			newc->next = NULL;
			if (!head)
				head = newc;
			else
				tail->next = newc;
			tail = newc;
			start = cur->next;
		}
		cur = cur->next;
	}
	seg = copy_segment(start, NULL);
	newc = parse_one_segment(seg, sh);
	free_tokens(seg);
	if (!newc)
		return (free_pipeline_list(head), NULL);
	newc->next = NULL;
	if (!head)
		head = newc;
	else
		tail->next = newc;
	return (head);
}

void	free_pipeline_list(t_cmd *cmds)
{
	if (cmds)
		free_commands(cmds);
}

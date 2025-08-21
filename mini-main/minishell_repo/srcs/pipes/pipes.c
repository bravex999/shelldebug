#include "minishell.h"

t_token	*copy_segment(t_token *a, t_token *b)
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

t_cmd	*parse_one_segment(t_token *seg, t_shell *sh)
{
	if (!seg)
		return (NULL);
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

static int	append_cmd(t_cmd **head, t_cmd **tail, t_cmd *node)
{
	if (!node)
		return (1);
	node->next = NULL;
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (0);
}

static int	append_last_segment(t_token *start, t_shell *sh,
								t_cmd **head, t_cmd **tail)
{
	t_cmd	*node;

	node = build_segment_cmd(start, NULL, sh);
	return (append_cmd(head, tail, node));
}

t_cmd	*parse_pipeline(t_token *tokens, t_shell *sh)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_token	*cur;
	t_token	*start;

	head = NULL;
	tail = NULL;
	cur = tokens;
	start = tokens;
	while (cur)
	{
		if (cur->type == T_PIPE)
		{
			if (append_cmd(&head, &tail, build_segment_cmd(start, cur, sh)))
				return (free_commands(head), NULL);
			start = cur->next;
		}
		cur = cur->next;
	}
	if (append_last_segment(start, sh, &head, &tail))
		return (free_commands(head), NULL);
	return (head);
}

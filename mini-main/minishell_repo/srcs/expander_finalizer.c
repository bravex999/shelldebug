#include "minishell.h"

static t_token	*process_join_sequence(t_token **list_cursor)
{
	t_token	*current;
	char	*final_str;
	char	*temp_str;

	current = *list_cursor;
	final_str = ft_strdup(current->str);
	if (!final_str)
		return (NULL);
	while (current->join_next == 1 && current->next
		&& is_token_word(current) && is_token_word(current->next))
	{
		temp_str = ft_strjoin(final_str, current->next->str);
		free(final_str);
		if (!temp_str)
			return (NULL);
		final_str = temp_str;
		current = current->next;
	}
	*list_cursor = current->next;
	return (create_token_safe(T_WORD, final_str));
}

static	t_token	*dup_and_advance(t_token **cur)
{
	t_token	*t;

	t = create_token_safe((*cur)->type, ft_strdup((*cur)->str));
	if (t)
		t->join_next = (*cur)->join_next;
	*cur = (*cur)->next;
	return (t);
}

t_token	*finalize_and_join_tokens(t_token *list)
{
	t_token	*final_list;
	t_token	*current;
	t_token	*new_token;

	final_list = NULL;
	current = list;
	while (current)
	{
		if (current->join_next && current->next
			&& is_token_word(current) && is_token_word(current->next))
			new_token = process_join_sequence(&current);
		else
			new_token = dup_and_advance(&current);
		if (!new_token)
			return (free_tokens(final_list), NULL);
		add_token(&final_list, new_token);
	}
	return (final_list);
}

#include "minishell.h"

void	str_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	counter(const char *s, char c, char b)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if ((*s != c && *s != b) && (in_word == 0))
		{
			in_word = 1;
			count++;
		}
		else if (*s == c || *s == b)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, char b)
{
	char	*start;

	start = (char *)s;
	while (*s && *s != c && *s != b)
		s++;
	return (ft_substr(start, 0, s - start));
}

char	**super_split(char const *s, char c, char b)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = ft_calloc(counter(s, c, b) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c && *s != b)
		{
			result[i] = get_word(s, c, b);
			if (!result[i++])
				return (str_free(result), NULL);
			while (*s && *s != c && *s != b)
				s++;
		}
		if (*s)
			s++;
	}
	result[i] = NULL;
	return (result);
}

t_token	*filter_argv_tokens(t_token *tokens)
{
	t_token	*argv_list;
	t_token	*current;

	argv_list = NULL;
	current = tokens;
	while (current)
	{
		if (current->type < T_REDIR_IN || current->type > T_HEREDOC)
		{
			add_token(&argv_list, create_token_safe(current->type,
					ft_strdup(current->str)));
			current = current->next;
		}
		else
		{
			if (current->next)
				current = current->next->next;
			else
				current = current->next;
		}
	}
	return (argv_list);
}

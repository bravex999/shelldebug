#include "minishell.h"

t_cmd	*build_segment_cmd(t_token *start, t_token *end, t_shell *sh)
{
	t_token	*seg;
	t_cmd	*node;

	seg = copy_segment(start, end);
	node = parse_one_segment(seg, sh);
	free_tokens(seg);
	return (node);
}

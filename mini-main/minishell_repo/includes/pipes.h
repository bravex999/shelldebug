#include "minishell.h"

#ifndef PIPES_H
# define PIPES_H

typedef struct s_pipe_stage
{
	t_cmd	*cmd;
	int		idx;
	int		is_last;
	int		prev;
	int		nextfd[2];
	t_shell	*sh;
}	t_pipe_stage;

t_cmd	*parse_pipeline(t_token *tokens, t_shell *shell);
int		execute_pipeline(t_cmd *cmds, t_shell *shell);
void	free_pipeline_list(t_cmd *cmds);
t_cmd	*build_segment_cmd(t_token *start, t_token *end, t_shell *sh);
t_token	*copy_segment(t_token *a, t_token *b);
t_cmd	*parse_one_segment(t_token *seg, t_shell *sh);

#endif

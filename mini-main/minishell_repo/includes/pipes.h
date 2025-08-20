#include "minishell.h"

#ifndef PIPES_H
# define PIPES_H

t_cmd	*parse_pipeline(t_token *tokens, t_shell *shell);
int		execute_pipeline(t_cmd *cmds, t_shell *shell);
void	free_pipeline_list(t_cmd *cmds);

#endif

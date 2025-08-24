#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	if (!shell || !envp)
		return ;
	shell->envp = envp;
	shell->last_status = EXIT_OK;
	shell->running = 1;
	shell->cmds = NULL;
}

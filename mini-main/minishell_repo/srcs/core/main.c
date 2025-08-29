#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	start_loop(&shell);
	free_env(shell.envp);
	return (shell.last_status);
}

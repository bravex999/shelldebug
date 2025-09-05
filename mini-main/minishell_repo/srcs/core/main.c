#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (UNKNOWN_COMMAND);
	}
	init_shell(&shell, envp);
	setup_signals();
	start_loop(&shell);
	free_env(shell.envp);
	rl_clear_history();
	return (shell.last_status);
}

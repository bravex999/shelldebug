#include "minishell.h"

static void	setup_child_and_exec(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_heredoc_stdin(cmd, NULL) != 0)
		exit(EXIT_KO);
	execve(cmd_path, cmd->argv, shell->envp);
	exit(UNKNOWN_COMMAND);
}

int	create_and_wait_child(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		setup_signals();
		perror("fork");
		free(cmd_path);
		return (-1);
	}
	if (pid == 0)
		setup_child_and_exec(cmd_path, cmd, shell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	free(cmd_path);
	while (waitpid(pid, &status, 0) == -1)
		if (errno != EINTR)
			break ;
	setup_signals();
	handle_wait_status(status, shell);
	g_signal = 0;
	return (0);
}

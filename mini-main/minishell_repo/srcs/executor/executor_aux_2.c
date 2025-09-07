/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:07:51 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:07:56 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_and_exec(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	struct stat	st;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_heredoc_stdin(cmd, NULL) != 0)
		exit(EXIT_KO);
	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(STDERR_FILENO, ": is a directory\n", 17);
		exit(CMD_NOT_EXECUTABLE);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		perror(cmd->argv[0]);
		exit(CMD_NOT_EXECUTABLE);
	}
	execve(cmd_path, cmd->argv, shell->envp);
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		exit(CMD_NOT_EXECUTABLE);
	exit(UNKNOWN_COMMAND);
}

/*static void	setup_child_and_exec(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_heredoc_stdin(cmd, NULL) != 0)
		exit(EXIT_KO);
	execve(cmd_path, cmd->argv, shell->envp);
	exit(UNKNOWN_COMMAND);
}*/

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

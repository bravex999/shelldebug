#include "minishell.h"

static void	apply_redirs(t_cmd *c)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (setup_input_redirection(c, &in) != 0)
		exit(EXIT_KO);
	if (setup_output_redirection(c, &out) != 0)
		exit(EXIT_KO);
}

static void	exec_command(t_pipe_stage *st)
{
	char	*path;

	if (!st->cmd->argv || !st->cmd->argv[0])
		exit(EXIT_OK);
	if (is_builtin(st->cmd->argv[0]))
	{
		execute_builtin(st->cmd, st->sh);
		exit(st->sh->last_status);
	}
	path = resolve_command_path(st->cmd->argv[0], st->sh);
	if (!path)
	{
		write(STDERR_FILENO, st->cmd->argv[0], ft_strlen(st->cmd->argv[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(UNKNOWN_COMMAND);
	}
	execve(path, st->cmd->argv, st->sh->envp);
	write(STDERR_FILENO, st->cmd->argv[0], ft_strlen(st->cmd->argv[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(UNKNOWN_COMMAND);
}

void	exec_child_stage(t_pipe_stage *st)
{
	int	here_flag;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	here_flag = (st->cmd->heredoc_content != NULL);
	if (setup_heredoc_stdin(st->cmd, NULL) != 0)
		exit(EXIT_KO);
	if (st->idx > 0 && !st->cmd->infile && !here_flag)
		dup2(st->prev, STDIN_FILENO);
	if (!st->is_last && !st->cmd->outfile)
		dup2(st->nextfd[1], STDOUT_FILENO);
	if (st->prev != -1)
		close(st->prev);
	if (!st->is_last)
	{
		close(st->nextfd[0]);
		close(st->nextfd[1]);
	}
	apply_redirs(st->cmd);
	if (!st->cmd->argv || !st->cmd->argv[0])
		exit(EXIT_OK);
	exec_command(st);
}

static void	update_status(pid_t p, pid_t last, int st, t_shell *sh)
{
	if (p == last)
	{
		if (WIFEXITED(st))
		{	
			sh->last_status = WEXITSTATUS(st);
			if (sh->last_status == 130)
				write(STDOUT_FILENO, "\n", 1);
		}		
		else if (WIFSIGNALED(st))
		{
			sh->last_status = 128 + WTERMSIG(st);
			if (WTERMSIG(st) == SIGINT)
				sh->need_newline = 1;
		}
	}
}

void	wait_last_and_reap(pid_t last, int n, t_shell *sh)
{
	int		i;
	int		st;
	pid_t	p;

	i = 0;
	while (i < n)
	{
		p = wait(&st);
		while (p == -1 && errno == EINTR)
			p = wait(&st);
		if (p == -1)
			break ;
		update_status(p, last, st, sh);
		i++;
	}
	g_signal = 0;
}

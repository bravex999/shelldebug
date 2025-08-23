#include "minishell.h"
#include <signal.h>
#include <errno.h>
#include <unistd.h>


void	exec_child_stage(t_pipe_stage *st);
void	wait_last_and_reap(pid_t last, int n, t_shell *sh);

static void	cleanup_fds(t_pipe_stage *st, int *fd)
{
	if (st->prev != -1)
		close(st->prev);
	if (!st->is_last)
	{
		close(fd[1]);
		st->prev = fd[0];
	}
	else
		st->prev = -1;
}

static int	run_stage(t_pipe_stage *st, t_cmd **next_cmd, pid_t *plast)
{
	int		fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	if (st->cmd->next && pipe(fd) == -1)
		return (1);
	st->is_last = (st->cmd->next == NULL);
	st->nextfd[0] = fd[0];
	st->nextfd[1] = fd[1];
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		exec_child_stage(st);
	cleanup_fds(st, fd);
	*plast = pid;
	*next_cmd = st->cmd->next;
	st->idx++;
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_shell *sh)
{
	t_pipe_stage	st;
	pid_t			last;

	st.cmd = cmds;
	st.idx = 0;
	st.prev = -1;
	st.sh = sh;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	last = -1;
	while (st.cmd)
	{
		if (run_stage(&st, &st.cmd, &last) != 0)
			return (1);
	}
	wait_last_and_reap(last, st.idx, sh);
	setup_signals();
	return (0);
}

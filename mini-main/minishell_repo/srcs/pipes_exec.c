#include "minishell.h"

static void	apply_redirs(t_cmd *c)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (setup_input_redirection(c, &in) != 0)
		exit(1);
	if (setup_output_redirection(c, &out) != 0)
		exit(1);
}

static void	exec_child_stage(t_cmd *c, int idx, int last, int prev, int nextfd[2], t_shell *sh)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_heredoc_stdin(c, NULL) != 0)
		exit(1);
	if (idx > 0 && !c->infile)
		dup2(prev, STDIN_FILENO);
	if (!last && !c->outfile)
		dup2(nextfd[1], STDOUT_FILENO);
	if (prev != -1)
		close(prev);
	if (!last)
	{
		close(nextfd[0]);
		close(nextfd[1]);
	}
	apply_redirs(c);
	if (is_builtin(c->argv[0]))
	{
		execute_builtin(c, sh);
		exit(sh->last_status);
	}
	path = resolve_command_path(c->argv[0], sh);
	if (!path)
		exit(127);
	execve(path, c->argv, sh->envp);
	exit(127);
}

static void	wait_last_and_reap(pid_t last, int n, t_shell *sh)
{
	int		i;
	int		st;
	pid_t	p;

	i = 0;
	while (i < n)
	{
		while ((p = wait(&st)) == -1 && errno == EINTR)
			;
		if (p == last)
		{
			if (WIFEXITED(st))
				sh->last_status = WEXITSTATUS(st);
			else if (WIFSIGNALED(st))
				sh->last_status = 128 + WTERMSIG(st);
		}
		i++;
	}
}

int	execute_pipeline(t_cmd *cmds, t_shell *sh)
{
	int		prev;
	int		fd[2];
	int		i;
	pid_t	last;

	prev = -1;
	i = 0;
	last = -1;
	while (cmds)
	{
		if (cmds->next && pipe(fd) == -1)
			return (1);
		last = fork();
		if (last == 0)
			exec_child_stage(cmds, i, (cmds->next == NULL), prev, fd, sh);
		if (prev != -1)
			close(prev);
		if (cmds->next)
		{
			close(fd[1]);
			prev = fd[0];
		}
		else
			prev = -1;
		cmds = cmds->next;
		i++;
	}
	wait_last_and_reap(last, i, sh);
	return (0);
}


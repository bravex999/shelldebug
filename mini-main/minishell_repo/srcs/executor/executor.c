#include "minishell.h"

void	restore_stdin_from_saved(int *saved_stdin);
void	run_external(t_cmd *cmd, t_shell *shell);
int		is_builtin(char *cmd);

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
/*	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);*/
	return (0);
}

static int	check_redir(int result, int *saved_stdin, int *saved_stdout)
{
	if (result != 0)
	{
		restore_redirections(saved_stdin, saved_stdout);
		return (1);
	}
	return (0);
}

static int	only_redirs_set_status(t_cmd *cmd, t_shell *sh)
{
	int	st;

	if (cmd && (!cmd->argv || !cmd->argv[0]))
	{
		st = handle_only_redirections(cmd);
		if (st == 0)
			sh->last_status = 0;
		else
			sh->last_status = 1;
		return (1);
	}
	return (0);
}

static int	prep(t_cmd *c, t_shell *sh, int *in, int *out)
{
	if (check_redir(setup_heredoc_stdin(c, in), in, out))
	{
		sh->last_status = 1;
		return (1);
	}
	if (check_redir(setup_input_redirection(c, in), in, out))
	{
		sh->last_status = 1;
		return (1);
	}
	if (check_redir(setup_output_redirection(c, out), in, out))
	{
		sh->last_status = 1;
		return (1);
	}
	return (0);
}

void	execute_commands(t_cmd *cmds, t_shell *sh)
{
	int	in;
	int	out;

	out = -1;
	in = -1;
	if (!cmds)
		return ;
	if (only_redirs_set_status(cmds, sh))
		return ;
	if (prep(cmds, sh, &in, &out))
		return ;
	if (is_builtin(cmds->argv[0]))
		execute_builtin(cmds, sh);
	else
		run_external(cmds, sh);
	restore_redirections(&in, &out);
}

/*void	execute_commands(t_cmd *commands, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdout = -1;
	saved_stdin = -1;
	if (!commands)
		return ;
	if (only_redirs_set_status(commands, shell))
		return ;
	if (check_redir(setup_heredoc_stdin(commands, &saved_stdin),
			&saved_stdin, &saved_stdout))
		return ;
	if (check_redir(setup_input_redirection(commands, &saved_stdin),
			&saved_stdin, &saved_stdout))
		return ;
	if (check_redir(setup_output_redirection(commands, &saved_stdout),
			&saved_stdin, &saved_stdout))
		return ;
	if (is_builtin(commands->argv[0]))
		execute_builtin(commands, shell);
	else
		run_external(commands, shell);
	restore_redirections(&saved_stdin, &saved_stdout);
}*/

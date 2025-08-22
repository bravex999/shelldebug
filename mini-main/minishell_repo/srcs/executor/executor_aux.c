#include "minishell.h"

char	**ultra_split(t_token *token_list)
{
	int		i;
	char	**argv;
	int		word;
	t_token	*current;

	current = token_list;
	word = 0;
	i = 0;
	argv = NULL;
	while (current)
	{
		word++;
		current = current->next;
	}
	current = token_list;
	argv = malloc(sizeof(char *) * (word + 1));
	while (current)
	{
		argv[i] = ft_strdup(current->str);
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;

	saved_stdin = -1;
	if (setup_heredoc_stdin(cmd, &saved_stdin) != 0)
	{
		restore_stdin_from_saved(&saved_stdin);
		return ;
	}
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd, shell);
/*  else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        funcion_pwd(cmd, shell);
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        funcion_cd(cmd, shell);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        funcion_unset(cmd, shell);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        funcion_export(cmd, shell);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        funcion_env(cmd, shell);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        funcion_exit(cmd, shell);*/
	restore_stdin_from_saved(&saved_stdin);
}

void	handle_wait_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
	{
		shell->last_status = WEXITSTATUS(status);
		if (shell->last_status == 130)
			shell->need_newline = 1;
		return ;
	}
	if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			shell->need_newline = 1;
		return ;
	}
}

void	run_external(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	cmd_path = resolve_command_path(cmd->argv[0], shell);
	if (!cmd_path)
	{
		write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		shell->last_status = UNKNOWN_COMMAND;
		return ;
	}
	create_and_wait_child(cmd_path, cmd, shell);
}

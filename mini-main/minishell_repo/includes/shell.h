#ifndef SHELL_H
# define SHELL_H

typedef struct s_shell {
	char			**envp;
	int				last_status;
	int				running;
	struct s_cmd	*cmds;
	int				need_newline;
}					t_shell;

void	init_shell(t_shell *shell, char **envp);
char	**copy_env(char **envp);
void	free_env(char **env);
char	*get_env_value(t_shell *sh, const char *name);

#endif

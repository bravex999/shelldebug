#include "minishell.h"

char	*read_input(void)
{
	return (readline("minishell$ "));
}

int	check_ctrl_d(char *line)
{
	if (!line)
	{
		printf("exit\n");
		rl_clear_history();
		return (1);
	}
	return (0);
}

int	handle_ctrl_c_signal(char **line, t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		return (handle_ctrl_c(line, shell));
	}	
	return (0);
}

int	history(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line != '\0');
}

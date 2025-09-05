#include "minishell.h"

char	*read_input(void)
{
	return (readline("\001\033[1;36m\002minishell$\001\033[0m\002 "));
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
	char	*p;

	if (g_signal != SIGINT)
		return (0);
	shell->last_status = SIGINT_EXIT;
	p = *line;
	while (p && (*p == ' ' || *p == '\t'))
		p++;
	if (!p || *p == '\0')
	{
		g_signal = 0;
		free(*line);
		*line = NULL;
		return (1);
	}
	g_signal = 0;
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

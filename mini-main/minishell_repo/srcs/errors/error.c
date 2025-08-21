#include "minishell.h"

static void	putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	print_error(char *cmd, char *arg, char *message)
{
	putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		putstr_fd(cmd, STDERR_FILENO);
		putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		putstr_fd(arg, STDERR_FILENO);
		putstr_fd(": ", STDERR_FILENO);
	}
	if (message)
		putstr_fd(message, STDERR_FILENO);
	putstr_fd("\n", STDERR_FILENO);
}

void	print_cmd_error(char *cmd, char *message)
{
	print_error(cmd, NULL, message);
}

void	print_file_error(char *cmd, char *filename)
{
	print_error(cmd, filename, (char *)strerror(errno));
}

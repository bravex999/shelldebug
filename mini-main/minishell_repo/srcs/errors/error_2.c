#include "minishell.h"

void	error_cd_home_not_set(void)
{
	print_cmd_error("cd", "HOME not set");
}

void	error_cd_no_such_file(char *path)
{
	print_error("cd", path, (char *)strerror(errno));
}

void	error_export_invalid_identifier(char *identifier)
{
	print_error("export", identifier, "not a valid identifier");
}

void	error_unset_invalid_identifier(char *identifier)
{
	print_error("unset", identifier, "not a valid identifier");
}

void	error_exit_numeric_required(char *arg)
{
	print_error("exit", arg, "numeric argument required");
}

#include "minishell.h"

#ifndef ERROR_H
# define ERROR_H

void	print_error(char *cmd, char *arg, char *message);
void	print_cmd_error(char *cmd, char *message);
void	print_file_error(char *cmd, char *filename);
void	error_cd_home_not_set(void);
void	error_cd_no_such_file(char *path);
void	error_export_invalid_identifier(char *identifier);
void	error_unset_invalid_identifier(char *identifier);
void	error_exit_numeric_required(char *arg);
int		is_numeric(char *str);
int		is_valid_identifier(char *str);

#endif

#include "minishell.h"

#ifndef MAIN_AUX_H
# define MAIN_AUX_H

void	start_loop(t_shell *shell);
int		handle_ctrl_c(char **line, t_shell *shell);
int		check_ctrl_d(char *line);
char	*read_input(void);
int		handle_ctrl_c_signal(char **line, t_shell *shell);
int		history(char *line);
void    process_tokens(t_token *tokens, char *line, t_shell *shell);

#endif

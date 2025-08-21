#include "minishell.h"

#ifndef SIGNALS_H
# define SIGNALS_H

extern volatile sig_atomic_t	g_signal;

void	setup_signals(void);
void	set_sigint_interactive(void);
void	set_sigint_heredoc(void);

#endif

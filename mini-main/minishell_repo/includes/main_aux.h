/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:27:02 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:37:52 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_AUX_H
# define MAIN_AUX_H

void	start_loop(t_shell *shell);
int		check_ctrl_d(char *line);
char	*read_input(void);
int		handle_ctrl_c_signal(char **line, t_shell *shell);
int		history(char *line);
void	process_tokens(t_token *tokens, char *line, t_shell *shell);

#endif

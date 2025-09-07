/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:26:09 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:34:34 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	execute_commands(t_cmd *commands, t_shell *shell);
int		ft_strcmp(char *s1, char *s2);
char	**ultra_split(t_token *token_list);
void	execute_builtin(t_cmd *cmd, t_shell *shell);
int		setup_heredoc_stdin(t_cmd *cmd, int *saved_stdin);
void	restore_stdin_from_saved(int *saved_stdin);
void	run_external(t_cmd *cmd, t_shell *shell);
int		is_builtin(char *cmd);
int		create_and_wait_child(char *cmd_path, t_cmd *cmd, t_shell *shell);
void	handle_wait_status(int status, t_shell *shell);
int		handle_only_redirections(t_cmd *cmd);

#endif

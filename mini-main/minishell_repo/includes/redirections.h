/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:28:26 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:38:35 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

int		setup_input_redirection(t_cmd *cmd, int *saved_stdin);
int		setup_output_redirection(t_cmd *cmd, int *saved_stdout);
void	restore_redirections(int *saved_stdin, int *saved_stdout);

#endif

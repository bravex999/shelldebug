/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:25:16 by chnaranj          #+#    #+#             */
/*   Updated: 2025/09/07 17:33:49 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd, t_shell *shell);
}	t_builtin;

int		ft_cd(t_cmd *cmd, t_shell *shell);
char	*ft_getenv(char **envp, const char *key);
void	ft_setenv(char ***envp, const char *key, const char *value);
char	*resolve_cd_argument(char *arg, t_shell *shell);
char	*resolve_cd_target(t_cmd *cmd, t_shell *shell);
void	update_pwd_and_oldpwd(t_shell *shell);
char	*build_env_var(const char *key, const char *value);
char	*expand_home(char *arg, t_shell *shell);
int		ft_pwd(t_cmd *cmd, t_shell *shell);
int		ft_echo(t_cmd *cmd, t_shell *shell);
int		builtin_export(t_cmd *cmd, t_shell *shell);
char	**sort_envp(char **envp);
int		is_valid_identifier_aux(const char *str);
void	print_export_error(const char *arg);
int		ft_env(t_cmd *cmd, t_shell *shell);
int		ft_exit(t_cmd *cmd, t_shell *shell);
void	free_env_array(char **envp);
int		ft_unset(t_cmd *cmd, t_shell *shell);
int		exec_builtin(t_cmd *cmd, t_shell *shell);

#endif

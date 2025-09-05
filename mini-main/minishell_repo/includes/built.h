#include "minishell.h" 

#ifndef BUILT_H
#define BUILT_H
 // incluye todos los typedefs que necesites, como t_cmd, t_shell, t_env

// ⚠️ Definición de t_builtin antes de usarlo
typedef struct s_builtin
{
    char *name;
    int (*func)(t_cmd *cmd, t_shell *shell);
} t_builtin;

// Declaración del array externo
extern t_builtin builtins[];

// Prototipos de funciones built-in

// CD
int ft_cd(t_cmd *cmd, t_shell *shell);
char *ft_getenv(char **envp, const char *key);
void ft_setenv(char ***envp, const char *key, const char *value);
char *resolve_cd_argument(char *arg, t_shell *shell);
char *resolve_cd_target(t_cmd *cmd, t_shell *shell);
void update_pwd_and_oldpwd(t_shell *shell);
char *build_env_var(const char *key, const char *value);
char *expand_home(char *arg, t_shell *shell);
// CD FIN

// PWD
int ft_pwd(t_cmd *cmd, t_shell *shell);
// PWD FIN

int ft_echo(t_cmd *cmd, t_shell *shell);

// EXPORT
int builtin_export(t_cmd *cmd, t_shell *shell);
char **sort_envp(char **envp);
int is_valid_identifier_aux(const char *str);
void print_export_error(const char *arg);

// ENV
int ft_env(t_cmd *cmd, t_shell *shell);

// EXIT
int ft_exit(t_cmd *cmd, t_shell *shell);
void free_env_array(char **envp);

// UNSET
int ft_unset(t_cmd *cmd, t_shell *shell);

// Ejecutar builtins
int exec_builtin(t_cmd *cmd, t_shell *shell);
//char *get_env_value(char *var, t_shell *shell);

#endif

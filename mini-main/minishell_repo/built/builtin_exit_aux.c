#include "minishell.h"

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free (envp[i++]);
	free(envp);
}

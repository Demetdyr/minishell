#include "../inc/minishell.h"
#include <stdlib.h>

void	ft_free_shell_single(t_shell **shell)
{
	int	i;

	if (!shell || !*shell)
		return ;
	i = 0;
	while ((*shell)->env && (*shell)->env[i])
		free((*shell)->env[i++]);
	free((*shell)->env);
	(*shell)->env = NULL;
	free((*shell)->prompt);
	(*shell)->prompt = NULL;
}

void	ft_free_path(char **path)
{
	int	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_free_env(char **copy_env, int i)
{
	if (!copy_env)
		return ;
	if (i > 0)
		while (i--)
			free(copy_env[i]);
	free(copy_env);
}

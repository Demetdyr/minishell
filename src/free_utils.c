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

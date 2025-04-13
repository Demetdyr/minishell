#include "../inc/minishell.h"
#include <stdlib.h>

static void	free_env(char **copy_env, int i)
{
	if (!copy_env)
		return ;
	if (i > 0)
		while (i--)
			free(copy_env[i]);
	free(copy_env);
}

char	**env_copy(char **env)
{
	char	**env_copy;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
			return (free_env(env_copy, i), NULL);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

static t_shell	*shell_init(char **argv, char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env_copy(env);
	if (!shell->env)
	return (free_shell(&shell), NULL);
	shell->argv = argv;
	shell->prompt = NULL;
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	t_shell	*shell;

	shell = shell_init(argv, env);
}
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
	shell->err = 0;
	return (shell);
}

static void	ft_routine(t_shell *shell)
{
	while (1)
	{
		//shell->prompt = readline("minishell> ");
		//if (!shell->prompt)
		//	break ;
		//add_history(shell->prompt);
		shell->err = ft_syntax_check(shell);
		if (shell->err)
		{
			ft_print_syntax_err(shell->err, shell);
			ft_free_prompt(shell);
			continue ;
		}
		shell->err = 0;
		shell->token_lst = ft_lexer(shell);
		if (!shell->token_lst)
		{
			free(shell->prompt);
			continue ;
		}
		//executer
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	shell = shell_init(argv, env);
	if (!shell)
		return (argc);
	ft_routine(shell);
	return (ft_free_shell(&shell), shell->status);
}

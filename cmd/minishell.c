/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:13 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/21 02:08:56 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	g_sig = 0;

char	**ft_env_copy(char **env)
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
			return (ft_free_env(env_copy, i), NULL);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

static t_shell	*ft_shell_init(char **argv, char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = ft_env_copy(env);
	if (!shell->env)
		return (ft_free_shell(&shell), NULL);
	shell->export_only = NULL;
	shell->argv = argv;
	shell->prompt = NULL;
	shell->err = 0;
	shell->cmd_count = 0;
	shell->status = 0;
	shell->token_lst = NULL;
	shell->oldpwd = NULL;
	return (shell);
}

static int	ft_route_in(t_shell *shell)
{
	if (shell->err)
	{
		ft_print_syntax_err(shell->err, shell);
		ft_free_prompt(shell);
		return (CONTINUE);
	}
	shell->err = 0;
	shell->token_lst = ft_lexer(shell);
	if (!shell->token_lst)
	{
		free(shell->prompt);
		return (CONTINUE);
	}
	ft_start_exec(shell);
	return (SUCCESS);
}

static void	ft_routine(t_shell *shell)
{
	while (1)
	{
		g_sig = 0;
		shell->prompt = readline("minishell> ");
		if (!shell->prompt)
		{
			fdprintln(1, "exit");
			break ;
		}
		add_history(shell->prompt);
		if (!shell->prompt)
			continue ;
		shell->err = ft_syntax_check(shell);
		if (ft_route_in(shell) == CONTINUE)
			continue ;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		err_sta;

	ft_check_signal();
	shell = ft_shell_init(argv, env);
	if (!shell)
		return (argc);
	ft_routine(shell);
	err_sta = shell->status;
	return (clear_history(), ft_free_shell(&shell), err_sta);
}

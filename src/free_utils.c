/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:18 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/19 16:24:59 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

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

void	ft_free_shell_cmd_exit(t_shell *shell, t_cmd *cmd, int status)
{
	ft_free_cmd(cmd);
	ft_free_shell(&shell);
	exit(status);
}

void	ft_free_shell_cmd_exit_status(t_shell *shell, t_cmd *cmd, pid_t *pid, int **pipe_fd)
{
	int	status;
	int	pipe_count;

	if (pid)
		free(pid);
	if (pipe_fd)
	{
		pipe_count = ft_count_tokens(shell->token_lst) - 1;
		ft_free_pipe(pipe_fd, pipe_count);
	}
	ft_free_cmd(cmd);
	status = shell->status;
	ft_free_shell(&shell);
	exit(status);
}

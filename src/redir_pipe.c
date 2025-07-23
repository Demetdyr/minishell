/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:55:18 by mehcakir          #+#    #+#             */
/*   Updated: 2025/07/23 15:27:09 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static void	ft_free_pipe_heredoc(pid_t *pid, int **pipe_fd, t_shell *shell)
{
	int	pipe_count;

	if (pid)
		free(pid);
	if (pipe_fd)
	{
		pipe_count = ft_count_tokens(shell->token_lst) - 1;
		ft_free_pipe(pipe_fd, pipe_count);
	}
}

static int	ft_check_redll_pipe(t_token *token, int index, t_cmd *cmd,
	t_pipe pipes)
{
	char	*str;
	int		fd[2];
	t_token	*iter;
	pid_t	pid_temp;
	int		status;

	str = NULL;
	if (!token || !token->next || pipe(fd) == -1)
		return (FAILURE);
	iter = token->next;
	g_sig = IN_HEREDOC;
	pid_temp = fork();
	if (pid_temp == -1)
		return (close(fd[0]), close(fd[1]), FAILURE);
	else if (pid_temp == 0)
		return (ft_free_pipe_heredoc(pipes.pid, pipes.pipe_fd, cmd->shell),
			ft_free_cmd(cmd), ft_check_redll_child(fd, str, iter, cmd->shell),
			FAILURE);
	else
	{
		close(fd[1]);
		waitpid(pid_temp, &status, 0);
		return (ft_check_redll_parent(fd, cmd, index, &status));
	}
	return (FAILURE);
}

int	ft_config_heredoc_fd_pipe(t_token *token, int index, t_cmd *cmd,
	t_pipe pipe)
{
	int	ret;

	if (!token)
		return (FAILURE);
	while (token)
	{
		if (token->type == RED_LL)
		{
			ret = ft_check_redll_pipe(token, index, cmd, pipe);
			if (ret != SUCCESS)
			{
				if (ret > 128)
				{
					cmd->shell->status = ret;
					return (FAILURE);
				}
				return (FAILURE);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

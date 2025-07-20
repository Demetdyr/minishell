/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:55:18 by mehcakir          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:49 by mehcakir         ###   ########.fr       */
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
				t_shell *shell, pid_t *pid, int **pipe_fd)
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
		return (ft_free_pipe_heredoc(pid, pipe_fd, shell), ft_free_cmd(cmd),
			ft_check_redll_child(fd, str, iter, shell), FAILURE);
	else
	{
		close(fd[1]);
		waitpid(pid_temp, &status, 0);
		return (ft_check_redll_parent(fd, cmd, index, &status));
	}
	return (FAILURE);
}

int	ft_config_heredoc_fd_pipe(t_token *token, int index, t_cmd *cmd,
		t_shell *shell, pid_t *pid, int **pipe_fd)
{
	int	ret;

	if (!token)
		return (FAILURE);
	while (token)
	{
		if (token->type == RED_LL)
		{
			ret = ft_check_redll_pipe(token, index, cmd, shell, pid, pipe_fd);
			if (ret != SUCCESS)
			{
				if (ret > 128)
				{
					shell->status = ret;
					return (FAILURE);
				}
				return (FAILURE);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

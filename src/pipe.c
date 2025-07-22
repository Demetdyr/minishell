/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:39 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/23 00:22:26 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

int	**ft_free_pipe(int **pipe_fd, int pipe_count)
{
	if (!pipe_fd)
		return (NULL);
	if (pipe_count <= 0)
		return (free(pipe_fd), NULL);
	pipe_count--;
	while (pipe_count >= 0)
	{
		free(pipe_fd[pipe_count]);
		pipe_count--;
	}
	free(pipe_fd);
	return (NULL);
}

int	**ft_init_pipe(int pipe_count, t_shell *shell)
{
	int	**pipe_fd;
	int	i;

	pipe_fd = (int **)malloc(sizeof(int *) * (pipe_count));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			return (ft_free_pipe(pipe_fd, i));
		i++;
	}
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipe_fd[i]) == -1)
			return (ft_free_pipe(pipe_fd, i), NULL);
		ft_add_fd(shell, pipe_fd[i][0]);
		ft_add_fd(shell, pipe_fd[i][1]);
		i++;
	}
	return (pipe_fd);
}

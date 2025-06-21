#include "minishell.h"

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

int	**ft_init_pipe(int pipe_count)
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
		i++;
	}
	return (pipe_fd);
}

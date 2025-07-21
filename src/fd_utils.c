/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:31:53 by mehcakir          #+#    #+#             */
/*   Updated: 2025/07/21 17:32:16 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void	ft_add_fd(t_shell *shell, int fd)
{
	int	i;

	if (!shell || fd < 0)
		return ;
	i = 0;
	while (i < shell->fd_count)
	{
		if (shell->fd_list[i] == fd)
			return ;
		i++;
	}
	if (shell->fd_count < 256)
		shell->fd_list[shell->fd_count++] = fd;
}

void	ft_close_all_fds(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	i = 0;
	while (i < shell->fd_count)
	{
		if (shell->fd_list[i] > 2)
			close(shell->fd_list[i]);
		shell->fd_list[i] = -1;
		i++;
	}
	shell->fd_count = 0;
}

void	ft_init_fd_list(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	shell->fd_count = 0;
	i = 0;
	while (i < 256)
		shell->fd_list[i++] = -1;
}

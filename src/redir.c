/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:51 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/20 11:03:20 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <signal.h>
#include <unistd.h>

int	ft_config_heredoc_fd(t_token *token, int index, t_cmd *cmd, t_shell *shell)
{
	int	ret;

	if (!token)
		return (FAILURE);
	while (token)
	{
		if (token->type == RED_LL)
		{
			ret = ft_check_redll(token, index, cmd, shell);
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

static int	ft_check_fds(t_token *token, t_shell *shell, t_cmd *cmd,
	bool last_heredoc)
{
	while (token)
	{
		if (token->type == RED_L)
		{
			if (ft_check_redl(token, shell, cmd, last_heredoc) != SUCCESS)
				return (FAILURE);
		}
		else if (token->type == RED_R)
		{
			if (ft_check_redr(token, shell, cmd) != SUCCESS)
				return (FAILURE);
		}
		else if (token->type == RED_RR)
		{
			if (ft_check_redrr(token, shell, cmd) != SUCCESS)
				return (FAILURE);
		}
		token = token->next;
		if (!token)
			break ;
	}
	return (SUCCESS);
}

int	ft_config_redir_fd(t_token *token, t_shell *shell, t_cmd *cmd)
{
	bool	last_heredoc;
	t_token	*iter;

	if (!token)
		return (FAILURE);
	last_heredoc = false;
	iter = token;
	while (iter)
	{
		if (iter->type == RED_LL)
			last_heredoc = true;
		else if (iter->type == RED_L)
			last_heredoc = false;
		iter = iter->next;
	}
	if (ft_check_fds(token, shell, cmd, last_heredoc) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

void	ft_check_redll_child(int fd[2], char *str, t_token *iter,
		t_shell *shell)
{
	int		empty_input;
	char	delimiter[PATH_MAX];
	int		delim_len;

	empty_input = 1;
	close(fd[0]);
	delim_len = ft_strlen(iter->value);
	if (delim_len >= PATH_MAX)
	{
		ft_free_shell(&shell);
		exit(1);
	}
	delim_len = 0;
	while (iter->value[delim_len] && delim_len < PATH_MAX - 1)
	{
		delimiter[delim_len] = iter->value[delim_len];
		delim_len++;
	}
	delimiter[delim_len] = '\0';
	ft_free_shell(&shell);
	signal(SIGINT, ft_sigint_heredoc_handler);
	ft_heredoc_child_handler(str, empty_input, delimiter, fd);
}

int	ft_check_redll_parent(int fd[2], t_cmd *cmd, int index, int *status)
{
	int	exit_status;

	g_sig = AFTER_HEREDOC;
	exit_status = ((*status >> 8) & 0xFF);
	if (exit_status == 1)
	{
		close(fd[0]);
		return (FAILURE);
	}
	if (exit_status == 130)
	{
		close(fd[0]);
		return (130);
	}
	if (cmd->heredoc_fd[index] != NO_FD)
		close(cmd->heredoc_fd[index]);
	cmd->heredoc_fd[index] = fd[0];
	return (SUCCESS);
}

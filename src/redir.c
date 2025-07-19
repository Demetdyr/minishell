/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:51 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/19 20:48:46 by mehcakir         ###   ########.fr       */
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

void	ft_check_redll_child(int fd[2], char *str, t_token *iter, t_shell *shell, t_cmd *cmd)
{
	int		empty_input;
	char	delimiter[PATH_MAX];
	int		delim_len;

	empty_input = 1;
	close(fd[0]);
	delim_len = ft_strlen(iter->value);
	if (delim_len >= PATH_MAX)
	{
		ft_free_cmd(cmd);
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
	ft_free_cmd(cmd);
	ft_free_shell(&shell);
	signal(SIGINT, SIG_DFL);
	while (true)
	{
		str = readline("> ");
		if (!str)
		{
			fdprintln(2, ERR_STR_CTRL_D_EOF);
			break ;
		}
		empty_input = 0;
		if (ft_strcmp(str, delimiter) == 0)
		{
			free(str);
			str = NULL;
			break ;
		}
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		free(str);
		str = NULL;
	}
	close(fd[1]);
	if (empty_input == 1)
		exit(1);
	exit(0);
}

int	ft_check_redll_parent(int fd[2], t_cmd *cmd, int index, int *status)
{
	int	exit_status;
	int	sig;

	g_sig = AFTER_HEREDOC;
	if ((*status & 0x7F) != 0)
	{
		sig = *status & 0x7F;
		close(fd[0]);
		return (128 + sig);
	}
	else
	{
		exit_status = ((*status >> 8) & 0xFF);
		if (exit_status == 1)
		{
			close(fd[0]);
			return (FAILURE);
		}
		if (cmd->heredoc_fd[index] != NO_FD)
			close(cmd->heredoc_fd[index]);
		cmd->heredoc_fd[index] = fd[0];
		return (SUCCESS);
	}
}

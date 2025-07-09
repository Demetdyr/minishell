/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:51 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:52 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_config_heredoc_fd(t_token *token, int index, t_cmd *cmd)
{
	if (!token)
		return (FAILURE);
	while (token)
	{
		if (token->type == RED_LL)
			if (ft_check_redll(token, index, cmd) != SUCCESS)
				return (FAILURE);
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

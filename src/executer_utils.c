/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:14 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/18 19:59:00 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_init_cmd(t_cmd *cmd, int token_count)
{
	int	i;

	cmd->argv = NULL;
	cmd->cmd = NULL;
	cmd->in_fd = NO_FD;
	cmd->out_fd = NO_FD;
	cmd->index = 0;
	cmd->count = 0;
	cmd->bin = NO_FD;
	cmd->bout = NO_FD;
	cmd->heredoc_fd = (int *)malloc(sizeof(int) * token_count);
	if (!cmd->heredoc_fd)
		return (FAILURE);
	i = 0;
	while (i < token_count)
	{
		cmd->heredoc_fd[i] = NO_FD;
		i++;
	}
	return (SUCCESS);
}

bool	ft_has_cmd(t_token *token)
{
	if (!token)
		return (false);
	while (token)
	{
		if (token->type == CMD)
			return (true);
		token = token->next;
	}
	return (false);
}

int	ft_child_exit_status(int status)
{
	return ((status >> 8) & 0x000000ff);
}

int	ft_get_len_env(const char *value, int *len)
{
	char	*equals_pos;

	equals_pos = ft_strchr(value, '=');
	if (!equals_pos)
		return (FAILURE);
	*len = equals_pos - value;
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:10:10 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/23 15:11:15 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_tokens(t_token **token_lst)
{
	int	i;

	i = 0;
	if (!token_lst)
		return (0);
	while (token_lst[i])
		i++;
	return (i);
}

int	ft_count_tokens_arg(t_token *token)
{
	t_token		*iter;
	int			size;
	bool		in_arg;

	size = 0;
	in_arg = false;
	if (!token)
		return (FAILURE);
	iter = token;
	while (iter)
	{
		if (iter->type == ARG)
		{
			size++;
			in_arg = true;
		}
		else if (in_arg)
			break ;
		iter = iter->next;
	}
	return (size);
}

static int	ft_token_set_built(t_token *token, t_shell *shell, t_cmd *cmd,
	t_pipe pipe)
{
	if (ft_exec_built(token, shell, cmd, pipe) != SUCCESS)
	{
		token->value = NULL;
		return (ft_free_cmd(cmd), FAILURE);
	}
	token->value = NULL;
	return (ft_free_cmd(cmd), SUCCESS);
}

int	ft_config_cmd_arg_path(t_token *token, t_shell *shell, t_cmd *cmd,
	t_pipe pipe)
{
	char	*path;
	char	**argv;

	if (!token || !shell || !cmd)
		return (FAILURE);
	if (ft_is_built(token))
		return (ft_token_set_built(token, shell, cmd, pipe));
	path = ft_get_path(token, shell);
	if (!path)
	{
		if (shell->err != HANDLED)
			return (ft_print_err_exec(token, shell, 127, ERR_NO_CMD), FAILURE);
		return (FAILURE);
	}
	cmd->cmd = path;
	argv = ft_token_to_arg(token, path);
	if (!argv)
		return (free(path), FAILURE);
	cmd->argv = argv;
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:00 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/23 15:25:30 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_free_pipe_exit(t_pipe pipe, t_shell *shell)
{
	int	pipe_count;

	if (pipe.pid)
		free(pipe.pid);
	if (pipe.pipe_fd)
	{
		pipe_count = ft_count_tokens(shell->token_lst) - 1;
		ft_free_pipe(pipe.pipe_fd, pipe_count);
	}
}

static void	ft_free_cmd_exit(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->cmd = NULL;
	if (cmd->argv)
	{
		free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->heredoc_fd)
	{
		free(cmd->heredoc_fd);
		cmd->heredoc_fd = NULL;
	}
}

static bool	ft_is_digit_exit(const char *c)
{
	int	i;

	i = 0;
	if (c[i] == '-' || c[i] == '+')
		i++;
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_free_all_exit(t_shell *shell, t_cmd *cmd, t_pipe pipe)
{
	ft_free_pipe_exit(pipe, shell);
	ft_free_shell(&shell);
	ft_free_cmd_exit(cmd);
}

int	ft_exec_exit(t_token *token, t_shell *shell, t_cmd *cmd, t_pipe pipe)
{
	int	err_num;

	err_num = 0;
	if (!token)
		ft_print_err_general("Invalid arguments\n", 2);
	fdprintln(2, "exit");
	if (token && token->next && token->next->next)
		return (ft_print_err_exec(token, shell, 1, ERR_MANY_ARGS));
	if (token->next && !ft_is_digit_exit(token->next->value))
		return (ft_print_err_exec(token, shell, 2, ERR_NOT_NUMERIC),
			ft_free_all_exit(shell, cmd, pipe), exit(2), FAILURE);
	if (token->next)
	{
		err_num = ft_atoi(token->next->value);
		if (err_num < 0)
			return (ft_print_err_exec(token, shell, (int)(256
					+ (err_num % 256)), ERR_OTHER),
						ft_free_all_exit(shell, cmd, pipe),
							exit(err_num), FAILURE);
		return (ft_print_err_exec(token, shell, (int)(err_num % 256),
			ERR_OTHER), ft_free_all_exit(shell, cmd, pipe),
				exit(err_num), FAILURE);
	}
	cmd->cmd = NULL;
	return (ft_free_all_exit(shell, cmd, pipe), exit(err_num), SUCCESS);
}

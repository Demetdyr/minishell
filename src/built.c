/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:30 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:31 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static int	ft_config_built_path_arg(t_token *token, t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	**arg;

	path = token->value;
	if (!path)
	{
		if (shell->err != HANDLED)
			return (ft_print_err_exec(token, shell, 127, ERR_NO_CMD), FAILURE);
		return (FAILURE);
	}
	cmd->cmd = path;
	arg = ft_token_to_arg(token, path);
	if (!arg)
		return (free(path), FAILURE);
	cmd->argv = arg;
	return (SUCCESS);
}

static void	ft_config_fd1_built(t_cmd *cmd, int i, int **pipe_fd)
{
	if (pipe_fd)
	{
		if (i != 0)
		{
			close(pipe_fd[i - 1][1]);
			if (cmd->in_fd != NO_FD)
			{
				cmd->bout = cmd->in_fd;
				close(pipe_fd[i - 1][0]);
			}
			else
				cmd->bin = pipe_fd[i - 1][0];
		}
		else
		{
			if (cmd->in_fd != NO_FD)
				cmd->bin = cmd->in_fd;
			else
				cmd->bin = STDIN_FILENO;
		}
	}
	else
		if (cmd->in_fd != NO_FD)
			cmd->bin = cmd->in_fd;
}

static void	ft_config_fd2_built(t_cmd *cmd, int i, int **pipe_fd, int count)
{
	if (pipe_fd)
	{
		if (i != count - 1)
		{
			close(pipe_fd[i][0]);
			if (cmd->out_fd != NO_FD)
			{
				cmd->bout = cmd->out_fd;
				close(pipe_fd[i][1]);
			}
			else
				cmd->bout = pipe_fd[i][1];
		}
		else
		{
			if (cmd->out_fd != NO_FD)
				cmd->bout = cmd->out_fd;
			else
				cmd->bout = STDOUT_FILENO;
		}
	}
	else
		if (cmd->out_fd != NO_FD)
			cmd->bout = cmd->out_fd;
}

void	ft_check_build_fd(t_cmd *cmd, int **pipe_fd)
{
	if (cmd->in_fd == NO_FD)
		if (cmd->heredoc_fd)
			cmd->in_fd = cmd->heredoc_fd[cmd->index];
	ft_config_fd1_built(cmd, cmd->index, pipe_fd);
	ft_config_fd2_built(cmd, cmd->index, pipe_fd, cmd->count);
	if (cmd->bout == NO_FD)
		cmd->bout = STDOUT_FILENO;
	if (cmd->bin == NO_FD)
		cmd->bin = STDIN_FILENO;
}

int	ft_exec_built(t_token *token, t_shell *shell, t_cmd *cmd, int **pipe_fd)
{
	ft_check_build_fd(cmd, pipe_fd);
	if (ft_config_built_path_arg(token, shell, cmd) != SUCCESS)
		return (FAILURE);
	if (ft_strncmp(token->value, "cd", 3) == 0)
		return (ft_exec_cd(token, shell));
	if (ft_strncmp(token->value, "export", 7) == 0)
		return (ft_exec_export(token, shell, cmd));
	if (ft_strncmp(token->value, "unset", 6) == 0)
		return (ft_exec_unset(token, shell));
	if (ft_strncmp(token->value, "env", 4) == 0)
		return (ft_exec_env(shell, cmd));
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		return (ft_exec_pwd(shell, cmd));
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		return (ft_exec_echo(token, shell, cmd));
	else if (ft_strncmp(token->value, "exit", 5) == 0)
		return (ft_exec_exit(token, shell, cmd));
	return (SUCCESS);
}

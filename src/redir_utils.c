/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:48 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/15 18:05:05 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

int	ft_check_redl(t_token *token, t_shell *shell, t_cmd *cmd, bool last_heredoc)
{
	t_token	*iter;

	if (!token)
		return (FAILURE);
	iter = token->next;
	if (!iter && !iter->next)
		return (FAILURE);
	if (access(iter->value, F_OK) == -1)
		return (ft_print_err_exec(token->next, shell, 1, ERR_NO_FILE));
	if (access(iter->value, R_OK) == -1)
		return (ft_print_err_exec(token->next, shell, 101, EACCES));
	if (last_heredoc)
		close(open(iter->value, O_RDONLY));
	else
	{
		if (cmd->in_fd != NO_FD)
			close(cmd->in_fd);
		cmd->in_fd = open(iter->value, O_RDONLY);
	}
	return (SUCCESS);
}

int	ft_check_redll(t_token *token, int index, t_cmd *cmd)
{
	char	*str;
	int		fd[2];
	t_token	*iter;
	pid_t	pid;
	int		status;

	str = NULL;
	if (!token || !token->next || pipe(fd) == -1)
		return (FAILURE);
	iter = token->next;
	g_sig = IN_HEREDOC;
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), FAILURE);
	else if (pid == 0)
		ft_check_redll_child(fd, str, iter);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		return (ft_check_redll_parent(fd, cmd, index, &status));
	}
	return (FAILURE);
}

int	ft_check_redr(t_token *token, t_shell *shell, t_cmd *cmd)
{
	t_token	*iter;

	if (!token)
		return (FAILURE);
	iter = token->next;
	if (!iter)
		return (FAILURE);
	if (access(iter->value, F_OK) == 0 && access(iter->value, W_OK) == -1)
	{
		if (ft_count_tokens(shell->token_lst) > 1)
			return (ft_print_err_exec(token, shell, 1, ERR_ACCESS_PIPE));
		return (ft_print_err_exec(token, shell, 1, ERR_ACCESS));
	}
	cmd->out_fd = open(iter->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out_fd == -1)
		return (ft_print_err_exec(token, shell, 103, ENOENT));
	if (ft_count_tokens(shell->token_lst) > 1)
		dup2(cmd->out_fd, STDOUT_FILENO);
	return (SUCCESS);
}

int	ft_check_redrr(t_token *token, t_shell *shell, t_cmd *cmd)
{
	t_token	*iter;

	if (!token)
		return (FAILURE);
	iter = token->next;
	if (access(iter->value, F_OK) == 0 && access(iter->value, W_OK) == -1)
		return (ft_print_err_exec(token, shell, 1, ERR_ACCESS));
	cmd->out_fd = open(iter->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out_fd == -1)
		return (ft_print_err_exec(token, shell, 105, ENOENT));
	if (ft_count_tokens(shell->token_lst) > 1)
		dup2(cmd->out_fd, STDOUT_FILENO);
	return (SUCCESS);
}

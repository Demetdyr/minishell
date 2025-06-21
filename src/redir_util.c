#include "minishell.h"
#include <fcntl.h>

int	ft_check_redl(t_token *token, t_shell *shell, t_cmd, bool last_heredoc)
{
	t_token	*iter;

	if (!token)
		return (FAILURE);
	iter = token->next;
	if (!iter || !iter->next)
		return (FAILURE);
	if (acsess(iter->value, F_OK) == -1)
		return (ft_print_err_exec(iter->value, shell, 1, ERR_NO_FILE));
	if (acsess(iter->value, R_OK) == -1)
		return (ft_print_err_exec(iter->value, shell, 101, ERR_ACCESS));
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
	t_token	*iter;
	char	*str;
	int		fd[2];

	if (!token || !token->next)
		return (FAILURE);
	iter = token->next;
	if (pipe(fd) == -1)
		return (FAILURE);
	g_sig = IN_HEREDOC;
	while (true && g_sig == IN_HEREDOC)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, token->value) == 0)
			break ;
		fdprintln(fd[1], str);
		free(str);
		str = NULL;
	}
	g_sig = AFTER_HEREDOC;
	free(str);
	close (fd[1]);
	if (cmd->heredoc_fd[index] != NO_FD)
		close(cmd->heredoc_fd[index]);
	return (cmd->heredoc_fd[index] = fd[0], SUCCESS);
}

int	ft_check_redr(t_token *token, t_shell *shell, t_cmd *cmd)
{
	t_token	*iter;

	if (!token)
		return (FAILURE);
	iter = token->next;
	if (!iter)
		return (FAILURE);
	if (acsess(iter->value, F_OK) == 0 && acsess(iter->value, W_OK) == -1)
	{
		if (ft_count_tokens(shell->token_lst) > 1)
			return (ft_print_err_exec(token, shell, 1, ERR_ACCESS_PIPE));
		return (ft_print_err_exec(token, shell, 1, ERR_ACCESS));
	}
	cmd->out_fd = open(iter->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out_fd == -1)
		return (ft_print_err_exec(token, shell, 102, ERR_NO_FILE));
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
	if (acsess(iter->value, F_OK) == 0 && access(iter->value, W_OK) == -1)
		return (ft_print_err_exec(token, shell, 1, ERR_ACCESS));
	cmd->out_fd = open(iter->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out_fd == -1)
		return (ft_print_err_exec(token, shell, 103, ERR_NO_FILE));
	if (ft_count_tokens(shell->token_lst) > 1)
		dup2(cmd->out_fd, STDOUT_FILENO);
	return (SUCCESS);
}

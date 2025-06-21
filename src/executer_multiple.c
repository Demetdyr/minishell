#include "minishell.h"
#include <unistd.h>


static void	ft_close_fds(int **pipe_fd, int i, int count)
{
	int	j;

	j = 0;
	while (j < count - 1)
	{
		if (j != i && j != i - 1)
		{
			close(pipe_fd[j][0]);
			close(pipe_fd[j][1]);
		}
		j++;
	}
}

static void	ft_config_fd1(t_cmd *cmd, int i, int **pipe_fd)
{
	if (cmd->in_fd == NO_FD)
	{
		if (cmd->in_fd == NO_FD)
			cmd->in_fd = cmd->heredoc_fd[i];
	}
	if (i != 0)
	{
		close (pipe_fd[i - 1][1]);
		if (cmd->in_fd != NO_FD)
		{
			dup2(cmd->in_fd, STDIN_FILENO);
			close(pipe_fd[i - 1][0]);
		}
		else
			dup2(pipe_fd[i - 1][0], STDIN_FILENO);
	}
	else
	{
		if (cmd->in_fd != NO_FD)
			dup2(cmd->in_fd, STDIN_FILENO);
	}
}

static void	ft_config_fd2(t_cmd *cmd, int i, int **pipe_fd, int count)
{
	if (i != count - 1)
	{
		close(pipe_fd[i][0]);
		if (cmd->out_fd != NO_FD)
		{
			dup2(cmd->out_fd, STDOUT_FILENO);
			close(pipe_fd[i][1]);
		}
		else
		{
			dup2(pipe_fd[i][1], STDOUT_FILENO);
			close(pipe_fd[i][1]);
		}
	}
	else
	{
		if (cmd->out_fd != NO_FD)
			dup2(cmd->out_fd, STDOUT_FILENO);
	}
}

void	ft_check_childs(t_shell *shell, t_cmd *cmd, int **pipe_fd, int i)
{
	int	count;

	count = ft_count_tokens(shell->token_lst);
	if (!shell->token_lst[i] || !shell || !cmd || count < 1)
		return (exit(shell->status));
	if (ft_config_redir_fd(shell->token_lst[i], shell, cmd) != SUCCESS)
		return (exit(shell->status));
	if (ft_has_cmd(shell->token_lst[i]) == false)
		return (exit(shell->status));
	cmd->index = i;
	cmd->count = count;
	ft_close_fds(pipe_fd, i, count);
	if (ft_config_cmd_arg_path(shell->token_lst[i], shell, cmd, pipe_fd)
		!= SUCCESS)
		return (exit(shell->status));
	ft_config_fd1(cmd, i, pipe_fd);
	ft_config_fd2(cmd, i, pipe_fd, count);
	if (execve(cmd->cmd, cmd->argv, shell->env) == -1)
		exit(shell->status);
	exit(0);
}

#include "../inc/minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	ft_exec_one_cmd_init(t_token *token, t_shell *shell, t_cmd *cmd)
{
	if (ft_config_heredoc_fd(token, 0, cmd) != SUCCESS)
		return (FAILURE);
	if (ft_config_redir_fd(token, shell, cmd) != SUCCESS)
		return (FAILURE);
	if (ft_has_cmd(token) == false)
		return (SUCCESS);
	if (ft_config_cmd_arg_path(token, shell, cmd, NULL) != SUCCESS)
		return (FAILURE);
	if (!cmd->cmd)
		return (FAILURE);
	if (cmd->in_fd == NO_FD)
		cmd->in_fd = cmd->heredoc_fd[0];
	return (SUCCESS);
}

static int	ft_exec_one_cmd_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	g_sig = IN_CMD;
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	else if (pid == 0)
	{
		if (cmd->in_fd != NO_FD)
			dup2(cmd->in_fd, STDIN_FILENO);
		if (cmd->out_fd != NO_FD)
			dup2(cmd->out_fd, STDOUT_FILENO);
		if (execve(cmd->cmd, cmd->argv, shell->env) == -1)
			exit(shell->status);
	}
	if (pid != 0)
	{
		waitpid(pid, &shell->status, 0);
		shell->status = ft_child_exit_status(shell->status);
	}
	g_sig = AFTER_CMD;
	return (SUCCESS);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
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

int	ft_exec_one_cmd(t_token *token, t_shell *shell, t_cmd *cmd)
{
	if (!token || !shell || !cmd)
		return (FAILURE);
	if (ft_exec_one_cmd_init(token, shell, cmd) != SUCCESS)
		return (ft_free_cmd(cmd), FAILURE);
	if (ft_exec_one_cmd_child(cmd, shell) != SUCCESS)
		return (ft_free_cmd(cmd), FAILURE);
	return (ft_free_cmd(cmd), SUCCESS);
}

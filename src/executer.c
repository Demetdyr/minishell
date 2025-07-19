/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:16 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/19 21:15:59 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	ft_close_childs(int **pipe_fd, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

static int	ft_pipline_init_childs(int **pipe_fd, t_shell *shell, t_cmd *cmd,
	pid_t *pid)
{
	int		i;
	int		count;
	pid_t	pid_temp;

	i = 0;
	count = ft_count_tokens(shell->token_lst);
	while (i < count)
	{
		if (ft_config_heredoc_fd(shell->token_lst[i], i, cmd, shell) != SUCCESS)
			return (FAILURE);
		g_sig = IN_CMD;
		pid_temp = fork();
		if (pid_temp == -1)
			return (free(pid), FAILURE);
		pid[i] = pid_temp;
		if (pid_temp == 0)
			ft_check_childs(cmd, pipe_fd, i, pid);
		i++;
	}
	ft_close_childs(pipe_fd, count);
	g_sig = AFTER_CMD;
	return (SUCCESS);
}

static int	ft_init_pipeline(int **pipe_fd, t_shell *shell, t_cmd *cmd,
	int count)
{
	pid_t	*pid;
	int		i;

	if (!pipe_fd || count < 0)
		return (FAILURE);
	pid = (pid_t *)malloc(sizeof(pid_t) * (count + 1));
	if (!pid)
		return (FAILURE);
	if (ft_pipline_init_childs(pipe_fd, shell, cmd, pid) != SUCCESS)
		return (free(pid), FAILURE);
	i = 0;
	while (i < count)
	{
		waitpid(pid[i], &shell->status, 0);
		shell->status = ft_child_exit_status(shell->status);
		i++;
	}
	return (free(pid), SUCCESS);
}

static int	ft_prompt_exec(t_shell *shell)
{
	int		token_count;
	t_cmd	cmd;
	int		**pipe_fd;

	pipe_fd = NULL;
	if (!shell || !shell->token_lst)
		return (FAILURE);
	token_count = ft_count_tokens(shell->token_lst);
	if (token_count < 1)
		return (FAILURE);
	if (ft_init_cmd(&cmd, shell, token_count) != SUCCESS)
		return (FAILURE);
	if (token_count == 1)
		return (ft_exec_one_cmd(shell->token_lst[0], shell, &cmd));
	pipe_fd = ft_init_pipe(token_count - 1);
	if (!pipe_fd)
		return (free(cmd.heredoc_fd), FAILURE);
	if (ft_init_pipeline(pipe_fd, shell, &cmd, token_count) != SUCCESS)
		return (ft_free_pipe(pipe_fd, token_count - 1), free(cmd.heredoc_fd),
			FAILURE);
	return (ft_free_pipe(pipe_fd, token_count - 1), free(cmd.heredoc_fd),
		SUCCESS);
}

void	ft_start_exec(t_shell *shell)
{
	if (!(shell->token_lst && ft_prompt_exec(shell) == SUCCESS))
		ft_print_err_unknown(shell);
	ft_free_prompt(shell);
	if (shell->token_lst)
	{
		ft_free_token_lst(&shell->token_lst);
		shell->token_lst = NULL;
	}
}

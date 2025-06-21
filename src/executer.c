#include "minishell.h"

void	ft_start_exec(t_shell *shell)
{
	if (!(shell->token_lst && ft_prompt_exec(shell) == SUCCESS))
		ft_print_err_unknown(shell);
	ft_free_prompt(shell);
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
	if (ft_init_cmd(&cmd, arr_len) != SUCCESS)
		return (FAILURE);
	if (token_count == 1)
		return (ft_exec_one_cmd(shell->token_lst[0], shell, &cmd));
	pipe_fd = ft_init_pipe(token_count - 1);
	if (!pipe_fd)
		return (free(cmd.heredoc), FAILURE);

}

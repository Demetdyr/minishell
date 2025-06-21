#include "minishell.h"

int	ft_count_tokens(t_token **token_lst)
{
	int	i;

	i = 0;
	if (!token_arr)
		return (0);
	while (token_arr[i])
		i++;
	return (i);
}

int	ft_config_cmd_arg_path(t_token *token, t_shell *shell, t_cmd *cmd,
	int **pipe_fd)
{
	char	*path;
	char	**argv;

	if (!token || !shell || !cmd)
		return (FAILURE);
	if (ft_is_built(token, shell, cmd, pipe_fd))
		return (ft_token_set_built(token, shell, cmd, pipe_fd));
	path = ft_get_cmd_path(token, shell);
	if (!path)
	{
		if (shell->err != HANDLED)
			return (ft_print_err_exec(token, shell, 104, ERR_NO_CMD), FAILURE);
		return (FAILURE);
	}
	cmd->cmd = path;
	argv = ft_token_to_argv(token, path);
	if (!argv)
		return (free(path), FAILURE);
	cmd->argv = argv;
	return (SUCCESS);
}

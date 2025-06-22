#include "../inc/minishell.h"

bool	ft_is_built(t_token *token)
{
	if (!token || token->type == CMD || !token->value)
		return (false);
	if ((ft_strncmp(token->value, "cd", 3) == 0)
		|| (ft_strncmp(token->value, "exit", 5) == 0)
		|| (ft_strncmp(token->value, "export", 7) == 0)
		|| (ft_strncmp(token->value, "unset", 6) == 0)
		|| (ft_strncmp(token->value, "env", 4) == 0)
		|| (ft_strncmp(token->value, "pwd", 4) == 0)
		|| (ft_strncmp(token->value, "echo", 5) == 0))
		return (true);
	return (false);
}

int	ft_exec_built(t_token *token, t_shell *shell, t_cmd *cmd, int **pipe_fd)
{
	ft_check_build_fd(cmd, pipe_fd);
	if (ft_config_built_path_arg(token, shell, cmd) != SUCCESS)
		return (FAILURE);
	if (ft_strncmp(token->value, "cd", 3) == 0)
		return (ft_exec_cd(cmd, shell));
	else if (ft_strncmp(token->value, "exit", 5) == 0)
		return (ft_exec_exit(cmd, shell));
	else if (ft_strncmp(token->value, "export", 7) == 0)
		return (ft_exec_export(cmd, shell));
	else if (ft_strncmp(token->value, "unset", 6) == 0)
		return (ft_exec_unset(cmd, shell));
	else if (ft_strncmp(token->value, "env", 4) == 0)
		return (ft_exec_env(cmd, shell));
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		return (ft_exec_pwd(cmd, shell));
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		return (ft_exec_echo(cmd, shell));
	return (SUCCESS);
}

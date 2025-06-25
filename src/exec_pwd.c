#include "../inc/minishell.h"
#include <unistd.h>

int	ft_exec_pwd(t_shell *shell, t_cmd *cmd)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == 0 || ft_strlen(buffer) == 0)
		return (FAILURE);
	fdprintln(cmd->bout, buffer);
	shell->status = 0;
	return (SUCCESS);
}

#include "../inc/minishell.h"

void	ft_print_err_unknown(t_shell *shell)
{
	if (shell->err == FAILURE)
	{
		shell->status = 1;
		errprintln(ERR_STR_UNKNOWN);
	}
}

int	ft_print_err_exec(const t_token *token, t_shell *shell,
	int err_code, int err_msg)
{
	shell->err = HANDLED;
	(void)err_code; // Suppress unused variable warning
	(void)token; // Suppress unused variable warning
	(void)err_msg; // Suppress unused variable warning
	return (FAILURE);
}

void	ft_print_err_general(const char *str, int err_no)
{
	errprintln(str);
	exit (err_no);
}

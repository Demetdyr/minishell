#include "../inc/minishell.h"
#include <errno.h>

void	ft_print_err_unknown(t_shell *shell)
{
	if (shell->err == FAILURE)
	{
		shell->status = 1;
		errprintln(ERR_STR_UNKNOWN);
	}
}

static int	ft_print_util(int err_msg)
{
	if (err_msg == ERR_ISDIR)
		return (errprintln(ERR_STR_ISDIR), FAILURE);
	else if (err_msg == ERR_PERMISSION)
		return (errprintln(ERR_STR_PERMISSION), FAILURE);
	else if (err_msg == ERR_NO_HOME)
		return (errprintln(ERR_STR_NO_HOME), FAILURE);
	else if (err_msg == ERR_CHANGE_DIR)
		return (errprintln(ERR_STR_CHANGE_DIR), FAILURE);
	else if (err_msg == ERR_MANY_ARGS)
		return (errprintln(ERR_STR_MANY_ARGS), FAILURE);
	else if (err_msg == ERR_NOT_NUMERIC)
		return (errprintln(ERR_STR_NOT_NUMERIC), FAILURE);
	else if (err_msg == ERR_INVALID_EXPORT)
		return (errprintln(ERR_STR_INVALID_EXPORT), FAILURE);
	return (SUCCESS);
}

int	ft_print_err_exec(const t_token *token, t_shell *shell,
	int err_code, int err_msg)
{
	shell->err = HANDLED;
	shell->status = err_code;
	if (err_msg != ERR_OTHER)
	{
		errprint(COLOR_RED PROMPT COLOR_RESET);
		errprint(token->value);
		errprint(": ");
	}
	if (err_msg == ERR_OTHER)
		return (FAILURE);
	else if (err_msg == ENOENT)
		return (errprint(strerror(err_msg)), FAILURE);
	else if (err_msg == ERR_NO_FILE)
		return (errprintln(ERR_STR_NO_FILE), FAILURE);
	else if (err_msg == ERR_ACCESS)
		return (errprintln(ERR_STR_ACCESS), FAILURE);
	else if (err_msg == ERR_ACCESS_PIPE)
		return (errprintln(ERR_STR_ACCESS_PIPE), FAILURE);
	else if (err_msg == ERR_NO_CMD)
		return (errprintln(ERR_STR_NO_CMD), FAILURE);
	else if (ft_print_util(err_msg) != SUCCESS)
		return (FAILURE);
	else
		return (errprintln(ERR_STR_UNEXPECT), FAILURE);
}

void	ft_print_err_general(const char *str, int err_no)
{
	errprintln(str);
	exit (err_no);
}

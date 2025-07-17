/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:48 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/17 19:19:06 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	ft_print_util(const t_token *token, int err_msg)
{
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
	else if (err_msg == ERR_NO_CMD)
		return (errprintln(ERR_STR_NO_CMD), FAILURE);
	else if (err_msg == ERRP_INVALID_ARG)
		return (errprintln(ERR_STR_INVALID_ARG), FAILURE);
	else if (err_msg == ERR_NO_FILE)
		return (errprintln(ERR_STR_NO_FILE), FAILURE);
	return (SUCCESS);
}

int	ft_print_err_exec(const t_token *token, t_shell *shell,
	int err_code, int err_msg)
{
	shell->err = HANDLED;
	shell->status = err_code;
	if (ft_print_util(token, err_msg) != SUCCESS)
		return (FAILURE);
	else if (err_msg == ERR_NOT_NUMERIC)
		errprintln(ERR_STR_NOT_NUMERIC);
	else if (err_msg == ERR_MANY_ARGS)
		errprintln(ERR_STR_MANY_ARGS);
	else if (err_msg == ERR_PERMISSION)
		errprintln(ERR_STR_PERMISSION);
	else if (err_msg == ERR_ACCESS_PIPE)
		errprintln(ERR_STR_ACCESS_PIPE);
	else if (err_msg == ERR_ISDIR)
		errprintln(ERR_STR_ISDIR);
	else if (err_msg == ERR_NO_OLDPWD)
		errprintln(ERR_STR_NO_OLDPWD);
	else
		errprintln(ERR_STR_UNEXPECT);
	return (FAILURE);
}

void	ft_print_err_general(const char *str, int err_no)
{
	errprintln(str);
	exit (err_no);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:50 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:51 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

int	ft_exec_cd(t_token *token, t_shell *shell)
{
	const char	*home;

	if (!token)
		return (FAILURE);
	if (!token->next)
	{
		home = ft_get_value_env("HOME", shell);
		if (!home)
			return (ft_print_err_exec(token, shell, 1, ERR_NO_HOME));
		if (chdir(home) == -1)
			return (ft_print_err_exec(token, shell, 114, ERR_CHANGE_DIR));
		if (ft_config_pwd_env(shell) != SUCCESS)
			return (FAILURE);
		shell->status = 0;
		return (SUCCESS);
	}
	if (token->next && token->next->next)
		return (ft_print_err_exec(token, shell, 1, ERR_MANY_ARGS));
	if (chdir(token->next->value) == -1)
		return (ft_print_err_exec(token, shell, 1, ERR_NO_FILE));
	if (ft_config_pwd_env(shell) != SUCCESS)
		return (FAILURE);
	shell->status = 0;
	return (SUCCESS);
}

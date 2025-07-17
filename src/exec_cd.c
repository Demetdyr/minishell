/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:50 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/17 19:17:07 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static int	ft_exec_cd_and_tilde(t_token *token, t_shell *shell, char *buffer)
{
	const char	*home;

	home = ft_get_value_env("HOME", shell);
	if (!home)
		return (ft_print_err_exec(token, shell, 1, ERR_NO_HOME));
	if (getcwd(buffer, PATH_MAX))
	{
		if (shell->oldpwd)
			free(shell->oldpwd);
		shell->oldpwd = ft_strdup(buffer);
	}
	if (chdir(home) == -1)
		return (ft_print_err_exec(token, shell, 114, ERR_CHANGE_DIR));
	if (ft_config_pwd_env(shell) != SUCCESS)
		return (FAILURE);
	shell->status = 0;
	return (SUCCESS);
}

static int	ft_exec_cd_hyphen(t_token *token, t_shell *shell, char *buffer)
{
	char	*prev_pwd;

	if (!shell->oldpwd)
		return (ft_print_err_exec(token, shell, 1, ERR_NO_OLDPWD));
	if (getcwd(buffer, PATH_MAX))
	{
		prev_pwd = ft_strdup(buffer);
		if (chdir(shell->oldpwd) == -1)
		{
			free(prev_pwd);
			return (ft_print_err_exec(token, shell, 1, ERR_NO_FILE));
		}
		fdprintln(1, shell->oldpwd);
		free(shell->oldpwd);
		shell->oldpwd = prev_pwd;
	}
	if (ft_config_pwd_env(shell) != SUCCESS)
		return (FAILURE);
	shell->status = 0;
	return (SUCCESS);
}

int	ft_exec_cd(t_token *token, t_shell *shell)
{
	char		buffer[PATH_MAX];

	if (!token)
		return (FAILURE);
	if (!token->next || (token->next && token->next->value
			&& ft_strcmp(token->next->value, "~") == 0))
		return (ft_exec_cd_and_tilde(token, shell, buffer));
	if (token->next && token->next->next)
		return (ft_print_err_exec(token, shell, 1, ERR_MANY_ARGS));
	if (token->next && token->next->value
		&& ft_strcmp(token->next->value, "-") == 0)
		return (ft_exec_cd_hyphen(token, shell, buffer));
	if (getcwd(buffer, PATH_MAX))
	{
		if (shell->oldpwd)
			free(shell->oldpwd);
		shell->oldpwd = ft_strdup(buffer);
	}
	if (chdir(token->next->value) == -1)
		return (ft_print_err_exec(token, shell, 1, ERR_NO_FILE));
	if (ft_config_pwd_env(shell) != SUCCESS)
		return (FAILURE);
	shell->status = 0;
	return (SUCCESS);
}

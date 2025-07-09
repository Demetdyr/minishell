/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:57 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:58 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

int	ft_exec_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!shell || !shell->env || !cmd)
		return (FAILURE);
	i = 0;
	while (shell->env[i])
		fdprintln(cmd->bout, shell->env[i++]);
	shell->status = 0;
	return (SUCCESS);
}

char	*ft_get_value_env(const char *str, t_shell *shell)
{
	int		i;
	size_t	len;

	if (!str || !shell || !shell->env)
		return (NULL);
	i = 0;
	while (shell->env[i])
	{
		len = ft_strlen(str);
		if (ft_strncmp(shell->env[i], str, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + 5);
		i++;
	}
	return (NULL);
}

int	ft_config_pwd_env(t_shell *shell)
{
	char	buffer[PATH_MAX];

	if (!shell)
		return (FAILURE);
	buffer[0] = 'P';
	buffer[1] = 'W';
	buffer[2] = 'D';
	buffer[3] = '=';
	getcwd(buffer + 4, PATH_MAX);
	if (!buffer[4])
		return (FAILURE);
	if (ft_config_value_env(shell, buffer) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_config_value_env_append(t_shell *shell, char *value)
{
	char	*temp;

	if (!shell || !value || !shell->env)
		return (FAILURE);
	temp = ft_strdup(value);
	if (!temp)
		return (FAILURE);
	shell->env = ft_str_lst_add(shell->env, temp);
	if (!shell->env)
		return (free(temp), FAILURE);
	return (SUCCESS);
}

int	ft_config_value_env(t_shell *shell, char *value)
{
	int		i;
	int		len;
	bool	found;

	if (!shell || !value || !shell->env)
		return (FAILURE);
	found = true;
	i = 0;
	while (shell->env[i])
	{
		len = ft_strlen(shell->env[i]) - ft_strlen(ft_strchr(value, '='));
		if (ft_strncmp(shell->env[i], value, len) == 0
			&& shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(value);
			found = false;
		}
		i++;
	}
	if (found)
		return (ft_config_value_env_append(shell, value));
	return (SUCCESS);
}

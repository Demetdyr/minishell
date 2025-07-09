/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:02 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:03 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_sort_env(t_shell *shell, int len)
{
	int		i;
	int		j;
	int		sorted;
	char	*temp;

	i = 0;
	sorted = 0;
	while (i < len - 1 && !sorted)
	{
		j = 0;
		sorted = 1;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(shell->env[j], shell->env[j + 1]) > 0)
			{
				temp = shell->env[j];
				shell->env[j] = shell->env[j + 1];
				shell->env[j + 1] = temp;
				sorted = 0;
			}
			j++;
		}
		i++;
	}
}

static int	ft_print_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!shell || !shell->env)
		return (FAILURE);
	i = 0;
	while (shell->env[i])
	{
		fdprint(cmd->bout, "declare -x ");
		fdprintln(cmd->bout, shell->env[i]);
		i++;
	}
	return (SUCCESS);
}

static bool	ft_confirm_export(t_token *token, t_shell *shell)
{
	int	i;

	if (!token || !shell)
		return (false);
	while (token)
	{
		if (token->type == ARG && !ft_is_al_underscore(token->value[0]))
			return (ft_print_err_exec(token, shell, 1, ERRP_INVALID_ARG),
				false);
		i = 0;
		while (token->value[i])
		{
			if (token->value[i] == '=')
				break ;
			if (!ft_is_alnum_underscore(token->value[i]) && token->type == ARG)
				return (ft_print_err_exec(token, shell, 1, ERRP_INVALID_ARG),
					false);
			i++;
		}
		token = token->next;
	}
	return (true);
}

static int	ft_config_export(t_token *token, t_shell *shell)
{
	if (!token || !shell)
		return (FAILURE);
	while (token)
	{
		if (!ft_strchr(token->value, '='))
		{
			token = token->next;
			continue ;
		}
		if (ft_config_value_env(shell, token->value) != SUCCESS)
			return (FAILURE);
		token = token->next;
	}
	return (SUCCESS);
}

int	ft_exec_export(t_token *token, t_shell *shell, t_cmd *cmd)
{
	if (!token || !shell || !cmd)
		return (FAILURE);
	if (ft_is_valid_arg(token->next))
	{
		ft_sort_env(shell, ft_env_size(shell));
		return (ft_print_export(shell, cmd));
	}
	if (ft_confirm_export(token->next, shell) == false)
		return (FAILURE);
	if (ft_config_export(token->next, shell) != SUCCESS)
		return (FAILURE);
	shell->status = 0;
	return (SUCCESS);
}

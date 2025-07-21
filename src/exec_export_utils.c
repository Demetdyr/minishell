/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:23:26 by mehcakir          #+#    #+#             */
/*   Updated: 2025/07/21 14:44:45 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_export_only(t_shell **shell)
{
	int	i;

	if ((*shell)->export_only)
	{
		i = 0;
		while ((*shell)->export_only[i])
			free((*shell)->export_only[i++]);
		free((*shell)->export_only);
		(*shell)->export_only = NULL;
	}
}

int	ft_add_export_only(t_shell *shell, char *key)
{
	int	i;

	if (!shell || !key)
		return (FAILURE);
	if (shell->export_only)
	{
		i = 0;
		while (shell->export_only[i])
		{
			if (ft_strcmp(shell->export_only[i], key) == 0)
				return (SUCCESS);
			i++;
		}
	}
	shell->export_only = ft_str_lst_add(shell->export_only, ft_strdup(key));
	return (SUCCESS);
}

void	ft_print_export_env(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*eq;
	int		key_len;

	i = 0;
	if (shell->env)
	{
		while (shell->env[i])
		{
			fdprint(cmd->bout, "declare -x ");
			eq = ft_strchr(shell->env[i], '=');
			if (eq)
			{
				key_len = eq - shell->env[i];
				fdprintn(cmd->bout, shell->env[i], key_len);
				fdprint(cmd->bout, "=\"");
				fdprint(cmd->bout, eq + 1);
				fdprintln(cmd->bout, "\"");
			}
			else
				fdprintln(cmd->bout, shell->env[i]);
			i++;
		}
	}
}

char	**ft_str_lst_add_export_only(char *value)
{
	char	**new_lst;

	new_lst = (char **)malloc(sizeof(char *) * 2);
	if (!new_lst)
		return (NULL);
	new_lst[0] = value;
	new_lst[1] = NULL;
	return (new_lst);
}

void	ft_set_shlvl(t_shell *shell)
{
	int		i;
	char	*new_shlvl;
	int		shlvl;
	char	*itoa_str;

	if (!shell || !shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(shell->env[i] + 6) + 1;
			if (shell->env[i])
				free(shell->env[i]);
			itoa_str = ft_itoa(shlvl);
			new_shlvl = ft_strjoin("SHLVL=", itoa_str, false);
			free (itoa_str);
			if (!new_shlvl)
				return ;
			shell->env[i] = new_shlvl;
			break ;
		}
		i++;
	}
}

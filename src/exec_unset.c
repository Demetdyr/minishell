/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:07 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:08 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**ft_allocate_str_lst(char **str_lst)
{
	int		i;
	char	**new_lst;

	i = 0;
	while (str_lst[i])
		i++;
	new_lst = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_lst)
		return (NULL);
	return (new_lst);
}

static char	**ft_lst_remove_env(char **str_lst, char *key)
{
	int		i;
	int		j;
	char	**new_lst;

	if (!str_lst || !key)
		return (NULL);
	new_lst = ft_allocate_str_lst(str_lst);
	i = 0;
	j = 0;
	while (str_lst[i])
	{
		if (str_lst[i] && key && ft_strncmp(str_lst[i],
				key, ft_strlen(key)) == 0 && str_lst[i][ft_strlen(key)] == '=')
		{
			free(str_lst[i]);
			str_lst[i] = NULL;
		}
		else
			new_lst[j++] = str_lst[i];
		i++;
	}
	new_lst[j] = NULL;
	return (free(str_lst), new_lst);
}

static bool	ft_confirm_unset(t_token *token, t_shell *shell)
{
	int	i;

	if (!token || !shell)
		return (false);
	while (token)
	{
		if (!ft_is_al_underscore(token->value[0]))
			return (ft_print_err_exec(token, shell, 1, ERRP_INVALID_ARG),
				false);
		i = 0;
		while (token->value[i])
		{
			if (!ft_is_alnum_underscore(token->value[i]))
				return (ft_print_err_exec(token, shell, 1, ERRP_INVALID_ARG),
					false);
			i++;
		}
		token = token->next;
	}
	return (true);
}

int	ft_exec_unset(t_token *token, t_shell *shell)
{
	if (!token || !shell)
		return (FAILURE);
	if (!token->next)
	{
		shell->status = 0;
		return (SUCCESS);
	}
	token = token->next;
	while (token)
	{
		if (ft_confirm_unset(token, shell) == false)
			return (FAILURE);
		shell->env = ft_lst_remove_env(shell->env, token->value);
		if (!shell->env)
			return (FAILURE);
		token = token->next;
	}
	shell->status = 0;
	return (SUCCESS);
}

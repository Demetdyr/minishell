/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:39 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:40 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_dollar_case(t_token **root, t_shell *shell)
{
	t_token		*temp;
	t_token		*iter;
	bool		has_dollar;

	if (!root || !*root || !shell)
		return ;
	iter = *root;
	while (iter)
	{
		has_dollar = false;
		temp = iter;
		iter = iter->next;
		ft_get_dollar_key_values(&temp->value, shell, &has_dollar);
		if (has_dollar)
		{
			if (!temp->prev)
				ft_insert_dollar_nodes(root);
			else
				ft_insert_dollar_nodes(&temp);
		}
	}
}

int	ft_special_dollar_case(char **data, int start, int i,
	t_shell *shell)
{
	char	*new_data;
	char	*value;
	char	*temp;

	i++;
	if ((*data)[i] == '?')
	{
		value = ft_itoa(shell->status);
		if (!value)
			return (i);
	}
	else
	{
		value = ft_strdup(shell->argv[0]);
		if (!value)
			return (i - 1);
	}
	i++;
	new_data = ft_create_data_from_dollar(*data, value, start, i);
	if (!new_data)
		return (free(value), i);
	temp = *data;
	*data = new_data;
	return (free(temp), free(value), i - 1);
}

void	ft_number_dollar_case(char **data, int start, int i)
{
	char	*new_data;
	char	*temp;
	char	*empty_value;

	empty_value = ft_strdup("");
	if (!empty_value)
		return ;
	i++;
	new_data = ft_create_data_from_dollar(*data, empty_value, start, i);
	if (!new_data)
		return ;
	temp = *data;
	*data = new_data;
	free(temp);
	free(empty_value);
}

static char	*ft_check_if_empty(char *value)
{
	if (!value)
		return (ft_strdup(""));
	return (value);
}

int	ft_normal_dollar_case(char **data, int start, int i, t_shell *shell)
{
	char	*value;
	char	*new_data;
	char	*temp;
	char	*key;
	int		len;

	while (ft_is_alnum_underscore((*data)[i]))
		i++;
	key = ft_substr(*data, start, i - start);
	if (!key)
		return (start - 1);
	value = ft_get_dollar_value(key, shell);
	value = ft_check_if_empty(value);
	if (!value)
		return (1);
	new_data = ft_create_data_from_dollar(*data, value, start, i);
	if (!new_data)
		return (start - 1);
	temp = *data;
	*data = new_data;
	len = ft_strlen(value);
	if (len == 0)
		return (free(key), free(temp), free(value), start - 1);
	return (free(key), free(temp), free(value), start + len - 1);
}

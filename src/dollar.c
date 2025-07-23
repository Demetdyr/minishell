/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:45 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/23 15:19:16 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

char	*ft_get_dollar_value(char *key, t_shell *shell)
{
	int			i;
	int			key_len;
	char		*value;

	i = 0;
	value = NULL;
	while (shell->env[i])
	{
		key_len = ft_strlen(key);
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			value = ft_strdup(&shell->env[i][key_len + 1]);
			if (!value)
				return (NULL);
		}
		i++;
	}
	return (value);
}

static void	ft_check_dollar_case(char **value, int i, t_shell *shell,
	int *start)
{
	*start = i + 1;
	if ((*value)[i + 1] == '0' || (*value)[i + 1] == '?')
		i = ft_special_dollar_case(value, *start, i, shell);
	else if ((*value)[i + 1] > '0' && (*value)[i + 1] <= '9')
		ft_number_dollar_case(value, *start, i + 1);
	else
		i = ft_normal_dollar_case(value, *start, i + 1, shell);
}

void	ft_get_dollar_key_values(char **value, t_shell *shell, bool *has_dollar)
{
	int	flag_single_quote;
	int	flag_double_quote;
	int	i;
	int	start;

	flag_single_quote = 0;
	flag_double_quote = 0;
	if (!value || !*value)
		return ;
	i = 0;
	while ((*value)[i])
	{
		if ((*value)[i] == '\'' && flag_double_quote == 0)
			flag_single_quote = !flag_single_quote;
		else if ((*value)[i] == '"' && flag_single_quote == 0)
			flag_double_quote = !flag_double_quote;
		if (flag_single_quote == 0 && ft_is_valid_dollar(*value, i))
		{
			*has_dollar = true;
			ft_check_dollar_case(value, i, shell, &start);
		}
		else
			i++;
	}
}

char	*ft_create_data_from_dollar(char *data, char *value, int start,
	int index)
{
	char	*new_data;
	int		i;
	int		j;
	int		value_len;

	if (!data)
		return (NULL);
	value_len = ft_strlen(value);
	new_data = (char *)malloc((start + value_len + ft_strlen(data + index - 1))
			* sizeof(char));
	if (!new_data)
		(void)index;
	i = 0;
	j = 0;
	while (i < start - 1)
		new_data[j++] = data[i++];
	i = 0;
	while (i < value_len)
		new_data[j++] = value[i++];
	while (data[index])
		new_data[j++] = data[index++];
	new_data[j] = '\0';
	return (new_data);
}

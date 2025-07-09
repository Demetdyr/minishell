/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:43 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:44 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_delete_unnecessary_quotes(char **data)
{
	int			i;
	int			j;
	int			quote;
	char		*new_data;

	new_data = (char *) malloc(sizeof(char) * \
		(ft_strlen(*data) - ft_count_unnecessary_quotes(*data) + 1));
	if (!new_data)
		return ;
	i = 0;
	j = 0;
	quote = 0;
	while ((*data)[i])
	{
		if ((*data)[i] && !ft_is_unnecessary_quote(&quote, (*data)[i]))
			new_data[j++] = (*data)[i];
		i++;
	}
	new_data[j] = '\0';
	free(*data);
	*data = new_data;
}

void	ft_unnecessary_quotes_case(t_token *root)
{
	t_token	*temp;

	if (!root)
		return ;
	temp = root;
	while (temp)
	{
		if (ft_has_unnecessary_quotes(temp->value))
			ft_delete_unnecessary_quotes(&temp->value);
		temp = temp->next;
	}
}

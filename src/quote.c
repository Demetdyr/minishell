/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:45 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:47 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pass_in_quote(char *prompt, int *i)
{
	int	index;

	index = *i;
	if (prompt[index] == '"')
	{
		index++;
		while (prompt[index] && prompt[index] != '"')
			index++;
		*i = index;
		if (!prompt[index])
			return (-1);
		(*i)++;
	}
	else if (prompt[index] == '\'')
	{
		index++;
		while (prompt[index] && prompt[index] != '\'')
			index++;
		*i = index;
		if (!prompt[index])
			return (-1);
		(*i)++;
	}
	return (0);
}

char	ft_get_in_quote(char old, char value)
{
	if (old == '"' && value == '"')
		old = 0;
	else if (old == '\'' && value == '\'')
		old = 0;
	else if (value == '\'' || value == '"')
		old = value;
	return (old);
}

bool	ft_is_unnecessary_quote(int *quote, char value)
{
	if (*quote)
	{
		if (value == *quote)
		{
			*quote = 0;
			return (true);
		}
	}
	else
	{
		if (value == '"')
		{
			*quote = '"';
			return (true);
		}
		else if (value == '\'')
		{
			*quote = '\'';
			return (true);
		}
	}
	return (false);
}

int	ft_count_unnecessary_quotes(char *data)
{
	int	quote;
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	quote = 0;
	while (data[i])
	{
		if (data[i] && ft_is_unnecessary_quote(&quote, data[i]))
			counter++;
		i++;
	}
	return (counter);
}

bool	ft_has_unnecessary_quotes(char *value)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (value[i])
	{
		ft_is_unnecessary_quote(&quote, value[i]);
		if (value[i] && ft_is_unnecessary_quote(&quote, value[i]))
			return (true);
		i++;
	}
	return (false);
}

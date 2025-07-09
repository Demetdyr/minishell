/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:53 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:54 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	ft_is_valid_arg(t_token *token)
{
	while (token)
	{
		if (token->type == ARG)
			return (false);
		token = token->next;
	}
	return (true);
}

bool	ft_is_newline_flag(const char *value)
{
	int	i;

	if (!(value[0] == '-' && value[1] == 'n'))
		return (false);
	i = 2;
	while (value[i])
	{
		if (value[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

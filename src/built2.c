/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:35 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:36 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	ft_is_built(t_token *token)
{
	if (!token || token->type != CMD || !token->value)
		return (false);
	if ((ft_strncmp(token->value, "cd", 3) == 0)
		|| (ft_strncmp(token->value, "exit", 5) == 0)
		|| (ft_strncmp(token->value, "export", 7) == 0)
		|| (ft_strncmp(token->value, "unset", 6) == 0)
		|| (ft_strncmp(token->value, "env", 4) == 0)
		|| (ft_strncmp(token->value, "pwd", 4) == 0)
		|| (ft_strncmp(token->value, "echo", 5) == 0))
		return (true);
	return (false);
}

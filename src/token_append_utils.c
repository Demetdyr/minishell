/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:10:02 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:10:03 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	ft_meta_append_pipe(t_token **token)
{
	t_token	*new;
	char	*value;

	if (!token || !*token)
		return (-1);
	value = ft_strdup("|");
	if (!value)
		return (-1);
	new = ft_new_token(value, PIPE);
	if (!new)
		return (free(value), -1);
	ft_token_to_prev(token, new);
	return (0);
}

int	ft_meta_append_redl(t_token **token)
{
	t_token	*new;
	char	*value;

	if (!token || !*token)
		return (-1);
	value = ft_strdup("<");
	if (!value)
		return (-1);
	new = ft_new_token(value, RED_L);
	if (!new)
		return (free(value), -1);
	ft_token_to_prev(token, new);
	return (0);
}

int	ft_meta_append_redll(t_token **token)
{
	t_token	*new;
	char	*value;

	if (!token || !*token)
		return (-1);
	value = ft_strdup("<<");
	if (!value)
		return (-1);
	new = ft_new_token(value, RED_LL);
	if (!new)
		return (free(value), -1);
	ft_token_to_prev(token, new);
	return (0);
}

int	ft_meta_append_redr(t_token **token)
{
	t_token	*new;
	char	*value;

	if (!token || !*token)
		return (-1);
	value = ft_strdup(">");
	if (!value)
		return (-1);
	new = ft_new_token(value, RED_R);
	if (!new)
		return (free(value), -1);
	ft_token_to_prev(token, new);
	return (0);
}

int	ft_meta_append_redrr(t_token **token)
{
	t_token	*new;
	char	*value;

	if (!token || !*token)
		return (-1);
	value = ft_strdup(">>");
	if (!value)
		return (-1);
	new = ft_new_token(value, RED_RR);
	if (!new)
		return (free(value), -1);
	ft_token_to_prev(token, new);
	return (0);
}

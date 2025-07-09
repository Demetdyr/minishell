/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:58 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:59 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_single_quote(t_syn *syn)
{
	if (syn->dual == 1)
	{
		syn->dual = 0;
		syn->pipe = 0;
		if (syn->single)
			syn->single = 0;
	}
	else if (syn->dual == 0)
		syn->dual = 1;
}

void	ft_double_quote(t_syn *syn)
{
	if (syn->dual == 2)
	{
		syn->dual = 0;
		syn->pipe = 0;
		if (syn->single)
			syn->single = 0;
	}
	else if (syn->dual == 0)
		syn->dual = 2;
}

int	ft_syntax_pipe(t_shell *shell, t_syn *syn, int *i)
{
	shell->cmd_count++;
	if (!syn->pipe)
		syn->pipe = 1;
	else
		return (2);
	if (!syn->single)
		syn->single = 3;
	else
		return (2);
	++(*i);
	return (0);
}

int	ft_single_arrow(t_syn *syn, int *i)
{
	if (!syn->single)
		syn->single = 1;
	else if (syn->single == 3)
		syn->single = 1;
	else
		return (2);
	++*i;
	return (0);
}

int	ft_double_arrow(t_syn *syn, int *i)
{
	if (!syn->single)
		syn->single = 2;
	else if (syn->single == 3)
	{
		syn->single = 2;
	}
	else
		return (2);
	*i += 2;
	return (0);
}

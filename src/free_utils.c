/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:18 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:19 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

void	ft_free_shell_single(t_shell **shell)
{
	int	i;

	if (!shell || !*shell)
		return ;
	i = 0;
	while ((*shell)->env && (*shell)->env[i])
		free((*shell)->env[i++]);
	free((*shell)->env);
	(*shell)->env = NULL;
	free((*shell)->prompt);
	(*shell)->prompt = NULL;
}

void	ft_free_path(char **path)
{
	int	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_free_env(char **copy_env, int i)
{
	if (!copy_env)
		return ;
	if (i > 0)
		while (i--)
			free(copy_env[i]);
	free(copy_env);
}

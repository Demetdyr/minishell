/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:55 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:56 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_buffer_init(int *size, int *new, t_token *token, int *j)
{
	*j = 0;
	*size = 0;
	if (token && token->value)
		*size += ft_strlen(token->value);
	*new = 1;
}

static int	ft_buffer_size(t_token *token, bool newline, int *j)
{
	int		size;
	int		new;
	int		spc;

	ft_buffer_init(&size, &new, token, j);
	if (newline)
		new = 0;
	spc = -1;
	if (!token)
		spc = 0;
	while (token)
	{
		if (token->type != ARG)
		{
			token = token->next;
			continue ;
		}
		size += ft_strlen(token->value);
		if (token->next)
			spc++;
		token = token->next;
	}
	return (size + spc + new + 2);
}

static char	*ft_join_args(t_token *token, bool newline)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = (char *) malloc(sizeof(char) * ft_buffer_size(token, newline, &j));
	if (!buffer)
		return (NULL);
	while (token)
	{
		if (token->type != ARG)
		{
			token = token->next;
			continue ;
		}
		i = 0;
		while (token->value[i])
			buffer[(j)++] = token->value[(i)++];
		if (token->next)
			buffer[(j)++] = ' ';
		token = token->next;
	}
	if (!newline)
		buffer[j++] = '\n';
	buffer[j] = '\0';
	return (buffer);
}

int	ft_exec_echo(t_token *token, t_shell *shell, t_cmd *cmd)
{
	char	*buffer;
	bool	newline;

	if (!token || !shell || !cmd)
		return (FAILURE);
	if (ft_is_valid_arg(token->next))
	{
		shell->status = 0;
		return (fdprint(cmd->out_fd, "\n"), SUCCESS);
	}
	token = token->next;
	newline = ft_is_newline_flag(token->value);
	if (newline)
		token = token->next;
	while (token && ft_is_newline_flag(token->value))
		token = token->next;
	buffer = ft_join_args(token, newline);
	if (!buffer)
		return (FAILURE);
	fdprint(cmd->bout, buffer);
	shell->status = 0;
	return (free(buffer), SUCCESS);
}

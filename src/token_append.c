/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:10:04 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:10:05 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "stdlib.h"
#include "unistd.h"

bool	ft_token_append_meta(t_token **token)
{
	t_token_append_meta	md;

	ft_token_append_meta_init(&md, token);
	while ((*token)->value[md.i])
	{
		md.in_quote = ft_get_in_quote(md.in_quote, (*token)->value[md.i]);
		md.type = ft_get_meta_type((*token)->value, md.i);
		if (ft_is_meta(md.type) && !md.in_quote)
		{
			md.has_meta = true;
			ft_token_append_all(token, md.start, md.i, md.type);
			if (md.type == RED_LL || md.type == RED_RR)
				md.i++;
			if ((*token)->value[md.i + 1]
				&& !ft_is_meta_char((*token)->value, md.i + 1))
				md.start = md.i + 1;
			else
				md.start = -1;
		}
		if (!(*token)->value[md.i + 1] && md.has_meta && md.start != -1)
			ft_token_append_str(token, md.start, md.i + 1);
		md.i++;
	}
	return (md.has_meta);
}

void	ft_token_append_all(t_token **token, int start, int i,
		t_token_type type)
{
	if (start != -1)
		ft_token_append_str(token, start, i);
	if (type == PIPE)
		ft_meta_append_pipe(token);
	if (type == RED_L)
		ft_meta_append_redl(token);
	if (type == RED_LL)
		ft_meta_append_redll(token);
	if (type == RED_R)
		ft_meta_append_redr(token);
	if (type == RED_RR)
		ft_meta_append_redrr(token);
}

void	ft_token_append_meta_init(t_token_append_meta *md,
		t_token **token)
{
	md->i = 0;
	if (!ft_is_meta_char((*token)->value, md->i))
		md->start = 0;
	else
		md->start = -1;
	md->has_meta = false;
	md->in_quote = 0;
}

int	ft_token_append_str(t_token **token, int start, int i)
{
	t_token	*new;
	char	*value;

	if (!token || !*token)
		return (-1);
	value = ft_substr((*token)->value, start, i - start);
	if (!value)
		return (-1);
	new = ft_new_token(value, NONE);
	if (!new)
		return (free(value), -1);
	ft_token_to_prev(token, new);
	return (0);
}

char	**ft_token_to_arg(t_token *token, char *path)
{
	char	**argv;
	int		i;
	bool	in_quote;

	if (!token || !path)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (ft_count_tokens_arg(token) + 3));
	if (!argv)
		return (NULL);
	argv[0] = path;
	i = 1;
	in_quote = false;
	while (token)
	{
		if (token->type == ARG)
		{
			argv[i++] = token->value;
			in_quote = true;
		}
		else if (in_quote)
			break ;
		token = token->next;
	}
	argv[i] = NULL;
	return (argv);
}

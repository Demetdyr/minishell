#include "../inc/minishell.h"
#include <stdlib.h>

t_token	*ft_token_get_root(t_token *node)
{
	if (!node)
		return (NULL);
	while (node && node->prev)
		node = node->prev;
	return (node);
}

t_token	*ft_token_get_last(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

int	ft_pipe_count(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

bool	ft_token_sep_md_init(t_token_sep_md *md, t_token *token)
{
	(*md).token_lst = (t_token **)malloc(sizeof(t_token *) * \
		(ft_pipe_count(token)+ 2));
	if (!(*md).token_lst)
		return (true);
	(*md).iter = token;
	(*md).temp_root = token;
	(*md).i = 0;
	return (false);
}

t_token	**ft_separate_by_pipe(t_token *token)
{
	t_token_sep_md	md;

	if (ft_token_sep_md_init(&md, token))
		return (NULL);
	while (md.iter)
	{
		if (md.iter->type == PIPE)
		{
			md.temp = md.iter;
			md.token_lst[md.i] = md.temp_root;
			md.temp_root = md.iter->next;
			md.iter->prev->next = NULL;
			md.iter = md.iter->next;
			if (md.temp)
				ft_free_token(&md.temp);
			if (md.temp_root && md.temp_root->type == PIPE)
				return (NULL);
			md.i++;
		}
		else
			md.iter = md.iter->next;
	}
	md.token_lst[md.i++] = md.temp_root;
	md.token_lst[md.i] = NULL;
	return (md.token_lst);
}

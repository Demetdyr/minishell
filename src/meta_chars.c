#include "../inc/minishell.h"
#include <stdlib.h>

t_token	*ft_label_meta_chars(t_token **root)
{
	t_token	*temp;
	t_token	*last;
	t_token	*temp_prev;

	temp = *root;
	last = temp;
	temp_prev = NULL;
	while (temp)
	{
		if (!temp->next)
			last = temp;
		if (ft_is_token_just_meta(&temp))
			temp = temp->next;
		else if (ft_token_append_meta(&temp))
		{
			if ((*temp).prev)
				temp_prev = (*temp).prev;
			ft_free_old_token(&temp, *root);
		}
		else
			temp = temp->next;
	}
	if (temp_prev)
		return (ft_token_get_root(temp_prev));
	return (ft_token_get_root(last));
}

bool	ft_is_meta(t_token_type type)
{
	return (type == PIPE || type == RED_L || type == RED_LL || type == RED_R
		|| type == RED_RR);
}

bool	ft_is_meta_char(char *data, int i)
{
	if (!data)
		return (false);
	if (data[i] == '>' && data[i + 1] == '>')
		return (true);
	if (data[i] == '<' && data[i + 1] == '<')
		return (true);
	return (data[i] == '|' || data[i] == '>' || data[i] == '<');
}

t_token_type	ft_get_meta_type(char *data, int i)
{
	if (data[i] == '|')
		return (PIPE);
	if (data[i] == '<' && data[i + 1] == '<')
		return (RED_LL);
	if (data[i] == '<')
		return (RED_L);
	if (data[i] == '>' && data[i + 1] == '>')
		return (RED_RR);
	if (data[i] == '>')
		return (RED_R);
	else
		return (NONE);
}

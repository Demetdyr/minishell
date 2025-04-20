#include "../inc/minishell.h"

void	ft_token_lst_types(t_token **token_lst)
{
	int	i;

	i = 0;
	if (!token_lst || !(*token_lst))
		return ;
	while (token_lst[i])
	{
		ft__token_types(token_lst[i]);
		i++;
	}
}

void	ft__token_types_file(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	while (temp)
	{
		if (temp->type == RED_L || temp->type == RED_R || temp->type == RED_RR)
		{
			temp = temp->next;
			if (temp)
				temp->type = RED_FILE;
			else
				break ;
		}
		else if (temp->type == RED_LL)
		{
			temp = temp->next;
			if (temp)
				temp->type = RED_HEREDOC;
			else
				break ;
		}
		temp = temp->next;
	}
}

void	ft__token_types(t_token *token)
{
	if (!token)
		return ;
	ft__token_types_file(token);
	while (token && token->type != NONE && token->type != ARG)
		token = token->next;
	if (token && token->type != RED_RR)
	{
		token->type = CMD;
		token = token->next;
	}
	while (token)
	{
		if (token->type == NONE)
			token->type = ARG;
		token = token->next;
	}
}

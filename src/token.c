#include "../inc/minishell.h"
#include <stdlib.h>

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->prev = NULL;
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*ft_token_to_last(t_token *token, t_token *new)
{
	t_token	*root;

	root = token;
	if (!root)
	{
		root = new;
		return (root);
	}
	while (token->next)
		token = token->next;
	token->next = new;
	if (token->next)
		token->next->prev = token;
	return (root);
}

void	ft_token_to_prev(t_token **token, t_token *new)
{
	t_token	*temp;

	if (!token || !*token || !new)
		return ;
	if (!(*token)->prev)
	{
		temp = *token;
		*token = new;
		new->next = temp;
		temp->prev = new;
		new->prev = NULL;
		*token = (*token)->next;
		return ;
	}
	temp = (*token)->prev;
	(*token)->prev = new;
	new->next = *token;
	temp->next = new;
	new->prev = temp;
}

bool	ft_is_token_just_meta(t_token **token)
{
	if (!token && !*token && !(*token)->value)
		return (false);
	if ((*token)->value[0] == '>' && (*token)->value[1] == '>'
		&& (*token)->value[2] == '\0')
		(*token)->type = RED_RR;
	else if ((*token)->value[0] == '<' && (*token)->value[1] == '<'
		&& (*token)->value[2] == '\0')
		(*token)->type = RED_LL;
	else if ((*token)->value[0] == '|' && (*token)->value[1] == '\0')
		(*token)->type = PIPE;
	else if ((*token)->value[0] == '<' && (*token)->value[1] == '\0')
		(*token)->type = RED_L;
	else if ((*token)->value[0] == '>' && (*token)->value[1] == '\0')
		(*token)->type = RED_R;
	else
		return (false);
	return (true);
}

void	ft_free_old_token(t_token **temp, t_token *root)
{
	t_token	*old_node;

	if (!temp || !*temp || !root)
		return ;
	old_node = *temp;
	if ((*temp)->prev)
		(*temp)->prev->next = (*temp)->next;
	if ((*temp)->next)
		(*temp)->next->prev = (*temp)->prev;
	*temp = (*temp)->next;
	ft_free_token(&old_node);
}

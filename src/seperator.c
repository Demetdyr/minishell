/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:53 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:54 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

t_token	*ft_prompt_seperator(char *prompt)
{
	t_token	*root;
	int		start;
	int		i;

	if (!prompt)
		return (NULL);
	i = 0;
	start = 0;
	root = NULL;
	while (prompt[i])
	{
		while (prompt[i] && (prompt[i] == ' ' || prompt[i] == '\t'))
			i++;
		start = i;
		while (prompt[i] && (prompt[i] != ' ' && prompt[i] != '\t'))
			if (ft_pass_words(prompt, &i) != 0)
				return (0);
		if (ft_create_nodes(&root, prompt, start, i) != 0)
			return (NULL);
		while (prompt[i] && prompt[i] == ' ')
			i++;
	}
	return (root);
}

int	ft_create_nodes(t_token **root, char *prompt, int start, int i)
{
	char	*content;
	t_token	*new;

	content = ft_substr(prompt, start, i - start);
	if (!content)
		return (ft_free_token(root), 1);
	new = ft_new_token(content, NONE);
	if (!new)
		return (free(content), ft_free_token(root), 1);
	*root = ft_token_to_last(*root, new);
	if (!*root)
		return (free(content), free(new), 1);
	return (0);
}

int	ft_pass_words(char *prompt, int *i)
{
	if (prompt[*i] && (prompt[*i] == '\'' || prompt[*i] == '"'))
		if (ft_pass_in_quote(prompt, i) == -1)
			return (1);
	while (prompt[*i] && prompt[*i] != ' ' && prompt[*i] != '\t'
		&& prompt[*i] != '\'' && prompt[*i] != '"')
		(*i)++;
	return (0);
}

void	ft_insert_dollar_nodes(t_token **token)
{
	t_token	*sub_nodes;
	t_token	*temp;

	if (!token || !*token)
		return ;
	temp = *token;
	sub_nodes = ft_prompt_seperator(temp->value);
	if (!sub_nodes)
	{
		if (temp->prev)
		{
			temp->prev->next = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
		}
		else
			*token = temp->next;
		ft_free_token(&temp);
		return ;
	}
	ft_insert_token(token, temp, sub_nodes);
}

void	ft_insert_token(t_token **token, t_token *temp, t_token *sub_nodes)
{
	t_token	*sub_last;

	if (temp->prev)
	{
		temp->prev->next = sub_nodes;
		sub_nodes->prev = temp->prev;
	}
	else
		*token = sub_nodes;
	sub_last = ft_token_get_last(sub_nodes);
	if (!sub_last)
		return ;
	if (temp->next)
		sub_last->next = temp->next;
	if (temp->next)
		temp->next->prev = sub_last;
	ft_free_token(&temp);
}

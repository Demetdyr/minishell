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

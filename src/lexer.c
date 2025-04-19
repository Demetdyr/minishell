#include "../inc/minishell.h"
#include <stdlib.h>

bool	ft_is_str_all_space(const char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_token_all_space(t_token *root)
{
	if (!root)
		return (true);
	while (root)
	{
		if (!ft_is_str_all_space(root->value))
			return (false);
		root = root->next;
	}
	return (true);
}

t_token	**ft_lexer(t_shell *shell)
{
	t_token	*root;
	t_token	**token_lst;

	if (!shell || !shell->prompt)
		return (NULL);
	root = ft_prompt_seperator(shell->prompt);
	if (!root)
		return (NULL);
	if (token_is_all_space(root))
		return (ft_free_all_tokens(&root), ft_free_shell_single(&shell), NULL);
	root = ft_label_meta_chars(&root);
	ft_dollar_case(&root, shell);
	ft_unnecessary_quotes_case(root);
	//continue	
	return (token_lst);
}

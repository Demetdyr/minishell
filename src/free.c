#include "../inc/minishell.h"
#include <stdlib.h>

void	ft_free_token(t_token **token)
{
	if (!token)
		return ;
	if (*token)
	{
		free((*token)->value);
		(*token)->value = NULL;
	}
	free(*token);
	*token = NULL;
}

void	ft_free_all_tokens(t_token **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->next)
		ft_free_all_tokens(&(*token)->next);
	ft_free_token(token);
}

void	ft_free_token_lst(t_token ***token_lst)
{
	int	i;

	if (!token_lst || !*token_lst || !**token_lst)
		return ;
	i = 0;
	while ((*token_lst)[i])
	{
		ft_free_all_tokens(&(*token_lst)[i]);
		i++;
	}
	free(*token_lst);
	*token_lst = NULL;
}

void	ft_free_shell(t_shell **shell)
{
	int	i;

	i = 0;
	if (!shell || !*shell)
		return ;
	if ((*shell)->env)
	{
		while ((*shell)->env[i])
			free((*shell)->env[i++]);
		free((*shell)->env);
		(*shell)->env = NULL;
	}
	free((*shell)->prompt);
	(*shell)->prompt = NULL;
	ft_free_token_lst(&(*shell)->token_lst);
	free(*shell);
	*shell = NULL;
}

void	ft_free_prompt(t_shell *shell)
{
	if (shell)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (shell->token_lst)
		ft_free_token_lst(&shell->token_lst);
}

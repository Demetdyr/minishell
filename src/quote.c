#include "../inc/minishell.h"

int	ft_pass_in_quote(char *prompt, int *i)
{
	int	index;

	index = *i;
	if (prompt[index] == '"')
	{
		index++;
		while (prompt[index] && prompt[index] != '"')
			index++;
		*i = index;
		if (!prompt[index])
			return (-1);
		(*i)++;
	}
	else if (prompt[index] == '\'')
	{
		index++;
		while (prompt[index] && prompt[index] != '\'')
			index++;
		*i = index;
		if (!prompt[index])
			return (-1);
		(*i)++;
	}
	return (0);
}
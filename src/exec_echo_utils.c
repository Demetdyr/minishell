#include "../inc/minishell.h"

bool	ft_is_valid_arg(t_token *token)
{
	while (token)
	{
		if (token->type == ARG)
			return (false);
		token = token->next;
	}
	return (true);
}

bool	ft_is_newline_flag(const char *value)
{
	int	i;

	if (!(value[0] == '-' && value[1] == 'n'))
		return (false);
	i = 2;
	while (value[i])
	{
		if (value[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

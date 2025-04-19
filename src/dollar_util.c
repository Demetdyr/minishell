#include "../inc/minishell.h"

bool	ft_is_valid_dollar(char *data, int i)
{
	return (data[i] == '$' && (is_alpha(data[i + 1]) || data[i + 1] == '_'
			|| is_digit(data[i + 1]) || data[i + 1] == '?'));
}

bool	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool	ft_is_alnum_underscore(char c)
{
	return (is_digit(c) || is_alpha(c) || c == '_');
}

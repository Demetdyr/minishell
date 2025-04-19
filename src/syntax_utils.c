#include "../inc/minishell.h"

bool	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

void	ft_skip_spaces(const char *s, int *i)
{
	while (s[*i] && is_space(s[*i]))
		(*i)++;
}

void	ft_toggle_quote(t_syn *st, char quote)
{
	if (st->in_quote && st->in_quote == quote)
		st->in_quote = 0;
	else if (!st->in_quote)
		st->in_quote = quote;
}

int	ft_handle_pipe(t_syn *st)
{
	if (st->in_quote || !st->pipe_expected)
		return (st->err_mask |= 0x00ff0000, 2);
	st->pipe_expected = false;
	st->redir_type = 0;
	return (0);
}

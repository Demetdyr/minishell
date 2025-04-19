#include "../inc/minishell.h"

static int	ft_handle_redir(t_syn *st, const char *s, int *i)
{
	int	dbl;

	dbl = (s[*i] == s[*i + 1]);
	if (st->in_quote)
		return (0);
	if (st->redir_type && st->redir_type != 3)
		return (st->err_mask |= 0x0000ff00, 2);
	if (dbl)
		st->redir_type = 2;
	else
		st->redir_type = 1;
	st->pipe_expected = true;
	if (dbl)
		(*i) += 2;
	else
		(*i) += 1;
	return (0);
}

static t_syn	ft_syntax_init(t_syn *st)
{
	st->pipe_expected = false;
	st->in_quote = 0;
	st->redir_type = 0;
	st->err_mask = 0;
	return (*st);
}

static int	ft_analyze_char(const char *p, int *i, t_syn *st)
{
	if (p[*i] == '\'' || p[*i] == '"')
	{
		ft_toggle_quote(st, p[*i]);
		(*i)++;
	}
	else if (!st->in_quote && (p[*i] == '>' || p[*i] == '<'))
		ft_handle_redir(st, p, i);
	else if (!st->in_quote && p[*i] == '|')
	{
		if (ft_handle_pipe(st))
			return (1);
		(*i)++;
	}
	else
	{
		st->pipe_expected = true;
		if (st->redir_type == 3)
			st->redir_type = 0;
		(*i)++;
	}
	return (0);
}

int	ft_syntax_check(t_shell *sh)
{
	const char	*p;
	int			i;
	t_syn		st;
	int			pipe_flag;

	p = sh->prompt;
	i = 0;
	st = ft_syntax_init(&st);
	ft_skip_spaces(p, &i);
	if (!p[i])
		return (0);
	while (p[i] && !st.err_mask)
	{
		if (ft_analyze_char(p, &i, &st))
			break ;
		ft_skip_spaces(p, &i);
	}
	if (st.in_quote)
		st.err_mask |= 0x000000ff;
	if (st.pipe_expected)
		pipe_flag = 1;
	else
		pipe_flag = 0;
	return (st.err_mask | ((st.redir_type & 0xff) << 8) | (pipe_flag << 16));
}

void	ft_print_syntax_err(int errs, t_shell *st)
{
	if (errs & 0xff000000)
	{
		errprintln(SYN_UNKNOWN_ERR_MSG);
		st->status = 1;
	}
	else if (errs & 0x00ff0000)
	{
		errprintln(SYN_ZERO_PIPE_MSG);
		st->status = 258;
	}
	else if (errs & 0x0000ff00)
	{
		errprintln(SYN_EMPTY_AFTER_MSG);
		st->status = 258;
	}
	else if (errs & 0x000000ff)
	{
		errprintln(SYN_MISS_QUOTE_MSG);
		st->status = 1;
	}
}

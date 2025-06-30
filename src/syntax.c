#include "../inc/minishell.h"

int	ft_is_space(char character)
{
	return (
		' ' == character || \
		'\t' == character || \
		'\v' == character || \
		'\f' == character || \
		'\r' == character
	);
}

void	ft_syntax_other(t_shell *shell, t_syn *syntax, int *i)
{
	if (ft_is_space(shell->prompt[*i]))
		++*i;
	else
		syntax->pipe = (syntax->single = (++*i, 0));
}

int	ft_process_char(t_shell *shell, t_syn *syn, int *i)
{
	(void)(((shell->prompt[*i] == '\'') && (ft_single_quote(syn), 1)) \
		|| ((shell->prompt[*i] == '"') && (ft_double_quote(syn), 1)));
	if (syn->dual)
		return ((*i)++, 1);
	if ((shell->prompt[*i] == '>' && shell->prompt[(*i) + 1] != '>') || \
			(shell->prompt[*i] == '<' && shell->prompt[(*i) + 1] != '<'))
	{
		if (ft_single_arrow(syn, i))
			return (2);
	}
	else if ((shell->prompt[*i] == '>' && shell->prompt[(*i) + 1] == '>') || \
			(shell->prompt[*i] == '<' && shell->prompt[(*i) + 1] == '<'))
	{
		if (ft_double_arrow(syn, i))
			return (2);
	}
	else if (shell->prompt[*i] == '|')
	{
		if (ft_syntax_pipe(shell, syn, i))
			return (2);
	}
	else
		ft_syntax_other(shell, syn, i);
	return (0);
}

int	ft_syntax_check(t_shell *shell)
{
	int i;
	t_syn syn;
	int result;

	syn.unknown = 0;
	syn.pipe = 1;
	syn.dual = 0;
	syn.single = 0;
	i = 0;
	while (ft_is_space(shell->prompt[i]))
		i++;
	if (shell->prompt[i] == '\0')
		return 0;
	while (shell->prompt[i])
	{
		result = ft_process_char(shell, &syn, &i);
		if (result == 2)
			break;
	}
	return ((syn.dual << 0) | (syn.single << 8) | \
			(syn.pipe << 16) | (syn.unknown << 24));
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

#include "../inc/minishell.h"

static void	ft_buffer_init(int *size, int *new, t_token *token)
{
	*size = 0;
	if (token && token->value)
		*size += ft_strlen(token->value);
	*new = 1;
}

static int	ft_buffer_size(t_token *token, bool newline)
{
	int		size;
	int		new;
	int		spc;

	ft_buffer_init(&size, &new, token);
	if (newline)
		new = 0;
	spc = -1;
	if (!token)
		spc = 0;
	while (token)
	{
		if (token->type != ARG)
		{
			token = token->next;
			continue ;
		}
		size += ft_strlen(token->value);
		if (token->next)
			spc++;
		token = token->next;
	}
	return (size + spc + new + 2);
}

static void	ft_join_args_init(t_token *token, char *buffer, int *j, int *i)
{
	*j = 0;
	while (token)
	{
		if (token->type != ARG)
		{
			token = token->next;
			continue ;
		}
		*i = 0;
		while (token->value[*i])
			buffer[(*j)++] = token->value[(*i)++];
		if (token->next)
			buffer[(*j)++] = ' ';
		token = token->next;
	}
}

static char	*ft_join_args(t_token *token, bool newline)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = (char *) malloc(sizeof(char) * ft_buffer_size(token, newline));
	if (!buffer)
		return (NULL);
	ft_join_args_init(token, buffer, &j, &i);
	buffer[j] = '\0';
	if (!newline)
		buffer[j++] = '\n';
	return (buffer);
}

int	ft_exec_echo(t_token *token, t_shell *shell, t_cmd *cmd)
{
	char	*buffer;
	bool	newline;

	if (!token || !shell || !cmd)
		return (FAILURE);
	if (ft_is_valid_arg(token->next))
	{
		shell->status = 0;
		return (fdprint(cmd->out_fd, "\n"), SUCCESS);
	}
	token = token->next;
	newline = ft_is_newline_flag(token->value);
	if (newline)
		token = token->next;
	while (token && ft_is_newline_flag(token->value))
		token = token->next;
	buffer = ft_join_args(token, newline);
	if (!buffer)
		return (FAILURE);
	fdprint(cmd->bout, buffer);
	shell->status = 0;
	return (free(buffer), SUCCESS);
}

#include "../inc/minishell.h"

static bool	ft_is_digit_exit(const char *c)
{
	int	i;

	i = 0;
	if (c[i] == '-' || c[i] == '+')
		i++;
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exec_exit(t_token *token, t_shell *shell)
{
	int	err_num;

	err_num = 0;
	if (!token)
		ft_print_err_general("Invalid arguments\n", 2);
	if (token && token->next && token->next->next)
		return (ft_print_err_exec(token, shell, 117, ERR_MANY_ARGS));
	if (token->next && !ft_is_digit_exit(token->next->value))
		return (ft_print_err_exec(token, shell, 118, ERR_NOT_NUMERIC),
			exit(255), FAILURE);
	if (token->next)
	{
		err_num = ft_atoi(token->next->value);
		if (err_num < 0)
			return (ft_print_err_exec(token, shell, \
				(int)(256 + (err_num % 256)), ERR_OTHER),
				exit(err_num), FAILURE);
		return (ft_print_err_exec(token, shell, \
			(int)(err_num % 256), ERR_OTHER),
			exit(err_num), FAILURE);
	}
	return (exit(err_num), SUCCESS);
}

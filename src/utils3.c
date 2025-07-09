#include "../inc/minishell.h"

static int	ft_is_line_incomplete(char *line)
{
	int		i;

	if (!line)
		return (0);
	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_is_space(line[i]))
		i--;
	return (i >= 0 && line[i] == '|');
}

static void	ft_append_prompt_line(char **original, char *new_line)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(*original, " ", 0);
	joined = ft_strjoin(tmp, new_line, 0);
	free(tmp);
	free(*original);
	*original = joined;
}

void	ft_pipe_ended_prompt(t_shell *shell)
{
	char	*line;

	while (ft_is_line_incomplete(shell->prompt))
	{
		g_sig = 2;
		line = readline("> ");
		if (!line || g_sig == 1)
		{
			if (g_sig == 1)
			{
				free(shell->prompt);
				shell->prompt = NULL;
				g_sig = 0;
				return ;
			}
			break ;
		}
		g_sig = 0;
		ft_append_prompt_line(&shell->prompt, line);
		free(line);
	}
	if (shell->prompt)
		add_history(shell->prompt);
}

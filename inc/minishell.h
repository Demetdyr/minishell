#ifndef MINISHELL
# define MINISHELL

typedef enum e_token_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	RED_L,
	RED_LL,
	RED_R,
	RED_HEREDOC,
	RED_FILE,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	int				status;
	char			**argv;
	char			**env;
	t_token			**token_lst;
	char			*prompt;
}	t_shell;

//minishell.c
char	**env_copy(char **env);

//utils.c
char	*ft_strdup(const char *src);
int		ft_strlen(const char *s);

//free.c
void	ft_free_token(t_token **token);
void	ft_free_all_tokens(t_token **token);
void	ft_free_token_lst(t_token ***token_lst);
void	ft_free_shell(t_shell **shell);


#endif
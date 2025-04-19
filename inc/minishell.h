#ifndef MINISHELL
# define MINISHELL

#include <stdbool.h>

#define SYN_UNKNOWN_ERR_MSG "unknown syntax error"
#define SYN_ZERO_PIPE_MSG "syntax error near unexpected token `newline'"
#define SYN_EMPTY_AFTER_MSG "syntax error near unexpected token `newline'"
#define SYN_MISS_QUOTE_MSG "unexpected quote `'', `\"'"

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
	int				err;
}	t_shell;

typedef struct s_syn
{
	bool  pipe_expected;   /* Öncü komut bittiyse pipe gelebilir   */
	bool  in_quote;        /* 1 = tek tırnak, 2 = çift tırnak      */
	int   redir_type;      /* 0 = yok, 1 = > veya <, 2 = >> veya <<*/
	int   err_mask;        /* Sonuç bitleri                        */
}	t_syn;

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
void	ft_free_prompt(t_shell *shell);

//print.c
void	fdprint(int fd, const char *s);
void	fdprintln(int fd, const char *s);
void	errprint(const char *str);
void	errprintln(const char *str);

//syntax.c
int		ft_syntax_check(t_shell *sh);
void	ft_print_syntax_err(int errs, t_shell *st);
t_syn	ft_syntax_init(t_syn *st);

//syntax_utils.c
bool	ft_is_space(char c);
void	ft_skip_spaces(const char *s, int *i);
void	ft_toggle_quote(t_syn *st, char quote);
int		ft_handle_pipe(t_syn *st);
int		ft_handle_redir(t_syn *st, const char *p, int *i);

//token.c


#endif
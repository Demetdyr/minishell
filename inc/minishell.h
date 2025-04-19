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
	RED_RR,
	RED_FILE,
	RED_HEREDOC,
}	t_token_type;

typedef struct s_token_append_meta
{
	t_token_type	type;
	int				in_quote;
	bool			has_meta;
	int				i;
	int				start;
}					t_token_append_meta;

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
char			**env_copy(char **env);

//free_utils.c
void			ft_free_shell_single(t_shell **shell);

//free.c
void			ft_free_token(t_token **token);
void			ft_free_all_tokens(t_token **token);
void			ft_free_token_lst(t_token ***token_lst);
void			ft_free_shell(t_shell **shell);
void			ft_free_prompt(t_shell *shell);

//lexer.c
bool			ft_is_str_all_space(const char *str);
bool			ft_is_token_all_space(t_token *root);
t_token			**ft_lexer(t_shell *shell);

//meta_chars.c
t_token			*ft_label_meta_chars(t_token **root);
bool			ft_is_meta(t_token_type type);
bool			ft_is_meta_char(char *data, int i);
t_token_type	ft_get_meta_type(char *data, int i);

//print.c
void			fdprint(int fd, const char *s);
void			fdprintln(int fd, const char *s);
void			errprint(const char *str);
void			errprintln(const char *str);

//quote.c
int				ft_pass_in_quote(char *prompt, int *i);
char			ft_get_in_quote(char old, char value);

//seperator.c
int				ft_create_nodes(t_token **root, char *prompt, int start, int i);
int				ft_pass_words(char *prompt, int *i);
t_token			*ft_prompt_seperator(char *prompt);

//syntax_utils.c
bool			ft_is_space(char c);
void			ft_skip_spaces(const char *s, int *i);
void			ft_toggle_quote(t_syn *st, char quote);
int				ft_handle_pipe(t_syn *st);

//syntax.c
int				ft_handle_redir(t_syn *st, const char *p, int *i);
int				ft_syntax_check(t_shell *sh);
void			ft_print_syntax_err(int errs, t_shell *st);
t_syn			ft_syntax_init(t_syn *st);

//token_append_utils.c
int				ft_meta_append_pipe(t_token **token);
int				ft_meta_append_redl(t_token **token);
int				ft_meta_append_redll(t_token **token);
int				ft_meta_append_redr(t_token **token);
int				ft_meta_append_redrr(t_token **token);

//token_append.c
bool			ft_token_append_meta(t_token **token);
void			ft_token_append_all(t_token **token, int start, int i,
					t_token_type type);
void			ft_token_append_meta_init(t_token_append_meta *md,
					t_token **token);
int				ft_token_append_str(t_token **token, int start, int i);

//token_utils.c
t_token			*ft_token_get_root(t_token *node);;

//token.c
t_token			*ft_new_token(char *value, t_token_type type);
t_token			*ft_token_to_last(t_token *token, t_token *new);
void			ft_token_to_prev(t_token **token, t_token *new);
bool			ft_is_token_just_meta(t_token **token);
void			ft_free_old_token(t_token **temp, t_token *root);

//utils.c
char			*ft_strdup(const char *src);
int				ft_strlen(const char *s);
char			*ft_substr(char const *s, int start, int len);

# endif
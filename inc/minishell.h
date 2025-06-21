#ifndef MINISHELL
# define MINISHELL

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# define IN_HEREDOC 2
# define AFTER_HEREDOC 3
# define IN_CMD 4
# define AFTER_CMD 5

# define SUCCESS 0
# define FAILURE -1
# define HANDLED -2

# define NO_FD -2

# define R_OK	4
# define W_OK	2
# define X_OK	1
# define F_OK	0

# define SYN_UNKNOWN_ERR_MSG "unknown syntax error"
# define SYN_ZERO_PIPE_MSG "syntax error near unexpected token `newline'"
# define SYN_EMPTY_AFTER_MSG "syntax error near unexpected token `newline'"
# define SYN_MISS_QUOTE_MSG "unexpected quote `'', `\"'"

# define ERR_NO_FILE 4001
# define ERR_ACCESS 4002
# define ERR_ACCESS_PIPE 4003

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

typedef struct s_token_sep_md
{
	t_token			**token_lst;
	t_token			*iter;
	t_token			*temp;
	t_token			*temp_root;
	int				i;
}					t_token_sep_md;

typedef struct s_shell
{
	int				status;
	char			**argv;
	char			**env;
	t_token			**token_lst;
	char			*prompt;
	int				err;
	int				cmd_count;
}	t_shell;

typedef struct s_syn
{
	bool	pipe_expected;   /* Öncü komut bittiyse pipe gelebilir   */
	bool	in_quote;        /* 1 = tek tırnak, 2 = çift tırnak      */
	int		redir_type;      /* 0 = yok, 1 = > veya <, 2 = >> veya <<*/
	int		err_mask;        /* Sonuç bitleri                        */
}	t_syn;

typedef struct s_cmd
{
	char			**argv;
	char			*cmd;
	int				in_fd;
	int				out_fd;
	int				heredoc_fd;
	int				index;
	int				count;
	int				bin;
	int				bout;
}	t_cmd;

//minishell.c
char			**env_copy(char **env);

//dollar_case.c
void			ft_dollar_case(t_token **root, t_shell *shell);
int				ft_special_dollar_case(char **data, int start, int i,
					t_shell *shell);
void			ft_number_dollar_case(char **data, int start, int i);
int				ft_normal_dollar_case(char **data, int start, int i,
					t_shell *shell);

//dollar_util.c
bool			ft_is_valid_dollar(char *data, int i);
bool			ft_is_digit(char c);
bool			ft_is_alpha(char c);
bool			ft_is_alnum_underscore(char c);

//dollar.c
char			*ft_get_dollar_value(char *key, t_shell *shell);
void			ft_get_dollar_key_values(char **value, t_shell *shell,
					bool *has_dollar);
char			*ft_create_data_from_dollar(char *data, char *value,
					int start, int index);

//free_utils.c
void			ft_free_shell_single(t_shell **shell);

//free.c
void			ft_free_token(t_token **token);
void			ft_free_all_tokens(t_token **token);
void			ft_free_token_lst(t_token ***token_lst);
void			ft_free_shell(t_shell **shell);
void			ft_free_prompt(t_shell *shell);

//ft_itoa.c
char			*ft_itoa(int n);

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

//quote_utils.c
void			ft_unnecessary_quotes_case(t_token *root);

//quote.c
int				ft_pass_in_quote(char *prompt, int *i);
char			ft_get_in_quote(char old, char value);
bool			ft_is_unnecessary_quote(int *quote, char value);
int				ft_count_unnecessary_quotes(char *data);
bool			ft_has_unnecessary_quotes(char *value);


//seperator.c
int				ft_create_nodes(t_token **root, char *prompt, int start, int i);
int				ft_pass_words(char *prompt, int *i);
t_token			*ft_prompt_seperator(char *prompt);
void			ft_insert_dollar_nodes(t_token **token);
void			ft_insert_token(t_token **token, t_token *temp,
					t_token *sub_nodes);

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

//token_types.c
void			ft_token_lst_types(t_token **token_lst);
void			ft__token_types(t_token *token);
void			ft__token_types_file(t_token *token);

//token_utils.c
t_token			*ft_token_get_root(t_token *node);
t_token			*ft_token_get_last(t_token *node);
int				ft_pipe_count(t_token *token);
bool			ft_token_sep_md_init(t_token_sep_md *md, t_token *token);
t_token			**ft_separate_by_pipe(t_token *token);

//token_utils2.c
int				ft_count_tokens(t_token **token_lst);
int				ft_config_cmd_arg_path(t_token *token, t_shell *shell,
					t_cmd *cmd, int **pipe_fd);

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
int				ft_strncmp(const char *s1, const char *s2, int n);

// signal.c
void			ft_check_signal(void);

// executer.c
void			ft_start_exec(t_shell *shell);

// executer_one.c
int				ft_exec_one_cmd(t_token *token, t_shell *shell, t_cmd *cmd);

// executer_utils.c
int				ft_init_cmd(t_cmd *cmd, int token_count);
bool			ft_has_cmd(t_token *token);
int				ft_child_exit_status(int status);

// redir.c
int				ft_config_heredoc_fd(t_token *token, int index, t_cmd *cmd);
int				ft_config_redir_fd(t_token *token, t_shell *shell, t_cmd *cmd);

// redir_util.c
int				ft_check_redl(t_token *token, t_shell *shell, t_cmd *cmd,
					bool last_heredoc);
int				ft_check_redll(t_token *token, int index, t_cmd *cmd);
int				ft_check_redr(t_token *token, t_shell *shell, t_cmd *cmd);
int				ft_check_redrr(t_token *token, t_shell *shell, t_cmd *cmd);

#endif
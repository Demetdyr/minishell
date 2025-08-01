/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:18 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/23 15:22:00 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>

# define CONTINUE 2
# define SUCCESS 0
# define FAILURE -1
# define HANDLED -2

# define NO_FD -2

# define R_OK	4
# define W_OK	2
# define X_OK	1
# define F_OK	0

# define IN_HEREDOC 2
# define AFTER_HEREDOC 3
# define IN_CMD 4
# define AFTER_CMD 5

# define PATH_MAX 4096
# define MAX_FD 256

# define STDIN_FILENO 0

# ifndef _POSIX_VDISABLE
#  define _POSIX_VDISABLE 0
# endif

extern int	g_sig;

# define SYN_UNKNOWN_ERR_MSG "unknown syntax error"
# define SYN_ZERO_PIPE_MSG "syntax error near unexpected token `newline'"
# define SYN_EMPTY_AFTER_MSG "syntax error near unexpected token `newline'"
# define SYN_MISS_QUOTE_MSG "unexpected quote `'', `\"'"

# define COLOR_RED "\033[0;31m"
# define COLOR_RESET "\033[0m"

# define PROMPT "minishell: "

# define ERR_NO_FILE 30002
# define ERR_ACCESS 30006
# define ERR_ACCESS_PIPE 30007
# define ERR_NO_CMD 10002
# define ERR_ISDIR 30008
# define ERR_PERMISSION 30006
# define ERR_NO_HOME 10001
# define ERR_CHANGE_DIR 10003
# define ERR_MANY_ARGS 30004
# define ERR_NOT_NUMERIC 30003
# define ERR_OTHER 40000
# define ERRP_INVALID_ARG 10004

# define ERR_STR_UNKNOWN "unknown error"
# define ERR_STR_NO_FILE "No such file or directory"
# define ERR_STR_ACCESS "Permission denied"
# define ERR_STR_ACCESS_PIPE "Permission denied"
# define ERR_STR_NO_CMD "command not found"
# define ERR_STR_ISDIR "Is a directory"
# define ERR_STR_PERMISSION "Permission denied"
# define ERR_STR_NO_HOME "HOME not set"
# define ERR_STR_CHANGE_DIR "cd: cannot change directory"
# define ERR_STR_MANY_ARGS "cd: too many arguments"
# define ERR_STR_NOT_NUMERIC "exit: numeric argument required"
# define ERR_STR_OTHER "An error occurred"
# define ERR_STR_INVALID_EXPORT "export: not a valid identifier"
# define ERR_STR_INVALID_ARG "unset: not a valid identifier"
# define ERR_STR_UNEXPECT "unexpected error"
# define ERR_STR_CTRL_D_EOF "minishell: warning: here-document delimited by eof"

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

typedef struct s_pipe
{
	int				**pipe_fd;
	pid_t			*pid;
}					t_pipe;

typedef struct s_shell
{
	int				status;
	char			**argv;
	char			**env;
	char			**export_only;
	t_token			**token_lst;
	char			*prompt;
	int				err;
	int				cmd_count;
	char			*oldpwd;
	int				fd_list[MAX_FD];
	int				fd_count;
}					t_shell;

typedef struct s_syn
{
	unsigned char	dual;
	unsigned char	single;
	unsigned char	pipe;
	unsigned char	unknown;
}					t_syn;

typedef struct s_cmd
{
	char			**argv;
	char			*cmd;
	int				in_fd;
	int				out_fd;
	int				*heredoc_fd;
	int				index;
	int				count;
	int				bin;
	int				bout;
	t_shell			*shell;
}					t_cmd;

//minishell.c
char			**ft_env_copy(char **env);

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
bool			ft_is_al_underscore(char c);

//dollar.c
char			*ft_get_dollar_value(char *key, t_shell *shell);
void			ft_get_dollar_key_values(char **value, t_shell *shell,
					bool *has_dollar);
char			*ft_create_data_from_dollar(char *data, char *value,
					int start, int index);

//free_utils.c
void			ft_free_shell_single(t_shell **shell);
void			ft_free_path(char **path);
void			ft_free_env(char **copy_env, int i);
void			ft_free_shell_cmd_exit(t_shell *shell, t_cmd *cmd, int status);
void			ft_free_shell_cmd_exit_status(t_shell *shell, t_cmd *cmd,
					t_pipe pipe);

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
void			fdprintn(int fd, const char *str, size_t n);

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
void			ft_single_quote(t_syn *syntax);
void			ft_double_quote(t_syn *syntax);
int				ft_syntax_pipe(t_shell *shell, t_syn *syntax, int *i);
int				ft_single_arrow(t_syn *syntax, int *i);
int				ft_double_arrow(t_syn *syntax, int *i);

//syntax.c
int				ft_process_char(t_shell *shell, t_syn *syn, int *i);
int				ft_is_space(char character);
void			ft_syntax_other(t_shell *shell, t_syn *syntax, int *i);
int				ft_syntax_check(t_shell *shell);
void			ft_print_syntax_err(int errs, t_shell *st);

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
char			**ft_token_to_arg(t_token *token, char *path);

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
					t_cmd *cmd, t_pipe pipe);
int				ft_count_tokens_arg(t_token *token);

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
char			*ft_strchr(const char *s, int c);

//signal.c
void			ft_check_signal(void);
void			ft_sigint_heredoc_handler(int sig);

//executer.c
void			ft_start_exec(t_shell *shell);

//executer_one.c
int				ft_exec_one_cmd(t_token *token, t_shell *shell, t_cmd *cmd);
void			ft_free_cmd(t_cmd *cmd);

//executer_utils.c
int				ft_init_cmd(t_cmd *cmd, t_shell *shell, int token_count);
bool			ft_has_cmd(t_token *token);
int				ft_child_exit_status(int status);
int				ft_get_len_env(const char *value, int *len);

//redir.c
int				ft_config_heredoc_fd(t_token *token, int index, t_cmd *cmd,
					t_shell *shell);
int				ft_config_redir_fd(t_token *token, t_shell *shell, t_cmd *cmd);
void			ft_check_redll_child(int fd[2], char *str, t_token *iter,
					t_shell *shell);
int				ft_check_redll_parent(int fd[2], t_cmd *cmd,
					int index, int *status);

//redir_utils.c
int				ft_check_redl(t_token *token, t_shell *shell, t_cmd *cmd,
					bool last_heredoc);
int				ft_check_redll(t_token *token, int index, t_cmd *cmd,
					t_shell *shell);
int				ft_check_redr(t_token *token, t_shell *shell, t_cmd *cmd);
int				ft_check_redrr(t_token *token, t_shell *shell, t_cmd *cmd);
void			ft_heredoc_child_handler(char *str, int empty_input,
					char *delimiter, int fd[2]);

//pipe.c
int				**ft_init_pipe(int pipe_count, t_shell *shell);
int				**ft_free_pipe(int **pipe_fd, int pipe_count);

//executer_multiple.c
void			ft_check_childs(t_cmd *cmd, t_pipe pipe, int i);

//path.c
char			*ft_get_path(t_token *token, t_shell *shell);
char			*ft_get_path_str(char **env);
char			*ft_get_exact_path(t_token *token, t_shell *shell);

//built.c
int				ft_exec_built(t_token *token, t_shell *shell,
					t_cmd *cmd, t_pipe pipe);

void			ft_check_build_fd(t_cmd *cmd, int **pipe_fd);

//err_print.c
int				ft_print_err_exec(const t_token *token, t_shell *shell,
					int err_code, int err_msg);
void			ft_print_err_unknown(t_shell *shell);
void			ft_print_err_general(const char *str, int err_no);

//utils2.c
char			*ft_strjoin(char const *s1, char const *s2, bool flag_free);
int				ft_strcmp(char *s1, char *s2);
char			**ft_str_lst_add(char **lst, char *value);
int				ft_atoi(const char *str);
int				ft_env_size(t_shell *shell);

//ft_split.c
char			**ft_split(char const *s, char c);

//built2.c
bool			ft_is_built(t_token *token);

//exec_echo.c
int				ft_exec_echo(t_token *token, t_shell *shell, t_cmd *cmd);

//exec_cd.c
int				ft_exec_cd(t_token *token, t_shell *shell);

//exec_export.c
int				ft_exec_export(t_token *token, t_shell *shell, t_cmd *cmd);

//exec_export_utils.c
void			ft_free_export_only(t_shell **shell);
int				ft_add_export_only(t_shell *shell, char *key);
void			ft_print_export_env(t_shell *shell, t_cmd *cmd);
char			**ft_str_lst_add_export_only(char *value);
void			ft_set_shlvl(t_shell *shell);

//exec_unset.c
int				ft_exec_unset(t_token *token, t_shell *shell);

//exec_env.c
int				ft_exec_env(t_shell *shell, t_cmd *cmd);
char			*ft_get_value_env(const char *str, t_shell *shell);
int				ft_config_pwd_env(t_shell *shell);
int				ft_config_value_env(t_shell *shell, char *value);

//exec_pwd.c
int				ft_exec_pwd(t_shell *shell, t_cmd *cmd);

//exec_exit.c
int				ft_exec_exit(t_token *token, t_shell *shell,
					t_cmd *cmd, t_pipe pipe);

//exec_echo_util.c
bool			ft_is_valid_arg(t_token *token);
bool			ft_is_newline_flag(const char *value);

//redir_pipe.c
int				ft_config_heredoc_fd_pipe(t_token *token, int index,
					t_cmd *cmd, t_pipe pipe);

//fd_utils.c
void			ft_add_fd(t_shell *shell, int fd);
void			ft_close_all_fds(t_shell *shell);
void			ft_init_fd_list(t_shell *shell);

#endif
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
PROGRAM			= minishell
SRC_DIR			= src
CMD_DIR			= cmd
BIN_DIR			= bin
INC_DIR			= -Iinc
OBJ_DIR			= build
NAME			= $(BIN_DIR)/$(PROGRAM)
SRCS			=	src/dollar_case.c src/dollar_util.c src/dollar.c \
					src/free_utils.c src/free.c src/ft_itoa.c src/lexer.c src/meta_chars.c \
					src/print.c src/quote_utils.c src/quote.c src/seperator.c src/syntax_utils.c \
					src/syntax.c src/token_append_utils.c src/token_utils.c src/token.c src/utils.c \
					src/token_append.c src/token_types.c src/token_utils2.c src/signal.c \
					src/executer.c src/executer_one.c src/executer_multiple.c src/executer_utils.c \
					src/path.c src/pipe.c src/redir.c src/redir_utils.c src/built.c \
					src/err_print.c src/utils2.c src/ft_split.c src/built2.c \
					src/exec_cd.c src/exec_echo.c src/exec_env.c src/exec_exit.c \
					src/exec_export.c src/exec_pwd.c src/exec_unset.c		

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CMD				= $(CMD_DIR)/$(PROGRAM).c
RM				= rm -rf

all:
	@mkdir -p bin
	@$(MAKE) $(NAME)

$(NAME): $(CMD) $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(CMD) $(OBJS) -o $(NAME) -lreadline -lncurses

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR) & wait
	$(RM) $(BIN_DIR) & wait

fclean: clean
	$(RM) $(NAME) & wait

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re

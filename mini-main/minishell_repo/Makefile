NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g3 -O0 -fsanitize=address,undefined
INCLUDES    = -I includes

# --- Directorios por familia ---
DIR_CORE    = srcs/core
DIR_LEXER   = srcs/lexer
DIR_PARSER  = srcs/parser
DIR_HEREDOC = srcs/heredoc
DIR_EXPAND  = srcs/expander
DIR_EXEC    = srcs/executor
DIR_PIPES   = srcs/pipes
DIR_ERRORS  = srcs/errors
DIR_UTILS   = srcs/utils
DIR_BUILT   = built

# --- Listas por familia (solo nombres de archivo) ---
SRCS_CORE    = main.c signals.c shell.c main_aux.c main_aux_input.c
SRCS_LEXER   = tokenizer.c tokenizer_aux.c handle_quotes.c
SRCS_PARSER  = parser.c parser_check.c parser_aux.c parser_aux_2.c parser_extension.c parser_extension_2.c
SRCS_HEREDOC = parser_heredoc.c parser_heredoc_aux.c heredoc.c heredoc_aux.c
SRCS_EXPAND  = expander.c expander_ultra.c expander_ultra_aux.c expander_finalizer.c
SRCS_EXEC    = executor.c executor_2.c executor_aux.c executor_aux_2.c redirections.c path_resolver.c process.c exec_redirs_only.c
SRCS_PIPES   = pipes.c pipes_2.c pipes_exec.c pipes_exec_2.c
SRCS_ERRORS  = error.c error_2.c error_vali.c
SRCS_UTILS   = free_every.c general_aux.c
SRCS_BUILT   = echo.c

# --- Composición de rutas completas ---
SRCS = \
  $(addprefix $(DIR_CORE)/,$(SRCS_CORE)) \
  $(addprefix $(DIR_LEXER)/,$(SRCS_LEXER)) \
  $(addprefix $(DIR_PARSER)/,$(SRCS_PARSER)) \
  $(addprefix $(DIR_HEREDOC)/,$(SRCS_HEREDOC)) \
  $(addprefix $(DIR_EXPAND)/,$(SRCS_EXPAND)) \
  $(addprefix $(DIR_EXEC)/,$(SRCS_EXEC)) \
  $(addprefix $(DIR_PIPES)/,$(SRCS_PIPES)) \
  $(addprefix $(DIR_ERRORS)/,$(SRCS_ERRORS)) \
  $(addprefix $(DIR_UTILS)/,$(SRCS_UTILS)) \
  $(addprefix $(DIR_BUILT)/,$(SRCS_BUILT))

OBJS    = $(SRCS:.c=.o)

HEADERS = includes/minishell.h includes/shell.h includes/tokenizer.h \
          includes/parser.h includes/status.h includes/signals.h includes/main_aux.h

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror"

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

